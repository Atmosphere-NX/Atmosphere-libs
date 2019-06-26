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
#include <set>
#include <switch.h>
#include <stratosphere.hpp>
#include <stratosphere/pm.hpp>

#include "pm_ams.h"

namespace sts::pm::info {

    namespace {

        /* Global lock. */
        HosMutex g_info_lock;
        std::set<u64> g_cached_launched_titles;

    }

    /* Information API. */
    Result GetTitleId(u64 *out_title_id, u64 process_id) {
        std::scoped_lock<HosMutex> lk(g_info_lock);

        return pminfoGetTitleId(out_title_id, process_id);
    }

    Result GetProcessId(u64 *out_process_id, u64 title_id) {
        std::scoped_lock<HosMutex> lk(g_info_lock);

        return pminfoAtmosphereGetProcessId(out_process_id, title_id);
    }

    Result __attribute__((weak)) HasLaunchedTitle(bool *out, u64 title_id) {
        std::scoped_lock<HosMutex> lk(g_info_lock);

        if (g_cached_launched_titles.find(title_id) != g_cached_launched_titles.end()) {
            *out = true;
            return ResultSuccess;
        }

        bool has_launched = false;
        R_TRY(pminfoAtmosphereHasLaunchedTitle(&has_launched, title_id));
        if (has_launched) {
            g_cached_launched_titles.insert(title_id);
        }

        *out = has_launched;
        return ResultSuccess;
    }

    bool HasLaunchedTitle(u64 title_id) {
        bool has_launched = false;
        R_ASSERT(HasLaunchedTitle(&has_launched, title_id));
        return has_launched;
    }

}
