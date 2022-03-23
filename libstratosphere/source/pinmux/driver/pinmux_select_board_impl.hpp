/*
 * Copyright (c) Atmosphère-NX
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
#include <stratosphere.hpp>

#if defined(ATMOSPHERE_BOARD_NINTENDO_NX)

    #include "board/nintendo/nx/pinmux_board_driver_api.hpp"
    namespace ams::pinmux::driver::board {
        using namespace ams::pinmux::driver::board::nintendo::nx;
    }

#else

    // TODO: #error "Unknown board for pinmux driver"

    namespace ams::pinmux::driver::board {

        inline void Initialize() {
            AMS_ABORT("TODO");
        }

        inline void Finalize() {
            AMS_ABORT("TODO");
        }

        inline bool IsInitialized() {
            AMS_ABORT("TODO");
        }

        inline void SetInitialConfig() {
            AMS_ABORT("TODO");
        }

        inline void SetInitialDrivePadConfig() {
            AMS_ABORT("TODO");
        }

    }

#endif