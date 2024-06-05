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
#include <vapours.hpp>
#include <stratosphere/fssystem/fssystem_nca_file_system_driver.hpp>
#include <stratosphere/ldr/ldr_platform_id.hpp>

namespace ams::fssystem {

    const ::ams::fssystem::NcaCryptoConfiguration *GetNcaCryptoConfiguration(bool prod);

    void SetUpKekAccessKeys(bool prod);

    void InvalidateHardwareAesKey();

    bool IsValidSignatureKeyGeneration(ldr::PlatformId platform, size_t key_generation);

    const u8 *GetAcidSignatureKeyModulus(ldr::PlatformId platform, bool prod, size_t key_generation, bool unk_unused);
    size_t GetAcidSignatureKeyModulusSize(ldr::PlatformId platform, bool unk_unused);

    const u8 *GetAcidSignatureKeyPublicExponent();

    constexpr inline size_t AcidSignatureKeyPublicExponentSize = NcaCryptoConfiguration::Rsa2048KeyPublicExponentSize;

}
