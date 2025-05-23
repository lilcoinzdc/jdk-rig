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

#ifndef KITTENPAW_IOCLRUNNER_H
#define KITTENPAW_IOCLRUNNER_H


#include "base/tools/Object.h"


#include <cstdint>


using cl_context = struct _cl_context *;


namespace kittenpaw {


class Algorithm;
class Job;
class OclLaunchData;


class IOclRunner
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(IOclRunner)

    IOclRunner()          = default;
    virtual ~IOclRunner() = default;

    virtual cl_context ctx() const                          = 0;
    virtual const Algorithm &algorithm() const              = 0;
    virtual const char *buildOptions() const                = 0;
    virtual const char *deviceKey() const                   = 0;
    virtual const char *source() const                      = 0;
    virtual const OclLaunchData &data() const               = 0;
    virtual size_t intensity() const                        = 0;
    virtual size_t threadId() const                         = 0;
    virtual uint32_t roundSize() const                      = 0;
    virtual uint32_t processedHashes() const                = 0;
    virtual uint32_t deviceIndex() const                    = 0;
    virtual void build()                                    = 0;
    virtual void init()                                     = 0;
    virtual void run(uint32_t nonce, uint32_t nonce_offset, uint32_t *hashOutput)  = 0;
    virtual void set(const Job &job, uint8_t *blob)         = 0;
    virtual void jobEarlyNotification(const Job&)           = 0;

protected:
    virtual size_t bufferSize() const                       = 0;
};


} /* namespace kittenpaw */


#endif // KITTENPAW_IOCLRUNNER_H
