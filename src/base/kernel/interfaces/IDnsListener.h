/* XMRig
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

#ifndef JDKRIG_IDNSLISTENER_H
#define JDKRIG_IDNSLISTENER_H


#include "base/tools/Object.h"


namespace jdkrig {


class DnsRecords;


class IDnsListener
{
public:
    JDKRIG_DISABLE_COPY_MOVE(IDnsListener)

    IDnsListener()          = default;
    virtual ~IDnsListener() = default;

    virtual void onResolved(const DnsRecords &records, int status, const char *error)   = 0;
};


} /* namespace jdkrig */


#endif // JDKRIG_IDNSLISTENER_H
