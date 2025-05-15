/* XMRig
 * Copyright (c) 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2020 XMRig       <https://github.com/jdkrig>, <support@jdkrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "backend/cuda/CudaWorker.h"
#include "backend/common/Tags.h"
#include "backend/cuda/runners/CudaCnRunner.h"
#include "backend/cuda/wrappers/CudaDevice.h"
#include "base/io/log/Log.h"
#include "base/tools/Alignment.h"
#include "base/tools/Chrono.h"
#include "core/Jdkrigger.h"
#include "crypto/common/Nonce.h"
#include "net/JobResults.h"


#ifdef JDKRIG_ALGO_RANDOMX
#   include "backend/cuda/runners/CudaRxRunner.h"
#endif


#ifdef JDKRIG_ALGO_KAWPOW
#   include "backend/cuda/runners/CudaKawPowRunner.h"
#endif


#include <cassert>
#include <thread>


namespace jdkrig {


std::atomic<bool> CudaWorker::ready;


static inline bool isReady()    { return !Nonce::isPaused() && CudaWorker::ready; }


} // namespace jdkrig



jdkrig::CudaWorker::CudaWorker(size_t id, const CudaLaunchData &data) :
    GpuWorker(id, data.thread.affinity(), -1, data.device.index()),
    m_algorithm(data.algorithm),
    m_jdkrigger(data.jdkrigger)
{
    switch (m_algorithm.family()) {
    case Algorithm::RANDOM_X:
#       ifdef JDKRIG_ALGO_RANDOMX
        m_runner = new CudaRxRunner(id, data);
#       endif
        break;

    case Algorithm::ARGON2:
        break;

    case Algorithm::KAWPOW:
#       ifdef JDKRIG_ALGO_KAWPOW
        m_runner = new CudaKawPowRunner(id, data);
#       endif
        break;

    default:
        m_runner = new CudaCnRunner(id, data);
        break;
    }

    if (!m_runner) {
        return;
    }

    if (!m_runner->init()) {
        delete m_runner;

        m_runner = nullptr;
    }
}


jdkrig::CudaWorker::~CudaWorker()
{
    delete m_runner;
}


void jdkrig::CudaWorker::jobEarlyNotification(const Job &job)
{
    if (m_runner) {
        m_runner->jobEarlyNotification(job);
    }
}


bool jdkrig::CudaWorker::selfTest()
{
    return m_runner != nullptr;
}


size_t jdkrig::CudaWorker::intensity() const
{
    return m_runner ? m_runner->roundSize() : 0;
}


void jdkrig::CudaWorker::start()
{
    while (Nonce::sequence(Nonce::CUDA) > 0) {
        if (!isReady()) {
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            while (!isReady() && Nonce::sequence(Nonce::CUDA) > 0);

            if (Nonce::sequence(Nonce::CUDA) == 0) {
                break;
            }

            if (!consumeJob()) {
                return;
            }
        }

        while (!Nonce::isOutdated(Nonce::CUDA, m_job.sequence())) {
            uint32_t foundNonce[16] = { 0 };
            uint32_t foundCount     = 0;

            if (!m_runner->run(readUnaligned(m_job.nonce()), &foundCount, foundNonce)) {
                return;
            }

            if (foundCount) {
                JobResults::submit(m_job.currentJob(), foundNonce, foundCount, m_deviceIndex);
            }

            if (!Nonce::isOutdated(Nonce::CUDA, m_job.sequence()) && !m_job.nextRound(1, intensity())) {
                JobResults::done(m_job.currentJob());
            }

            storeStats();
            std::this_thread::yield();
        }

        if (isReady() && !consumeJob()) {
            return;
        }
    }
}


bool jdkrig::CudaWorker::consumeJob()
{
    if (Nonce::sequence(Nonce::CUDA) == 0) {
        return false;
    }

    m_job.add(m_jdkrigger->job(), intensity(), Nonce::CUDA);

    return m_runner->set(m_job.currentJob(), m_job.blob());
}


void jdkrig::CudaWorker::storeStats()
{
    if (!isReady()) {
        return;
    }

    m_count += m_runner ? m_runner->processedHashes() : 0;

    const uint64_t timeStamp = Chrono::steadyMSecs();
    m_hashrateData.addDataPoint(m_count, timeStamp);

    GpuWorker::storeStats();
}
