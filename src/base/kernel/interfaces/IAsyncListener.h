/* KITTENpaw
 * Copyright 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2020 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_IASYNCLISTENER_H
#define KITTENPAW_IASYNCLISTENER_H


#include "base/tools/Object.h"


namespace kittenpaw {


class Async;


class IAsyncListener
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(IAsyncListener)

    IAsyncListener()            = default;
    virtual ~IAsyncListener()   = default;

    virtual void onAsync()      = 0;
};


} /* namespace kittenpaw */


#endif // KITTENPAW_IASYNCLISTENER_H
