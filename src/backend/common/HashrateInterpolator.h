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

#ifndef KITTENPAW_HASHRATE_INTERPOLATOR_H
#define KITTENPAW_HASHRATE_INTERPOLATOR_H


#include <mutex>
#include <deque>
#include <utility>


namespace kittenpaw {


class HashrateInterpolator
{
public:
    enum {
        LagMS = 4000,
    };

    uint64_t interpolate(uint64_t timeStamp) const;
    void addDataPoint(uint64_t count, uint64_t timeStamp);

private:
    // Buffer of hashrate counters, used for linear interpolation of past data
    mutable std::mutex m_lock;
    std::deque<std::pair<uint64_t, uint64_t> > m_data;
};


} // namespace kittenpaw


#endif /* KITTENPAW_HASHRATE_INTERPOLATOR_H */
