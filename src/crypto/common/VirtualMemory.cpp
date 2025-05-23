/* KITTENpaw
 * Copyright (c) 2018-2020 tevador     <tevador@gmail.com>
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


#include "crypto/common/VirtualMemory.h"
#include "backend/cpu/Cpu.h"
#include "base/io/log/Log.h"
#include "crypto/common/MemoryPool.h"
#include "crypto/common/portable/mm_malloc.h"


#ifdef KITTENPAW_FEATURE_HWLOC
#   include "crypto/common/NUMAMemoryPool.h"
#endif


#include <cinttypes>
#include <mutex>


namespace kittenpaw {


size_t VirtualMemory::m_hugePageSize    = VirtualMemory::kDefaultHugePageSize;
static IMemoryPool *pool                = nullptr;
static std::mutex mutex;


} // namespace kittenpaw


kittenpaw::VirtualMemory::VirtualMemory(size_t size, bool hugePages, bool oneGbPages, bool usePool, uint32_t node, size_t alignSize) :
    m_size(alignToHugePageSize(size)),
    m_node(node),
    m_capacity(m_size)
{
    if (usePool) {
        std::lock_guard<std::mutex> lock(mutex);
        if (hugePages && !pool->isHugePages(node) && allocateLargePagesMemory()) {
            return;
        }

        m_scratchpad = pool->get(m_size, node);
        if (m_scratchpad) {
            m_flags.set(FLAG_HUGEPAGES, pool->isHugePages(node));
            m_flags.set(FLAG_EXTERNAL,  true);

            return;
        }
    }

    if (oneGbPages && allocateOneGbPagesMemory()) {
        m_capacity = align(size, 1ULL << 30);
        return;
    }

    if (hugePages && allocateLargePagesMemory()) {
        return;
    }

    m_scratchpad = static_cast<uint8_t*>(_mm_malloc(m_size, alignSize));
}


kittenpaw::VirtualMemory::~VirtualMemory()
{
    if (!m_scratchpad) {
        return;
    }

    if (m_flags.test(FLAG_EXTERNAL)) {
        std::lock_guard<std::mutex> lock(mutex);
        pool->release(m_node);
    }
    else if (isHugePages() || isOneGbPages()) {
        freeLargePagesMemory();
    }
    else {
        _mm_free(m_scratchpad);
    }
}


kittenpaw::HugePagesInfo kittenpaw::VirtualMemory::hugePages() const
{
    return { this };
}


#ifndef KITTENPAW_FEATURE_HWLOC
uint32_t kittenpaw::VirtualMemory::bindToNUMANode(int64_t)
{
    return 0;
}
#endif


void kittenpaw::VirtualMemory::destroy()
{
    delete pool;
}


void kittenpaw::VirtualMemory::init(size_t poolSize, size_t hugePageSize)
{
    if (!pool) {
        osInit(hugePageSize);
    }

#   ifdef KITTENPAW_FEATURE_HWLOC
    if (Cpu::info()->nodes() > 1) {
        pool = new NUMAMemoryPool(align(poolSize, Cpu::info()->nodes()), hugePageSize > 0);
    } else
#   endif
    {
        pool = new MemoryPool(poolSize, hugePageSize > 0);
    }
}
