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

#ifndef KITTENPAW_CONTROLLER_H
#define KITTENPAW_CONTROLLER_H


#include "base/kernel/Base.h"


#include <memory>


namespace kittenpaw {


class HwApi;
class Job;
class Kittenpawger;
class Network;


class Controller : public Base
{
public:
    KITTENPAW_DISABLE_COPY_MOVE_DEFAULT(Controller)

    Controller(Process *process);
    ~Controller() override;

    int init() override;
    void start() override;
    void stop() override;

    Kittenpawger *kittenpawger() const;
    Network *network() const;
    void execCommand(char command) const;

private:
    std::shared_ptr<Kittenpawger> m_kittenpawger;
    std::shared_ptr<Network> m_network;

#   ifdef KITTENPAW_FEATURE_API
    std::shared_ptr<HwApi> m_hwApi;
#   endif
};


} // namespace kittenpaw


#endif /* KITTENPAW_CONTROLLER_H */
