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

static constexpr u32 Module_Sm = 21;

static constexpr Result ResultSmInsufficientProcesses = MAKERESULT(Module_Sm, 1);
static constexpr Result ResultSmInvalidClient         = MAKERESULT(Module_Sm, 2);
static constexpr Result ResultSmInsufficientSessions  = MAKERESULT(Module_Sm, 3);
static constexpr Result ResultSmAlreadyRegistered     = MAKERESULT(Module_Sm, 4);
static constexpr Result ResultSmInsufficientServices  = MAKERESULT(Module_Sm, 5);
static constexpr Result ResultSmInvalidServiceName    = MAKERESULT(Module_Sm, 6);
static constexpr Result ResultSmNotRegistered         = MAKERESULT(Module_Sm, 7);
static constexpr Result ResultSmNotAllowed            = MAKERESULT(Module_Sm, 8);
static constexpr Result ResultSmTooLargeAccessControl = MAKERESULT(Module_Sm, 9);
