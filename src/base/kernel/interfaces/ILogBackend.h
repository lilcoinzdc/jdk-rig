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

#ifndef KITTENPAW_ILOGBACKEND_H
#define KITTENPAW_ILOGBACKEND_H


#include "base/tools/Object.h"


#include <cstdarg>
#include <cstddef>


namespace kittenpaw {


class ILogBackend
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(ILogBackend)

    ILogBackend()           = default;
    virtual ~ILogBackend()  = default;

    virtual void print(uint64_t timestamp, int level, const char *line, size_t offset, size_t size, bool colors) = 0;
};


} /* namespace kittenpaw */


#endif // KITTENPAW_ILOGBACKEND_H
