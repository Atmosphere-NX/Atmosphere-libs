/*
 * Copyright (c) 2018-2019 Atmosphère-NX
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

#include <switch.h>
#include <stratosphere.hpp>
#include <stratosphere/cfg.hpp>

namespace sts::cfg {

    namespace {

        /* Convenience definitions. */
        constexpr u64 InitialProcessIdMinDeprecated = 0x00;
        constexpr u64 InitialProcessIdMaxDeprecated = 0x50;

        /* Privileged process globals. */
        HosMutex g_lock;
        bool g_detected_privileged_process = false;
        bool g_is_privileged_process = false;

        /* SD card helpers. */
        void GetPrivilegedProcessIdRange(u64 *out_min, u64 *out_max) {
            u64 min = 0, max = 0;
             if (GetRuntimeFirmwareVersion() >= FirmwareVersion_500) {
                /* On 5.0.0+, we can get precise limits from svcGetSystemInfo. */
                R_ASSERT(svcGetSystemInfo(&min, SystemInfoType_InitialProcessIdRange, INVALID_HANDLE, InitialProcessIdRangeInfo_Minimum));
                R_ASSERT(svcGetSystemInfo(&max, SystemInfoType_InitialProcessIdRange, INVALID_HANDLE, InitialProcessIdRangeInfo_Maximum));
            } else if (GetRuntimeFirmwareVersion() >= FirmwareVersion_400) {
                /* On 4.0.0-4.1.0, we can get the precise limits from normal svcGetInfo. */
                R_ASSERT(svcGetInfo(&min, InfoType_InitialProcessIdRange, INVALID_HANDLE, InitialProcessIdRangeInfo_Minimum));
                R_ASSERT(svcGetInfo(&max, InfoType_InitialProcessIdRange, INVALID_HANDLE, InitialProcessIdRangeInfo_Maximum));
            } else {
                /* On < 4.0.0, we just use hardcoded extents. */
                min = InitialProcessIdMinDeprecated;
                max = InitialProcessIdMaxDeprecated;
            }

            *out_min = min;
            *out_max = max;
        }

        u64 GetCurrentProcessId() {
            u64 process_id = 0;
            R_ASSERT(svcGetProcessId(&process_id, CUR_PROCESS_HANDLE));
            return process_id;
        }

        void DetectIsPrivilegedProcess() {
            u64 min = 0, max = 0, cur = 0;
            GetPrivilegedProcessIdRange(&min, &max);
            cur = GetCurrentProcessId();
            g_is_privileged_process = min <= cur && cur <= max;
            g_detected_privileged_process = true;
        }


    }

    /* SD card utilities. */
    bool IsPrivilegedProcess() {
        std::scoped_lock<HosMutex> lk(g_lock);

        /* If we've already detected, return cached result. */
        if (!g_detected_privileged_process) {
            DetectIsPrivilegedProcess();
        }

        /* Determine if we're privileged, and return. */
        return g_is_privileged_process;
    }

}
