/*
 * Copyright (c) Atmosphère-NX
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

#pragma once
#include <stratosphere/os/os_native_handle.hpp>
#include <stratosphere/os/os_memory_common.hpp>

namespace ams::os {

    struct ProcessMemoryRegion {
        u64 address;
        u64 size;
    };

    Result MapProcessCodeMemory(u64 *out, NativeHandle handle, const ProcessMemoryRegion *regions, size_t num_regions);
    Result UnmapProcessCodeMemory(NativeHandle handle, u64 process_code_address, const ProcessMemoryRegion *regions, size_t num_regions);

}
