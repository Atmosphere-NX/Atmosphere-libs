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

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 magic;
    u32 error_desc;
    u64 title_id;
    union {
        u64 gprs[32];
        struct {
            u64 _gprs[29];
            u64 fp;
            u64 lr;
            u64 sp;
        };
    };
    u64 pc;
    u64 padding;
    u32 pstate;
    u32 afsr0;
    u32 afsr1;
    u32 esr;
    u64 far;
    u64 report_identifier; /* Normally just system tick. */
} AtmosphereFatalErrorContext;

Result bpcAmsInitialize(void);
void bpcAmsExit(void);

Result bpcAmsRebootToFatalError(AtmosphereFatalErrorContext *ctx);

#ifdef __cplusplus
}
#endif