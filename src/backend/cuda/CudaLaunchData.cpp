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


#include "backend/cuda/CudaLaunchData.h"
#include "backend/common/Tags.h"


kittenpaw::CudaLaunchData::CudaLaunchData(const Kittenpawger *kittenpawger, const Algorithm &algorithm, const CudaThread &thread, const CudaDevice &device) :
    algorithm(algorithm),
    device(device),
    thread(thread),
    affinity(thread.affinity()),
    kittenpawger(kittenpawger)
{
}


bool kittenpaw::CudaLaunchData::isEqual(const CudaLaunchData &other) const
{
    return (other.algorithm.family() == algorithm.family() &&
            other.algorithm.l3()     == algorithm.l3() &&
            other.thread             == thread);
}


const char *kittenpaw::CudaLaunchData::tag()
{
    return cuda_tag();
}
