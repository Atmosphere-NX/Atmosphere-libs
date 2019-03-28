/*
 * Copyright (c) 2018 Atmosphère-NX
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

static constexpr u32 Module_Kernel = 1;

static constexpr Result ResultKernelOutOfSessions                = MAKERESULT(Module_Kernel, 7);

static constexpr Result ResultKernelInvalidCapabilityDescriptor  = MAKERESULT(Module_Kernel, 14);

static constexpr Result ResultKernelNotImplemented               = MAKERESULT(Module_Kernel, 33);
static constexpr Result ResultKernelThreadTerminating            = MAKERESULT(Module_Kernel, 59);

static constexpr Result ResultKernelOutOfDebugEvents             = MAKERESULT(Module_Kernel, 70);

static constexpr Result ResultKernelInvalidSize                  = MAKERESULT(Module_Kernel, 101);
static constexpr Result ResultKernelInvalidAddress               = MAKERESULT(Module_Kernel, 102);
static constexpr Result ResultKernelResourceExhausted            = MAKERESULT(Module_Kernel, 103);
static constexpr Result ResultKernelOutOfMemory                  = MAKERESULT(Module_Kernel, 104);
static constexpr Result ResultKernelOutOfHandles                 = MAKERESULT(Module_Kernel, 105);
static constexpr Result ResultKernelInvalidMemoryState           = MAKERESULT(Module_Kernel, 106);
static constexpr Result ResultKernelInvalidMemoryPermissions     = MAKERESULT(Module_Kernel, 108);
static constexpr Result ResultKernelInvalidMemoryRange           = MAKERESULT(Module_Kernel, 110);
static constexpr Result ResultKernelInvalidPriority              = MAKERESULT(Module_Kernel, 112);
static constexpr Result ResultKernelInvalidCoreId                = MAKERESULT(Module_Kernel, 113);
static constexpr Result ResultKernelInvalidHandle                = MAKERESULT(Module_Kernel, 114);
static constexpr Result ResultKernelInvalidUserBuffer            = MAKERESULT(Module_Kernel, 115);
static constexpr Result ResultKernelInvalidCombination           = MAKERESULT(Module_Kernel, 116);
static constexpr Result ResultKernelTimedOut                     = MAKERESULT(Module_Kernel, 117);
static constexpr Result ResultKernelCancelled                    = MAKERESULT(Module_Kernel, 118);
static constexpr Result ResultKernelOutOfRange                   = MAKERESULT(Module_Kernel, 119);
static constexpr Result ResultKernelInvalidEnumValue             = MAKERESULT(Module_Kernel, 120);
static constexpr Result ResultKernelNotFound                     = MAKERESULT(Module_Kernel, 121);
static constexpr Result ResultKernelAlreadyExists                = MAKERESULT(Module_Kernel, 122);
static constexpr Result ResultKernelConnectionClosed             = MAKERESULT(Module_Kernel, 123);
static constexpr Result ResultKernelUnhandledUserInterrupt       = MAKERESULT(Module_Kernel, 124);
static constexpr Result ResultKernelInvalidState                 = MAKERESULT(Module_Kernel, 125);
static constexpr Result ResultKernelReservedValue                = MAKERESULT(Module_Kernel, 126);
static constexpr Result ResultKernelInvalidHwBreakpoint          = MAKERESULT(Module_Kernel, 127);
static constexpr Result ResultKernelFatalUserException           = MAKERESULT(Module_Kernel, 128);
static constexpr Result ResultKernelOwnedByAnotherProcess        = MAKERESULT(Module_Kernel, 129);
static constexpr Result ResultKernelConnectionRefused            = MAKERESULT(Module_Kernel, 131);
static constexpr Result ResultKernelOutOfResource                = MAKERESULT(Module_Kernel, 132);

static constexpr Result ResultKernelIpcMapFailed                 = MAKERESULT(Module_Kernel, 259);
static constexpr Result ResultKernelIpcCmdBufTooSmall            = MAKERESULT(Module_Kernel, 260);

static constexpr Result ResultKernelNotDebugged                  = MAKERESULT(Module_Kernel, 520);
