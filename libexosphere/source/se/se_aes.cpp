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
#include <exosphere.hpp>
#include "se_execute.hpp"

namespace ams::se {

    namespace {

        constexpr inline int AesKeySizeMax = 256 / BITSIZEOF(u8);

        enum AesMode {
            AesMode_Aes128 = ((SE_CONFIG_ENC_MODE_AESMODE_KEY128 << SE_CONFIG_ENC_MODE_OFFSET) | (SE_CONFIG_DEC_MODE_AESMODE_KEY128 << SE_CONFIG_DEC_MODE_OFFSET)) >> SE_CONFIG_DEC_MODE_OFFSET,
            AesMode_Aes192 = ((SE_CONFIG_ENC_MODE_AESMODE_KEY192 << SE_CONFIG_ENC_MODE_OFFSET) | (SE_CONFIG_DEC_MODE_AESMODE_KEY192 << SE_CONFIG_DEC_MODE_OFFSET)) >> SE_CONFIG_DEC_MODE_OFFSET,
            AesMode_Aes256 = ((SE_CONFIG_ENC_MODE_AESMODE_KEY256 << SE_CONFIG_ENC_MODE_OFFSET) | (SE_CONFIG_DEC_MODE_AESMODE_KEY256 << SE_CONFIG_DEC_MODE_OFFSET)) >> SE_CONFIG_DEC_MODE_OFFSET,
        };

        enum MemoryInterface {
            MemoryInterface_Ahb = SE_CRYPTO_CONFIG_MEMIF_AHB,
            MemoryInterface_Mc  = SE_CRYPTO_CONFIG_MEMIF_MCCIF,
        };

        constexpr inline u32 AesConfigEcb = reg::Encode(SE_REG_BITS_VALUE(CRYPTO_CONFIG_CTR_CNTN,             0),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_KEYSCH_BYPASS,  DISABLE),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_IV_SELECT,     ORIGINAL),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_VCTRAM_SEL,      MEMORY),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_INPUT_SEL,       MEMORY),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_XOR_POS,         BYPASS),
                                                        SE_REG_BITS_ENUM (CRYPTO_CONFIG_HASH_ENB,       DISABLE));

        void SetConfig(volatile SecurityEngineRegisters *SE, bool encrypt, SE_CONFIG_DST dst) {
            reg::Write(SE->SE_CONFIG, SE_REG_BITS_ENUM    (CONFIG_ENC_MODE, AESMODE_KEY128),
                                      SE_REG_BITS_ENUM    (CONFIG_DEC_MODE, AESMODE_KEY128),
                                      SE_REG_BITS_ENUM_SEL(CONFIG_ENC_ALG,          encrypt, AES_ENC,     NOP),
                                      SE_REG_BITS_ENUM_SEL(CONFIG_DEC_ALG,          encrypt,     NOP, AES_DEC),
                                      SE_REG_BITS_VALUE   (CONFIG_DST,                  dst));
        }

        void SetAesConfig(volatile SecurityEngineRegisters *SE, int slot, bool encrypt, u32 config) {
            const u32 encoded = reg::Encode(SE_REG_BITS_ENUM    (CRYPTO_CONFIG_MEMIF,        AHB),
                                            SE_REG_BITS_VALUE   (CRYPTO_CONFIG_KEY_INDEX,   slot),
                                            SE_REG_BITS_ENUM_SEL(CRYPTO_CONFIG_CORE_SEL,  encrypt, ENCRYPT, DECRYPT));

            reg::Write(SE->SE_CRYPTO_CONFIG, (config | encoded));
        }

        void SetBlockCount(volatile SecurityEngineRegisters *SE, int count) {
            reg::Write(SE->SE_CRYPTO_LAST_BLOCK, count - 1);
        }

        void UpdateAesMode(volatile SecurityEngineRegisters *SE, AesMode mode) {
            reg::ReadWrite(SE->SE_CONFIG, REG_BITS_VALUE(16, 16, mode));
        }

        // void UpdateMemoryInterface(volatile SecurityEngineRegisters *SE, MemoryInterface memif) {
        //     reg::ReadWrite(SE->SE_CRYPTO_CONFIG, SE_REG_BITS_VALUE(CRYPTO_CONFIG_MEMIF, memif));
        // }

        void SetEncryptedAesKey(int dst_slot, int kek_slot, const void *key, size_t key_size, AesMode mode) {
            AMS_ABORT_UNLESS(key_size <= AesKeySizeMax);
            AMS_ABORT_UNLESS(0 <= dst_slot && dst_slot < AesKeySlotCount);
            AMS_ABORT_UNLESS(0 <= kek_slot && kek_slot < AesKeySlotCount);

            /* Get the engine. */
            auto *SE = GetRegisters();

            /* Configure for single AES ECB decryption to key table. */
            SetConfig(SE, false, SE_CONFIG_DST_KEYTABLE);
            SetAesConfig(SE, kek_slot, false, AesConfigEcb);
            UpdateAesMode(SE, mode);
            SetBlockCount(SE, 1);

            /* Select the destination keyslot. */
            reg::Write(SE->SE_CRYPTO_KEYTABLE_DST, SE_REG_BITS_VALUE(CRYPTO_KEYTABLE_DST_KEY_INDEX, dst_slot), SE_REG_BITS_ENUM(CRYPTO_KEYTABLE_DST_WORD_QUAD, KEYS_0_3));

            /* Ensure that the se sees the keydata we want it to. */
            hw::FlushDataCache(key, key_size);
            hw::DataSynchronizationBarrierInnerShareable();

            /* Execute the operation. */
            ExecuteOperation(SE, SE_OPERATION_OP_START, nullptr, 0, key, key_size);
        }

        void EncryptAes(void *dst, size_t dst_size, int slot, const void *src, size_t src_size, AesMode mode) {
            /* If nothing to decrypt, succeed. */
            if (src_size == 0) { return; }

            /* Validate input. */
            AMS_ABORT_UNLESS(dst_size == AesBlockSize);
            AMS_ABORT_UNLESS(src_size == AesBlockSize);
            AMS_ABORT_UNLESS(0 <= slot && slot < AesKeySlotCount);

            /* Get the engine. */
            auto *SE = GetRegisters();

            /* Configure for AES-ECB encryption to memory. */
            SetConfig(SE, true, SE_CONFIG_DST_MEMORY);
            SetAesConfig(SE, slot, true, AesConfigEcb);
            UpdateAesMode(SE, mode);

            /* Execute the operation. */
            ExecuteOperationSingleBlock(SE, dst, dst_size, src, src_size);
        }

    }

    void ClearAesKeySlot(int slot) {
        /* Validate the key slot. */
        AMS_ABORT_UNLESS(0 <= slot && slot < AesKeySlotCount);

        /* Get the engine. */
        auto *SE = GetRegisters();

        for (int i = 0; i < 16; ++i) {
            /* Select the keyslot. */
            reg::Write(SE->SE_CRYPTO_KEYTABLE_ADDR, SE_REG_BITS_VALUE(CRYPTO_KEYTABLE_ADDR_KEYIV_KEY_SLOT, slot), SE_REG_BITS_VALUE(CRYPTO_KEYTABLE_ADDR_KEYIV_WORD, i));

            /* Write the data. */
            SE->SE_CRYPTO_KEYTABLE_DATA = 0;
        }
    }

    void LockAesKeySlot(int slot, u32 flags) {
        /* Validate the key slot. */
        AMS_ABORT_UNLESS(0 <= slot && slot < AesKeySlotCount);

        /* Get the engine. */
        auto *SE = GetRegisters();

        /* Set non per-key flags. */
        if ((flags & ~KeySlotLockFlags_PerKey) != 0) {
            /* TODO: KeySlotLockFlags_DstKeyTableOnly is Mariko-only. How should we handle this? */
            /* TODO: Mariko bit support. */
            reg::ReadWrite(SE->SE_CRYPTO_KEYTABLE_ACCESS[slot], REG_BITS_VALUE(0, 7, ~flags));
        }

        /* Set per-key flag. */
        if ((flags & KeySlotLockFlags_PerKey) != 0) {
            reg::ReadWrite(SE->SE_CRYPTO_SECURITY_PERKEY, REG_BITS_VALUE(slot, 1, 0));
        }
    }

    void SetAesKey(int slot, const void *key, size_t key_size) {
        /* Validate the key slot and key size. */
        AMS_ABORT_UNLESS(0 <= slot && slot < AesKeySlotCount);
        AMS_ABORT_UNLESS(key_size <= AesKeySizeMax);

        /* Get the engine. */
        auto *SE = GetRegisters();

        /* Set each key word in order. */
        const u32 *key_u32  = static_cast<const u32 *>(key);
        const int num_words = key_size / sizeof(u32);
        for (int i = 0; i < num_words; ++i) {
            /* Select the keyslot. */
            reg::Write(SE->SE_CRYPTO_KEYTABLE_ADDR, SE_REG_BITS_VALUE(CRYPTO_KEYTABLE_ADDR_KEYIV_KEY_SLOT,   slot),
                                                    SE_REG_BITS_ENUM (CRYPTO_KEYTABLE_ADDR_KEYIV_KEYIV_SEL,   KEY),
                                                    SE_REG_BITS_VALUE(CRYPTO_KEYTABLE_ADDR_KEYIV_KEY_WORD,      i));

            /* Set the key word. */
            SE->SE_CRYPTO_KEYTABLE_DATA = *(key_u32++);
        }
    }

    void SetEncryptedAesKey128(int dst_slot, int kek_slot, const void *key, size_t key_size) {
        return SetEncryptedAesKey(dst_slot, kek_slot, key, key_size, AesMode_Aes128);
    }

    void SetEncryptedAesKey256(int dst_slot, int kek_slot, const void *key, size_t key_size) {
        return SetEncryptedAesKey(dst_slot, kek_slot, key, key_size, AesMode_Aes256);
    }

    void EncryptAes128(void *dst, size_t dst_size, int slot, const void *src, size_t src_size) {
        return EncryptAes(dst, dst_size, slot, src, src_size, AesMode_Aes128);
    }

    void DecryptAes128(void *dst, size_t dst_size, int slot, const void *src, size_t src_size) {
        /* If nothing to decrypt, succeed. */
        if (src_size == 0) { return; }

        /* Validate input. */
        AMS_ABORT_UNLESS(dst_size == AesBlockSize);
        AMS_ABORT_UNLESS(src_size == AesBlockSize);
        AMS_ABORT_UNLESS(0 <= slot && slot < AesKeySlotCount);

        /* Get the engine. */
        auto *SE = GetRegisters();

        /* Configure for AES-ECB decryption to memory. */
        SetConfig(SE, false, SE_CONFIG_DST_MEMORY);
        SetAesConfig(SE, slot, false, AesConfigEcb);

        ExecuteOperationSingleBlock(SE, dst, dst_size, src, src_size);
    }

}
