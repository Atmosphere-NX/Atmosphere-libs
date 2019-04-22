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
#include <switch.h>
#include <cstdlib>

#include "hossynch.hpp"
#include "mitm/sm_mitm.h"

static inline void RebootToRcm() {
    SecmonArgs args = {0};
    args.X[0] = 0xC3000401; /* smcSetConfig */
    args.X[1] = 65001; /* Exosphere reboot */
    args.X[3] = 1; /* Perform reboot to RCM. */
    svcCallSecureMonitor(&args);
}

static inline void RebootToIramPayload() {
    SecmonArgs args = {0};
    args.X[0] = 0xC3000401; /* smcSetConfig */
    args.X[1] = 65001; /* Exosphere reboot */
    args.X[3] = 2; /* Perform reboot to payload at 0x40010000 in IRAM. */
    svcCallSecureMonitor(&args);
}

static inline void PerformShutdownSmc() {
    SecmonArgs args = {0};
    args.X[0] = 0xC3000401; /* smcSetConfig */
    args.X[1] = 65002; /* Exosphere shutdown */
    args.X[3] = 1; /* Perform shutdown. */
    svcCallSecureMonitor(&args);
}

static inline void CopyToIram(uintptr_t iram_addr, void *src_addr, size_t size) {
    SecmonArgs args = {0};
    args.X[0] = 0xF0000201;     /* smcAmsIramCopy */
    args.X[1] = (u64)src_addr;  /* DRAM address */
    args.X[2] = (u64)iram_addr; /* IRAM address */
    args.X[3] = size;           /* Amount to copy */
    args.X[4] = 1;              /* 1 = Write */
    svcCallSecureMonitor(&args);
}

static inline void CopyFromIram(void *dst_addr, uintptr_t iram_addr, size_t size) {
    SecmonArgs args = {0};
    args.X[0] = 0xF0000201;     /* smcAmsIramCopy */
    args.X[1] = (u64)dst_addr;  /* DRAM address */
    args.X[2] = (u64)iram_addr; /* IRAM address */
    args.X[3] = size;           /* Amount to copy */
    args.X[4] = 0;              /* 0 = Read */
    svcCallSecureMonitor(&args);
}

static inline Result SmcGetConfig(SplConfigItem config_item, u64 *out_config) {
    SecmonArgs args = {0};
    args.X[0] = 0xC3000002;        /* smcGetConfig */
    args.X[1] = (u64)config_item;  /* config item */

    Result rc = svcCallSecureMonitor(&args);
    if (R_SUCCEEDED(rc)) {
        if (args.X[0] == 0) {
            if (out_config) {
                *out_config = args.X[1];
            }
        } else {
            /* SPL result n = SMC result n */
            rc = MAKERESULT(26, args.X[0]);
        }
    }
    return rc;
}

static inline Result GetRcmBugPatched(bool *out) {
    u64 tmp = 0;
    Result rc = SmcGetConfig((SplConfigItem)65004, &tmp);
    if (R_SUCCEEDED(rc)) {
        *out = (tmp != 0);
    }
    return rc;
}

static inline bool IsRcmBugPatched() {
    bool rcm_bug_patched;
    if (R_FAILED(GetRcmBugPatched(&rcm_bug_patched))) {
        std::abort();
    }
    return rcm_bug_patched;
}

HosRecursiveMutex &GetSmSessionMutex();
HosRecursiveMutex &GetSmMitmSessionMutex();

template<typename F>
static void DoWithSmSession(F f) {
    std::scoped_lock<HosRecursiveMutex &> lk(GetSmSessionMutex());
    {
        Result rc;
        if (R_SUCCEEDED((rc = smInitialize()))) {
            f();
        } else {
            /* TODO: fatalSimple(rc); ? */
            std::abort();
        }
        smExit();
    }
}

template<typename F>
static void DoWithSmMitmSession(F f) {
    std::scoped_lock<HosRecursiveMutex &> lk(GetSmMitmSessionMutex());
    {
        Result rc;
        if (R_SUCCEEDED((rc = smMitMInitialize()))) {
            f();
        } else {
            /* TODO: fatalSimple(rc); ? */
            std::abort();
        }
        smMitMExit();
    }
}
