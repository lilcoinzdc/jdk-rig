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

#ifndef KITTENPAW_TAGS_H
#define KITTENPAW_TAGS_H


#include <cstddef>
#include <cstdint>


namespace kittenpaw {


class Tags
{
public:
    static const char *config();
    static const char *network();
    static const char *origin();
    static const char *signal();

#   ifdef KITTENPAW_KITTENPAWGER_PROJECT
    static const char *cpu();
    static const char *kittenpawger();
#   ifdef KITTENPAW_ALGO_RANDOMX
    static const char *randomx();
#   endif
#   ifdef KITTENPAW_FEATURE_BENCHMARK
    static const char *bench();
#   endif
#   endif

#   ifdef KITTENPAW_PROXY_PROJECT
    static const char *proxy();
#   endif

#   ifdef KITTENPAW_FEATURE_CUDA
    static const char *nvidia();
#   endif

#   ifdef KITTENPAW_FEATURE_OPENCL
    static const char *opencl();
#   endif

#   ifdef KITTENPAW_FEATURE_PROFILING
    static const char* profiler();
#   endif
};


} /* namespace kittenpaw */


#endif /* KITTENPAW_TAGS_H */
