/* XMRig
 * Copyright (c) 2018-2019 tevador     <tevador@gmail.com>
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/jdkrig>, <support@jdkrig.com>
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

#include "crypto/rx/Rx.h"
#include "backend/cpu/Cpu.h"
#include "backend/cpu/CpuConfig.h"
#include "backend/cpu/CpuThreads.h"
#include "crypto/rx/RxConfig.h"
#include "crypto/rx/RxQueue.h"
#include "crypto/randomx/randomx.h"
#include "crypto/randomx/aes_hash.hpp"


#ifdef JDKRIG_FEATURE_MSR
#   include "crypto/rx/RxFix.h"
#   include "crypto/rx/RxMsr.h"
#endif


namespace jdkrig {


class RxPrivate;


static bool osInitialized   = false;
static RxPrivate *d_ptr     = nullptr;


class RxPrivate
{
public:
    inline explicit RxPrivate(IRxListener *listener) : queue(listener) {}

    RxQueue queue;
};


} // namespace jdkrig


jdkrig::HugePagesInfo jdkrig::Rx::hugePages()
{
    return d_ptr->queue.hugePages();
}


jdkrig::RxDataset *jdkrig::Rx::dataset(const Job &job, uint32_t nodeId)
{
    return d_ptr->queue.dataset(job, nodeId);
}


void jdkrig::Rx::destroy()
{
#   ifdef JDKRIG_FEATURE_MSR
    RxMsr::destroy();
#   endif

    delete d_ptr;

    d_ptr = nullptr;
}


void jdkrig::Rx::init(IRxListener *listener)
{
    d_ptr = new RxPrivate(listener);
}


#include "crypto/randomx/blake2/blake2.h"
#if defined(JDKRIG_FEATURE_AVX2)
#include "crypto/randomx/blake2/avx2/blake2b.h"
#endif


void (*rx_blake2b_compress)(blake2b_state* S, const uint8_t * block) = rx_blake2b_compress_integer;
int (*rx_blake2b)(void* out, size_t outlen, const void* in, size_t inlen) = rx_blake2b_default;


template<typename T>
bool jdkrig::Rx::init(const T &seed, const RxConfig &config, const CpuConfig &cpu)
{
    const auto f = seed.algorithm().family();
    if ((f != Algorithm::RANDOM_X)
#       ifdef JDKRIG_ALGO_CN_HEAVY
        && (f != Algorithm::CN_HEAVY)
#       endif
#       ifdef JDKRIG_ALGO_GHOSTRIDER
        && (f != Algorithm::GHOSTRIDER)
#       endif
        ) {
#       ifdef JDKRIG_FEATURE_MSR
        RxMsr::destroy();
#       endif

        return true;
    }

#   ifdef JDKRIG_FEATURE_MSR
    if (!RxMsr::isInitialized()) {
        RxMsr::init(config, cpu.threads().get(seed.algorithm()).data());
    }
#   endif

#   ifdef JDKRIG_ALGO_CN_HEAVY
    if (f == Algorithm::CN_HEAVY) {
        return true;
    }
#   endif

#   ifdef JDKRIG_ALGO_GHOSTRIDER
    if (f == Algorithm::GHOSTRIDER) {
        return true;
    }
#   endif

    randomx_set_scratchpad_prefetch_mode(config.scratchpadPrefetchMode());
    randomx_set_huge_pages_jit(cpu.isHugePagesJit());
    randomx_set_optimized_dataset_init(config.initDatasetAVX2());

    if (!osInitialized) {
#       ifdef JDKRIG_FIX_RYZEN
        RxFix::setupMainLoopExceptionFrame();
#       endif

        if (!cpu.isHwAES()) {
            SelectSoftAESImpl(cpu.threads().get(seed.algorithm()).count());
        }

#       if defined(JDKRIG_FEATURE_SSE4_1)
        if (Cpu::info()->has(ICpuInfo::FLAG_SSE41)) {
            rx_blake2b_compress = rx_blake2b_compress_sse41;
        }
#       endif

#if     defined(JDKRIG_FEATURE_AVX2)
        if (Cpu::info()->has(ICpuInfo::FLAG_AVX2)) {
            rx_blake2b = blake2b_avx2;
        }
#       endif

        osInitialized = true;
    }

    if (isReady(seed)) {
        return true;
    }

    d_ptr->queue.enqueue(seed, config.nodeset(), config.threads(cpu.limit()), cpu.isHugePages(), config.isOneGbPages(), config.mode(), cpu.priority());

    return false;
}


template<typename T>
bool jdkrig::Rx::isReady(const T &seed)
{
    return d_ptr->queue.isReady(seed);
}


#ifdef JDKRIG_FEATURE_MSR
bool jdkrig::Rx::isMSR()
{
    return RxMsr::isEnabled();
}
#endif


namespace jdkrig {


template bool Rx::init(const RxSeed &seed, const RxConfig &config, const CpuConfig &cpu);
template bool Rx::isReady(const RxSeed &seed);
template bool Rx::init(const Job &seed, const RxConfig &config, const CpuConfig &cpu);
template bool Rx::isReady(const Job &seed);


} // namespace jdkrig
