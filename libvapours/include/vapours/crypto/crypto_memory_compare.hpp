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
#include <vapours/defines.hpp>
#include <vapours/util.hpp>

#ifdef ATMOSPHERE_ARCH_ARM64

#include <vapours/crypto/impl/crypto_memory_compare.arch.arm64.hpp>

#else

#error "Unknown architecture for crypto::IsSameBytes"

#endif

namespace ams::crypto {

    bool IsSameBytes(const void *lhs, const void *rhs, size_t size) {
        return impl::IsSameBytes(lhs, rhs, size);
    }

}
