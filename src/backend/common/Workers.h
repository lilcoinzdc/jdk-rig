/* KITTENpaw
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_WORKERS_H
#define KITTENPAW_WORKERS_H


#include <memory>


#include "backend/common/Thread.h"
#include "backend/cpu/CpuLaunchData.h"


#ifdef KITTENPAW_FEATURE_OPENCL
#   include "backend/opencl/OclLaunchData.h"
#endif


#ifdef KITTENPAW_FEATURE_CUDA
#   include "backend/cuda/CudaLaunchData.h"
#endif


namespace kittenpaw {


class Benchmark;
class Hashrate;
class WorkersPrivate;


template<class T>
class Workers
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(Workers)

    Workers();
    ~Workers();

    inline void start(const std::vector<T> &data)   { start(data, true); }

    bool tick(uint64_t ticks);
    const Hashrate *hashrate() const;
    void jobEarlyNotification(const Job &job);
    void setBackend(IBackend *backend);
    void stop();

#   ifdef KITTENPAW_FEATURE_BENCHMARK
    void start(const std::vector<T> &data, const std::shared_ptr<Benchmark> &benchmark);
#   endif

private:
    static IWorker *create(Thread<T> *handle);
    static void *onReady(void *arg);

    void start(const std::vector<T> &data, bool sleep);

    std::vector<Thread<T> *> m_workers;
    WorkersPrivate *d_ptr;
};


template<class T>
void kittenpaw::Workers<T>::jobEarlyNotification(const Job &job)
{
    for (Thread<T>* t : m_workers) {
        if (t->worker()) {
            t->worker()->jobEarlyNotification(job);
        }
    }
}


template<>
IWorker *Workers<CpuLaunchData>::create(Thread<CpuLaunchData> *handle);
extern template class Workers<CpuLaunchData>;


#ifdef KITTENPAW_FEATURE_OPENCL
template<>
IWorker *Workers<OclLaunchData>::create(Thread<OclLaunchData> *handle);
extern template class Workers<OclLaunchData>;
#endif


#ifdef KITTENPAW_FEATURE_CUDA
template<>
IWorker *Workers<CudaLaunchData>::create(Thread<CudaLaunchData> *handle);
extern template class Workers<CudaLaunchData>;
#endif


} // namespace kittenpaw


#endif /* KITTENPAW_WORKERS_H */
