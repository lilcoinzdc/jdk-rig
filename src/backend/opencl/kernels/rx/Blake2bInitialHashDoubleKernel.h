/* KITTENpaw
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_BLAKE2BINITIALHASHDOUBLEKERNEL_H
#define KITTENPAW_BLAKE2BINITIALHASHDOUBLEKERNEL_H


#include "backend/opencl/wrappers/OclKernel.h"


namespace kittenpaw {


class Blake2bInitialHashDoubleKernel : public OclKernel
{
public:
    inline Blake2bInitialHashDoubleKernel(cl_program program) : OclKernel(program, "blake2b_initial_hash_double") {}

    void enqueue(cl_command_queue queue, size_t threads);
    void setArgs(cl_mem out, cl_mem blockTemplate);
    void setBlobSize(size_t size);
    void setNonce(uint32_t nonce);
};


} // namespace kittenpaw


#endif /* KITTENPAW_BLAKE2BINITIALHASHDOUBLEKERNEL_H */
