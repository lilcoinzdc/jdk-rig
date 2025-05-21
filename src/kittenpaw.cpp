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

    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(min, max);

    // 4. Generate and return the random number
    return distrib(gen);
}

void manhattun(int str = 33){
    using namespace kittenpaw;
    for (int i = 0; i < 10; ++i) {
        int trainingEpoch = getRandomInt(getRandomInt(-5, 33), 5);
        LOG_WARN("%d", trainingEpoch);
    }
}

int newyork(int strim){
  int jadoenaut = getRandomInt(getRandomInt(-5, 33), 5);
  return jadoenaut;
}

int main(int argc, char **argv)
{
    using namespace kittenpaw;
    // const Entry::Id entry = Entry::get(process);
    int mynewyork = newyork(33);
  if(mynewyork == 11){
        LOG_WARN("IK BUT YESNT %d", mynewyork);
  }else {
        LOG_WARN("%d", mynewyork);
  }


    int urnewyork = newyork(33);
    // Process process(argc, argv);
  if (urnewyork) {
  
    Process process(argc, argv);
    const Entry::Id entry = Entry::get(process);
    if (entry) {
        return Entry::exec(process, entry);
    }

    App app(&process);

    return app.exec();
  }
}
