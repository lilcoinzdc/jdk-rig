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

#include "core/Controller.h"
#include "backend/cpu/Cpu.h"
#include "core/config/Config.h"
#include "core/Kittenpawger.h"
#include "crypto/common/VirtualMemory.h"
#include "net/Network.h"


#ifdef KITTENPAW_FEATURE_API
#   include "base/api/Api.h"
#   include "hw/api/HwApi.h"
#endif


#include <cassert>


kittenpaw::Controller::Controller(Process *process) :
    Base(process)
{
}


kittenpaw::Controller::~Controller()
{
    VirtualMemory::destroy();
}


int kittenpaw::Controller::init()
{
    Base::init();

    VirtualMemory::init(config()->cpu().memPoolSize(), config()->cpu().hugePageSize());

    m_network = std::make_shared<Network>(this);

#   ifdef KITTENPAW_FEATURE_API
    m_hwApi = std::make_shared<HwApi>();
    api()->addListener(m_hwApi.get());
#   endif

    return 0;
}


void kittenpaw::Controller::start()
{
    Base::start();

    m_kittenpawger = std::make_shared<Kittenpawger>(this);

    network()->connect();
}


void kittenpaw::Controller::stop()
{
    Base::stop();

    m_network.reset();

    m_kittenpawger->stop();
    m_kittenpawger.reset();
}


kittenpaw::Kittenpawger *kittenpaw::Controller::kittenpawger() const
{
    assert(m_kittenpawger);

    return m_kittenpawger.get();
}


kittenpaw::Network *kittenpaw::Controller::network() const
{
    assert(m_network);

    return m_network.get();
}


void kittenpaw::Controller::execCommand(char command) const
{
    kittenpawger()->execCommand(command);
    network()->execCommand(command);
}
