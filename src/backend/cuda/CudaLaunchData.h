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

#ifndef KITTENPAW_CUDALAUNCHDATA_H
#define KITTENPAW_CUDALAUNCHDATA_H


#include "backend/cuda/CudaThread.h"
#include "base/crypto/Algorithm.h"
#include "crypto/common/Nonce.h"


namespace kittenpaw {


class CudaDevice;
class Kittenpawger;


class CudaLaunchData
{
public:
    CudaLaunchData(const Kittenpawger *kittenpawger, const Algorithm &algorithm, const CudaThread &thread, const CudaDevice &device);

    bool isEqual(const CudaLaunchData &other) const;

    inline constexpr static Nonce::Backend backend() { return Nonce::CUDA; }

    inline bool operator!=(const CudaLaunchData &other) const    { return !isEqual(other); }
    inline bool operator==(const CudaLaunchData &other) const    { return isEqual(other); }

    static const char *tag();

    const Algorithm algorithm;
    const CudaDevice &device;
    const CudaThread thread;
    const int64_t affinity;
    const Kittenpawger *kittenpawger;
    const uint32_t benchSize = 0;
};


} // namespace kittenpaw


#endif /* KITTENPAW_OCLLAUNCHDATA_H */
