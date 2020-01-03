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
#pragma once
#include <mesosphere.hpp>

namespace ams::kern::smc {

    /* Types. */
    enum MemorySize {
        MemorySize_4GB = 0,
        MemorySize_6GB = 1,
        MemorySize_8GB = 2,
    };

    enum class ConfigItem : u32 {
        /* Standard config items. */
        DisableProgramVerification  = 1,
        DramId                      = 2,
        SecurityEngineIrqNumber     = 3,
        Version                     = 4,
        HardwareType                = 5,
        IsRetail                    = 6,
        IsRecoveryBoot              = 7,
        DeviceId                    = 8,
        BootReason                  = 9,
        MemoryMode                  = 10,
        IsDebugMode                 = 11,
        KernelConfiguration         = 12,
        IsChargerHiZModeEnabled     = 13,
        IsQuest                     = 14,
        RegulatorType               = 15,
        DeviceUniqueKeyGeneration   = 16,
        Package2Hash                = 17,

        /* Extension config items for exosphere. */
        ExosphereApiVersion     = 65000,
        ExosphereNeedsReboot    = 65001,
        ExosphereNeedsShutdown  = 65002,
        ExosphereGitCommitHash  = 65003,
        ExosphereHasRcmBugPatch = 65004,
    };

    enum class SmcResult {
        Success               = 0,
        NotImplemented        = 1,
        InvalidArgument       = 2,
        InProgress            = 3,
        NoAsyncOperation      = 4,
        InvalidAsyncOperation = 5,
        NotPermitted          = 6,
    };

    struct KernelConfiguration {
        using DebugFillMemory             = util::BitPack32::Field<0,                                 1, bool>;
        using EnableUserExceptionHandlers = util::BitPack32::Field<DebugFillMemory::Next,             1, bool>;
        using EnableUserPmuAccess         = util::BitPack32::Field<EnableUserExceptionHandlers::Next, 1, bool>;
        using IncreaseThreadResourceLimit = util::BitPack32::Field<EnableUserPmuAccess::Next,         1, bool>;
        using Reserved4                   = util::BitPack32::Field<IncreaseThreadResourceLimit::Next, 4, u32>;
        using UseSecureMonitorPanicCall   = util::BitPack32::Field<Reserved4::Next,                   1, bool>;
        using Reserved9                   = util::BitPack32::Field<UseSecureMonitorPanicCall::Next,   7, u32>;
        using MemorySize                  = util::BitPack32::Field<Reserved9::Next,                   2, smc::MemorySize>;
    };

    /* TODO: Rest of Secure Monitor API. */
    void NORETURN Panic(u32 color);

    namespace init {

        void GetConfig(u64 *out, size_t num_qwords, ConfigItem config_item);
        void GenerateRandomBytes(void *dst, size_t size);
        bool ReadWriteRegister(u32 *out, u64 address, u32 mask, u32 value);

    }

}