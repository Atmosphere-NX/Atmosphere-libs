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

    Result OutputDebugString64(KUserPointer<const char *> debug_str, ams::svc::Size len) {
        MESOSPHERE_PANIC("Stubbed SvcOutputDebugString64 was called.");
    }

    /* ============================= 64From32 ABI ============================= */

    Result OutputDebugString64From32(KUserPointer<const char *> debug_str, ams::svc::Size len) {
        MESOSPHERE_PANIC("Stubbed SvcOutputDebugString64From32 was called.");
    }

}
