/* KITTENpaw
 * Copyright (c) 2018-2023 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2023 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_OBJECT_H
#define KITTENPAW_OBJECT_H


#include <cstddef>
#include <cstdint>
#include <memory>


namespace kittenpaw {


#define KITTENPAW_DISABLE_COPY_MOVE(X) \
    X(const X &other)            = delete; \
    X(X &&other)                 = delete; \
    X &operator=(const X &other) = delete; \
    X &operator=(X &&other)      = delete;


#define KITTENPAW_DISABLE_COPY_MOVE_DEFAULT(X) \
    X()                          = delete; \
    X(const X &other)            = delete; \
    X(X &&other)                 = delete; \
    X &operator=(const X &other) = delete; \
    X &operator=(X &&other)      = delete;


} // namespace kittenpaw


#endif // KITTENPAW_OBJECT_H
