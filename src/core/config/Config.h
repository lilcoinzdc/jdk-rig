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

#ifndef KITTENPAW_CONFIG_H
#define KITTENPAW_CONFIG_H


#include <cstdint>


#include "3rdparty/rapidjson/fwd.h"
#include "backend/cpu/CpuConfig.h"
#include "base/kernel/config/BaseConfig.h"
#include "base/tools/Object.h"


namespace kittenpaw {


class ConfigPrivate;
class CudaConfig;
class IThread;
class OclConfig;
class RxConfig;


class Config : public BaseConfig
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(Config);

    static const char *kPauseOnBattery;
    static const char *kPauseOnActive;

#   ifdef KITTENPAW_FEATURE_OPENCL
    static const char *kOcl;
#   endif

#   ifdef KITTENPAW_FEATURE_CUDA
    static const char *kCuda;
#   endif

#   if defined(KITTENPAW_FEATURE_NVML) || defined (KITTENPAW_FEATURE_ADL)
    static const char *kHealthPrintTime;
#   endif

#   ifdef KITTENPAW_FEATURE_DMI
    static const char *kDMI;
#   endif

    Config();
    ~Config() override;

    inline bool isPauseOnActive() const { return idleTime() > 0; }

    bool isPauseOnBattery() const;
    const CpuConfig &cpu() const;
    uint32_t idleTime() const;

#   ifdef KITTENPAW_FEATURE_OPENCL
    const OclConfig &cl() const;
#   endif

#   ifdef KITTENPAW_FEATURE_CUDA
    const CudaConfig &cuda() const;
#   endif

#   ifdef KITTENPAW_ALGO_RANDOMX
    const RxConfig &rx() const;
#   endif

#   if defined(KITTENPAW_FEATURE_NVML) || defined (KITTENPAW_FEATURE_ADL)
    uint32_t healthPrintTime() const;
#   else
    uint32_t healthPrintTime() const        { return 0; }
#   endif

#   ifdef KITTENPAW_FEATURE_DMI
    bool isDMI() const;
#   else
    static constexpr inline bool isDMI()    { return false; }
#   endif

    bool isShouldSave() const;
    bool read(const IJsonReader &reader, const char *fileName) override;
    void getJSON(rapidjson::Document &doc) const override;

private:
    ConfigPrivate *d_ptr;
};


} /* namespace kittenpaw */


#endif /* KITTENPAW_CONFIG_H */
