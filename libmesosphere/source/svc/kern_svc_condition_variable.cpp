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

namespace ams::kern::svc {

    /* =============================    Common    ============================= */

    namespace {



    }

    /* =============================    64 ABI    ============================= */

    Result WaitProcessWideKeyAtomic64(ams::svc::Address address, ams::svc::Address cv_key, uint32_t tag, int64_t timeout_ns) {
        MESOSPHERE_PANIC("Stubbed SvcWaitProcessWideKeyAtomic64 was called.");
    }

    void SignalProcessWideKey64(ams::svc::Address cv_key, int32_t count) {
        MESOSPHERE_PANIC("Stubbed SvcSignalProcessWideKey64 was called.");
    }

    /* ============================= 64From32 ABI ============================= */

    Result WaitProcessWideKeyAtomic64From32(ams::svc::Address address, ams::svc::Address cv_key, uint32_t tag, int64_t timeout_ns) {
        MESOSPHERE_PANIC("Stubbed SvcWaitProcessWideKeyAtomic64From32 was called.");
    }

    void SignalProcessWideKey64From32(ams::svc::Address cv_key, int32_t count) {
        MESOSPHERE_PANIC("Stubbed SvcSignalProcessWideKey64From32 was called.");
    }

}
