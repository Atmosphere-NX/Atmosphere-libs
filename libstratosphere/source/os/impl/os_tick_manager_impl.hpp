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
#pragma once
#include <stratosphere.hpp>

#ifdef ATMOSPHERE_OS_HORIZON
    #include "os_tick_manager_impl.os.horizon.hpp"
#else
    #error "Unknown OS for TickManagerImpl"
#endif

namespace ams::os::impl {

    /* Tick frequency must be less than INT64_MAX / 1 second. */
    static constexpr s64 MaxTickFrequency = (std::numeric_limits<s64>::max() / TimeSpan::FromSeconds(1).GetNanoSeconds()) - 1;

    class TickManager {
        private:
            TickManagerImpl impl;
        public:
            constexpr TickManager() : impl() { /* ... */ }

            ALWAYS_INLINE Tick GetTick() const {
                return this->impl.GetTick();
            }

            ALWAYS_INLINE Tick GetSystemTickOrdered() const {
                return this->impl.GetSystemTickOrdered();
            }

            ALWAYS_INLINE s64 GetTickFrequency() const {
                return this->impl.GetTickFrequency();
            }

            ALWAYS_INLINE s64 GetMaxTick() const {
                return this->impl.GetMaxTick();
            }

            ALWAYS_INLINE s64 GetMaxTimeSpanNs() const {
                return this->impl.GetMaxTimeSpanNs();
            }

            TimeSpan ConvertToTimeSpan(Tick tick) const;
            Tick     ConvertToTick(TimeSpan ts) const;
    };

}
