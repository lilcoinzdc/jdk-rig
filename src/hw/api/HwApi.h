/* XMRig
 * Copyright (c) 2018-2021 SChernykh    <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig        <https://github.com/jdkrig>, <support@jdkrig.com>
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

#ifndef JDKRIG_HWAPI_H
#define JDKRIG_HWAPI_H


#include "base/api/interfaces/IApiListener.h"


#include <memory>


namespace jdkrig {


class DmiReader;


class HwApi : public IApiListener
{
public:
    HwApi() = default;

protected:
    void onRequest(IApiRequest &request) override;

private:
#   ifdef JDKRIG_FEATURE_DMI
    std::shared_ptr<DmiReader> m_dmi;
#   endif
};


} /* namespace jdkrig */


#endif /* JDKRIG_HWAPI_H */
