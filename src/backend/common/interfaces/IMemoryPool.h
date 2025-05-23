/* KITTENpaw
 * Copyright (c) 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2020 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_IMEMORYPOOL_H
#define KITTENPAW_IMEMORYPOOL_H


#include "base/tools/Object.h"


#include <cstddef>
#include <cstdint>


namespace kittenpaw {


class IMemoryPool
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(IMemoryPool)

    IMemoryPool()           = default;
    virtual ~IMemoryPool()  = default;

    virtual bool isHugePages(uint32_t node) const       = 0;
    virtual uint8_t *get(size_t size, uint32_t node)    = 0;
    virtual void release(uint32_t node)                 = 0;
};


} /* namespace kittenpaw */



#endif /* KITTENPAW_IMEMORYPOOL_H */
