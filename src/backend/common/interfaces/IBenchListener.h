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

#ifndef JDKRIG_IBENCHLISTENER_H
#define JDKRIG_IBENCHLISTENER_H


#include "base/tools/Object.h"


namespace jdkrig {


class IBackend;


class IBenchListener
{
public:
    JDKRIG_DISABLE_COPY_MOVE(IBenchListener)

    IBenchListener()            = default;
    virtual ~IBenchListener()   = default;

    virtual void onBenchDone(uint64_t result, uint64_t diff, uint64_t ts)               = 0;
    virtual void onBenchReady(uint64_t ts, uint32_t threads, const IBackend *backend)   = 0;
};


} /* namespace jdkrig */


#endif // JDKRIG_IBENCHLISTENER_H
