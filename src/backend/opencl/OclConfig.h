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

#ifndef KITTENPAW_OCLCONFIG_H
#define KITTENPAW_OCLCONFIG_H


#include "backend/common/Threads.h"
#include "backend/opencl/OclLaunchData.h"
#include "backend/opencl/OclThreads.h"
#include "backend/opencl/wrappers/OclPlatform.h"


namespace kittenpaw {


class OclConfig
{
public:
    OclConfig();

    OclPlatform platform() const;
    rapidjson::Value toJSON(rapidjson::Document &doc) const;
    std::vector<OclLaunchData> get(const Kittenpawger *kittenpawger, const Algorithm &algorithm, const OclPlatform &platform, const std::vector<OclDevice> &devices) const;
    void read(const rapidjson::Value &value);

    inline bool isCacheEnabled() const                  { return m_cache; }
    inline bool isEnabled() const                       { return m_enabled; }
    inline bool isShouldSave() const                    { return m_shouldSave; }
    inline const String &loader() const                 { return m_loader; }
    inline const Threads<OclThreads> &threads() const   { return m_threads; }

#   ifdef KITTENPAW_FEATURE_ADL
    inline bool isAdlEnabled() const                    { return m_adl; }
#   endif

private:
    void generate();
    void setDevicesHint(const char *devicesHint);

    bool m_cache         = true;
    bool m_enabled       = false;
    bool m_shouldSave    = false;
    std::vector<uint32_t> m_devicesHint;
    String m_loader;
    Threads<OclThreads> m_threads;

#   ifndef KITTENPAW_OS_APPLE
    void setPlatform(const rapidjson::Value &platform);

    String m_platformVendor;
    uint32_t m_platformIndex = 0;
#   endif

#   ifdef KITTENPAW_FEATURE_ADL
    bool m_adl          = true;
#   endif
};


} /* namespace kittenpaw */


#endif /* KITTENPAW_OCLCONFIG_H */
