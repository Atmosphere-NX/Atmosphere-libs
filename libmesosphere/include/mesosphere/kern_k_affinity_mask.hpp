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
#include <mesosphere/kern_common.hpp>
#include <mesosphere/kern_select_cpu.hpp>

namespace ams::kern {

    class KAffinityMask {
        private:
            static constexpr u64 AllowedAffinityMask = (1ul << cpu::NumCores) - 1;
        private:
            u64 mask;
        private:
            static constexpr ALWAYS_INLINE u64 GetCoreBit(s32 core) {
                MESOSPHERE_ASSERT(0 <= core && core < static_cast<s32>(cpu::NumCores));
                return (1ul << core);
            }
        public:
            constexpr ALWAYS_INLINE KAffinityMask() : mask(0) { MESOSPHERE_ASSERT_THIS(); }

            constexpr ALWAYS_INLINE u64 GetAffinityMask() const { return this->mask; }

            constexpr ALWAYS_INLINE void SetAffinityMask(u64 new_mask) {
                MESOSPHERE_ASSERT((new_mask & ~AllowedAffinityMask) == 0);
                this->mask = new_mask;
            }

            constexpr ALWAYS_INLINE bool GetAffinity(s32 core) const {
                return this->mask & GetCoreBit(core);
            }

            constexpr ALWAYS_INLINE void SetAffinity(s32 core, bool set) {
                MESOSPHERE_ASSERT(0 <= core && core < static_cast<s32>(cpu::NumCores));

                if (set) {
                    this->mask |= GetCoreBit(core);
                } else {
                    this->mask &= ~GetCoreBit(core);
                }
            }

            constexpr ALWAYS_INLINE void SetAll() {
                this->mask = AllowedAffinityMask;
            }
    };

}
