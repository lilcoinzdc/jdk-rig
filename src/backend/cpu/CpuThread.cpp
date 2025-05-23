/* KITTENpaw
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
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


#include "backend/cpu/CpuThread.h"
#include "3rdparty/rapidjson/document.h"
#include "base/io/json/Json.h"


kittenpaw::CpuThread::CpuThread(const rapidjson::Value &value)
{
    if (value.IsArray() && value.Size() >= 2) {
        m_intensity = value[0].GetUint();
        m_affinity  = value[1].GetInt();
    }
    else if (value.IsInt()) {
        m_intensity = 0;
        m_affinity  = value.GetInt();
    }
}


rapidjson::Value kittenpaw::CpuThread::toJSON(rapidjson::Document &doc) const
{
    using namespace rapidjson;
    if (m_intensity == 0) {
        return Value(m_affinity);
    }

    auto &allocator = doc.GetAllocator();

    Value out(kArrayType);
    out.PushBack(m_intensity, allocator);
    out.PushBack(m_affinity, allocator);

    return out;
}
