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

/* Please note: These results are all custom, and not official. */

static constexpr u32 Module_Atmosphere = 444;

/* Result 1-1000 reserved for Atmosphere. */
static constexpr Result ResultAtmosphereExosphereNotPresent = MAKERESULT(Module_Atmosphere, 1);
static constexpr Result ResultAtmosphereVersionMismatch     = MAKERESULT(Module_Atmosphere, 2);

/* Results 1000-2000 reserved for Atmosphere Mitm. */
static constexpr Result ResultAtmosphereMitmShouldForwardToSession =  MAKERESULT(Module_Atmosphere, 1000);
static constexpr Result ResultAtmosphereMitmProcessNotAssociated =  MAKERESULT(Module_Atmosphere, 1100);

