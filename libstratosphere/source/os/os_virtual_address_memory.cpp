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
#include <stratosphere.hpp>

namespace ams::os {

    namespace {

        /* TODO: Remove, add VammManager */
        size_t GetSystemResourceSize() {
            u64 v;
            if (R_SUCCEEDED(svcGetInfo(std::addressof(v), InfoType_SystemResourceSizeTotal, CUR_PROCESS_HANDLE, 0))) {
                return v;
            } else {
                return 0;
            }
        }

    }

    bool IsVirtualAddressMemoryEnabled() {
        return GetSystemResourceSize() > 0;
    }

}
