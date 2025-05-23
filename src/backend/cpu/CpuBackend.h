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

#ifndef KITTENPAW_CPUBACKEND_H
#define KITTENPAW_CPUBACKEND_H


#include "backend/common/interfaces/IBackend.h"
#include "base/tools/Object.h"


#include <utility>


namespace kittenpaw {


class Controller;
class CpuBackendPrivate;
class Kittenpawger;


class CpuBackend : public IBackend
{
public:
    KITTENPAW_DISABLE_COPY_MOVE_DEFAULT(CpuBackend)

    CpuBackend(Controller *controller);
    ~CpuBackend() override;

protected:
    inline void execCommand(char) override {}

    bool isEnabled() const override;
    bool isEnabled(const Algorithm &algorithm) const override;
    bool tick(uint64_t ticks) override;
    const Hashrate *hashrate() const override;
    const String &profileName() const override;
    const String &type() const override;
    void prepare(const Job &nextJob) override;
    void printHashrate(bool details) override;
    void printHealth() override;
    void setJob(const Job &job) override;
    void start(IWorker *worker, bool ready) override;
    void stop() override;

#   ifdef KITTENPAW_FEATURE_API
    rapidjson::Value toJSON(rapidjson::Document &doc) const override;
    void handleRequest(IApiRequest &request) override;
#   endif

#   ifdef KITTENPAW_FEATURE_BENCHMARK
    Benchmark *benchmark() const override;
    void printBenchProgress() const override;
#   endif

private:
    CpuBackendPrivate *d_ptr;
};


} /* namespace kittenpaw */


#endif /* KITTENPAW_CPUBACKEND_H */
