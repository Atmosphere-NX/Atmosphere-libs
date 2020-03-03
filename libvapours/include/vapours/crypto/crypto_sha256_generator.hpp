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
#include <vapours/common.hpp>
#include <vapours/assert.hpp>
#include <vapours/util.hpp>
#include <vapours/crypto/impl/crypto_sha256_impl.hpp>

namespace ams::crypto {

    class Sha256Generator {
        private:
            using Impl = impl::Sha256Impl;
        public:
            static constexpr size_t HashSize  = Impl::HashSize;
            static constexpr size_t BlockSize = Impl::BlockSize;

            static constexpr inline u8 Asn1Identifier[] = {
                0x30, 0x31, /* Sequence, size 0x31 */
                    0x30, 0x0D, /* Sequence, size 0x0D */
                        0x06, 0x09, /* Object Identifier */
                            0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, /* SHA-256 */
                        0x00, /* Null */
                    0x04, 0x20, /* Octet string, size 0x20 */
            };
            static constexpr size_t Asn1IdentifierSize = util::size(Asn1Identifier);
        private:
            Impl impl;
        public:
            Sha256Generator() { /* ... */ }

            void Initialize() {
                this->impl.Initialize();
            }

            void Update(const void *data, size_t size) {
                this->impl.Update(data, size);
            }

            void GetHash(void *dst, size_t size) {
                this->impl.GetHash(dst, size);
            }
    };

    void GenerateSha256Hash(void *dst, size_t dst_size, const void *src, size_t src_size);

}
