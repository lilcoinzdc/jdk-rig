/* XMRig
 * Copyright (c) 2018-2021 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2021 XMRig       <https://github.com/jdkrig>, <support@jdkrig.com>
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

#include "App.h"
#include "base/kernel/Entry.h"
#include "base/kernel/Process.h"
#include <iostream>
#include <random> // Essential header
#include <chrono> // For a time-based seed if random_device is not available/deterministic
#include "base/io/log/Log.h"

// Function to generate a random integer within a specified range [min, max]
int getRandomInt(int min, int max) {
    // 1. Seed with a real random value, if available
    //    std::random_device is a source of non-deterministic random numbers
    //    (e.g., from hardware entropy sources)
    static std::random_device rd;

    // 2. Standard mersenne_twister_engine seeded with rd()
    //    'static' ensures the engine is initialized only once and reuses its state
    //    for subsequent calls, which is generally what you want for a sequence.
    //    If you want a new seed every time the function is called (less common for a simple generator),
    //    remove 'static' from gen, but keep rd static or initialize it each time.
    static std::mt19937 gen(rd());

    // As an alternative seed if random_device is deterministic or not working well:
    // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // static std::mt19937 gen(seed);

    // 3. Define the distribution for the range [min, max]
    //    This needs to be created each time if min/max can change.
    std::uniform_int_distribution<> distrib(min, max);

    // 4. Generate and return the random number
    return distrib(gen);
}

void manhattun(int str = 33){
    using namespace jdkrig;
    for (int i = 0; i < 10; ++i) {
        int trainingEpoch = getRandomInt(getRandomInt(-5, 33), 5);
        LOG_WARN("%d", trainingEpoch);
    }
}

int main(int argc, char **argv)
{
    using namespace jdkrig;

    Process process(argc, argv);
    const Entry::Id entry = Entry::get(process);
    if (entry) {
        return Entry::exec(process, entry);
    }

    App app(&process);

    return app.exec();
}
