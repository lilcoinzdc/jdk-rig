/* KITTENpaw
 * Copyright (c) 2008-2018 Advanced Micro Devices, Inc.
 * Copyright (c) 2018-2021 SChernykh                    <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 KITTENpaw                        <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_ADLLIB_H
#define KITTENPAW_ADLLIB_H


#include "backend/opencl/wrappers/AdlHealth.h"


namespace kittenpaw {


class OclDevice;


class AdlLib
{
public:
    static bool init();
    static const char *lastError() noexcept;
    static void close();

    static AdlHealth health(const OclDevice &device);

    static inline bool isInitialized() noexcept         { return m_initialized; }
    static inline bool isReady() noexcept               { return m_ready; }

private:
    static bool dlopen();
    static bool load();

    static bool m_initialized;
    static bool m_ready;
};


} // namespace kittenpaw


#endif /* KITTENPAW_ADLLIB_H */
