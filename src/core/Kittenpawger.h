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

#ifndef KITTENPAW_KITTENPAWGER_H
#define KITTENPAW_KITTENPAWGER_H


#include <vector>


#include "backend/common/interfaces/IRxListener.h"
#include "base/api/interfaces/IApiListener.h"
#include "base/crypto/Algorithm.h"
#include "base/kernel/interfaces/IBaseListener.h"
#include "base/kernel/interfaces/ITimerListener.h"
#include "base/tools/Object.h"


namespace kittenpaw {


class Controller;
class Job;
class KittenpawgerPrivate;
class IBackend;


class Kittenpawger : public ITimerListener, public IBaseListener, public IApiListener, public IRxListener
{
public:
    KITTENPAW_DISABLE_COPY_MOVE_DEFAULT(Kittenpawger)

    Kittenpawger(Controller *controller);
    ~Kittenpawger() override;

    bool isEnabled() const;
    bool isEnabled(const Algorithm &algorithm) const;
    const Algorithms &algorithms() const;
    const std::vector<IBackend *> &backends() const;
    Job job() const;
    void execCommand(char command);
    void pause();
    void setEnabled(bool enabled);
    void setJob(const Job &job, bool donate);
    void stop();

protected:
    void onConfigChanged(Config *config, Config *previousConfig) override;
    void onTimer(const Timer *timer) override;

#   ifdef KITTENPAW_FEATURE_API
    void onRequest(IApiRequest &request) override;
#   endif

#   ifdef KITTENPAW_ALGO_RANDOMX
    void onDatasetReady() override;
#   endif

private:
    KittenpawgerPrivate *d_ptr;
};


} // namespace kittenpaw


#endif /* KITTENPAW_KITTENPAWGER_H */
