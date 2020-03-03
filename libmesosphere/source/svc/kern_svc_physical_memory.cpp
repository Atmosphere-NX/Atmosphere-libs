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

    Result SetHeapSize64(ams::svc::Address *out_address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcSetHeapSize64 was called.");
    }

    Result MapPhysicalMemory64(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcMapPhysicalMemory64 was called.");
    }

    Result UnmapPhysicalMemory64(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcUnmapPhysicalMemory64 was called.");
    }

    Result MapPhysicalMemoryUnsafe64(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcMapPhysicalMemoryUnsafe64 was called.");
    }

    Result UnmapPhysicalMemoryUnsafe64(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcUnmapPhysicalMemoryUnsafe64 was called.");
    }

    Result SetUnsafeLimit64(ams::svc::Size limit) {
        MESOSPHERE_PANIC("Stubbed SvcSetUnsafeLimit64 was called.");
    }

    /* ============================= 64From32 ABI ============================= */

    Result SetHeapSize64From32(ams::svc::Address *out_address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcSetHeapSize64From32 was called.");
    }

    Result MapPhysicalMemory64From32(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcMapPhysicalMemory64From32 was called.");
    }

    Result UnmapPhysicalMemory64From32(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcUnmapPhysicalMemory64From32 was called.");
    }

    Result MapPhysicalMemoryUnsafe64From32(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcMapPhysicalMemoryUnsafe64From32 was called.");
    }

    Result UnmapPhysicalMemoryUnsafe64From32(ams::svc::Address address, ams::svc::Size size) {
        MESOSPHERE_PANIC("Stubbed SvcUnmapPhysicalMemoryUnsafe64From32 was called.");
    }

    Result SetUnsafeLimit64From32(ams::svc::Size limit) {
        MESOSPHERE_PANIC("Stubbed SvcSetUnsafeLimit64From32 was called.");
    }

}
