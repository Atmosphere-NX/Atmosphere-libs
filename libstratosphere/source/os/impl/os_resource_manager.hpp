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
#include "os_rng_manager_impl.hpp"
#include "os_tick_manager_impl.hpp"

namespace ams::os::impl {

    class OsResourceManager {
        private:
            RngManager  rng_manager{};
            /* TODO */
            TickManager tick_manager{};
            /* TODO */
        public:
            constexpr OsResourceManager() = default;

            constexpr ALWAYS_INLINE RngManager &GetRngManager() { return this->rng_manager; }
            constexpr ALWAYS_INLINE TickManager &GetTickManager() { return this->tick_manager; }
    };

    class ResourceManagerHolder {
        private:
            static /* TODO: C++20 constinit */ OsResourceManager s_resource_manager;
        private:
            constexpr ResourceManagerHolder() { /* ... */ }
        public:
            static ALWAYS_INLINE OsResourceManager &GetResourceManagerInstance() {
                return s_resource_manager;
            }
    };

    ALWAYS_INLINE OsResourceManager &GetResourceManager() {
        return ResourceManagerHolder::GetResourceManagerInstance();
    }

}
