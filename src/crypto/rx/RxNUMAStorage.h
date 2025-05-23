/* KITTENpaw
 * Copyright (c) 2018-2019 tevador     <tevador@gmail.com>
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

#ifndef KITTENPAW_RX_NUMASTORAGE_H
#define KITTENPAW_RX_NUMASTORAGE_H


#include "backend/common/interfaces/IRxStorage.h"


#include <vector>


namespace kittenpaw
{


class RxNUMAStoragePrivate;


class RxNUMAStorage : public IRxStorage
{
public:
    KITTENPAW_DISABLE_COPY_MOVE(RxNUMAStorage);

    RxNUMAStorage(const std::vector<uint32_t> &nodeset);
    ~RxNUMAStorage() override;

protected:
    bool isAllocated() const override;
    HugePagesInfo hugePages() const override;
    RxDataset *dataset(const Job &job, uint32_t nodeId) const override;
    void init(const RxSeed &seed, uint32_t threads, bool hugePages, bool oneGbPages, RxConfig::Mode mode, int priority) override;

private:
    RxNUMAStoragePrivate *d_ptr;
};


} /* namespace kittenpaw */


#endif /* KITTENPAW_RX_NUMASTORAGE_H */
