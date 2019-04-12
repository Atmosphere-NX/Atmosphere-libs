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
 
#include <mutex>
#include <switch.h>
#include <stratosphere.hpp>

extern "C" {
    __attribute__((weak)) u64 __stratosphere_title_id = 0;
    void __attribute__((weak)) __libstratosphere_exception_handler(AtmosphereFatalErrorContext *ctx);
    
    /* Redefine abort, so that it triggers these handlers. */
    void abort();
};

void StratosphereCrashHandler(ThreadExceptionDump *ctx) {
    AtmosphereFatalErrorContext ams_ctx;
    /* Convert thread dump to atmosphere dump. */
    {
        ams_ctx.magic = AtmosphereFatalErrorMagic;
        ams_ctx.error_desc = ctx->error_desc;
        ams_ctx.title_id = __stratosphere_title_id;
        for (size_t i = 0; i < AtmosphereFatalErrorNumGprs; i++) {
            ams_ctx.gprs[i] = ctx->cpu_gprs[i].x;
        }
        ams_ctx.fp = ctx->fp.x;
        ams_ctx.lr = ctx->lr.x;
        ams_ctx.sp = ctx->sp.x;
        ams_ctx.pc = ctx->pc.x;
        ams_ctx.pstate = ctx->pstate;
        ams_ctx.afsr0 = ctx->afsr0;
        ams_ctx.afsr1 = ctx->afsr1;
        ams_ctx.far = ctx->far.x;
        ams_ctx.report_identifier = armGetSystemTick();
    }
    
    /* Just call the user exception handler. */
    __libstratosphere_exception_handler(&ams_ctx);
}

/* Default exception handler behavior. */    
void __attribute__((weak)) __libstratosphere_exception_handler(AtmosphereFatalErrorContext *ctx) {
    Result rc = bpcAmsInitialize();
    if (R_SUCCEEDED(rc)) {
        rc = bpcAmsRebootToFatalError(ctx);
        bpcAmsExit();
    }
    if (R_FAILED(rc)) {
        std::abort();
    }
    while (1) { }
}

/* Custom abort handler, so that std::abort will trigger these. */
void abort() {
    /* Just perform a data abort. */
    while (true) {
        *((volatile u64 *)0x8) = 0xCAFEBABE;
    }
}