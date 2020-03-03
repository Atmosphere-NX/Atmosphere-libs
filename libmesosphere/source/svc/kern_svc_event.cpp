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

    Result SignalEvent64(ams::svc::Handle event_handle) {
        MESOSPHERE_PANIC("Stubbed SvcSignalEvent64 was called.");
    }

    Result ClearEvent64(ams::svc::Handle event_handle) {
        MESOSPHERE_PANIC("Stubbed SvcClearEvent64 was called.");
    }

    Result CreateEvent64(ams::svc::Handle *out_write_handle, ams::svc::Handle *out_read_handle) {
        MESOSPHERE_PANIC("Stubbed SvcCreateEvent64 was called.");
    }

    /* ============================= 64From32 ABI ============================= */

    Result SignalEvent64From32(ams::svc::Handle event_handle) {
        MESOSPHERE_PANIC("Stubbed SvcSignalEvent64From32 was called.");
    }

    Result ClearEvent64From32(ams::svc::Handle event_handle) {
        MESOSPHERE_PANIC("Stubbed SvcClearEvent64From32 was called.");
    }

    Result CreateEvent64From32(ams::svc::Handle *out_write_handle, ams::svc::Handle *out_read_handle) {
        MESOSPHERE_PANIC("Stubbed SvcCreateEvent64From32 was called.");
    }

}
