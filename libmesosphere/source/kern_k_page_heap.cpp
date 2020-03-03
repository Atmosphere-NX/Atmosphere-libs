/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <mesosphere.hpp>

namespace ams::kern {

    size_t KPageHeap::CalculateMetadataOverheadSize(size_t region_size, const size_t *block_shifts, size_t num_block_shifts) {
        size_t overhead_size = 0;
        for (size_t i = 0; i < num_block_shifts; i++) {
            overhead_size += KPageHeap::Block::CalculateMetadataOverheadSize(region_size, block_shifts[i], (i != num_block_shifts - 1) ? block_shifts[i + 1] : 0);
        }
        return util::AlignUp(overhead_size, KMemoryManager::PageSize);
    }

}
