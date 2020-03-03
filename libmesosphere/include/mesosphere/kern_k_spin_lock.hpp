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
#include <vapours.hpp>
#include "kern_panic.hpp"

#if defined(ATMOSPHERE_ARCH_ARM64)

    #include <mesosphere/arch/arm64/kern_k_spin_lock.hpp>
    namespace ams::kern {
        using ams::kern::arm64::KAlignedSpinLock;
        using ams::kern::arm64::KNotAlignedSpinLock;
        using ams::kern::arm64::KSpinLock;
    }

#else

    #error "Unknown architecture for KInterruptManager"

#endif


namespace ams::kern {

    class KScopedSpinLock {
        private:
            KSpinLock *lock_ptr;
        public:
            explicit ALWAYS_INLINE KScopedSpinLock(KSpinLock *l) : lock_ptr(l) {
                this->lock_ptr->Lock();
            }
            ALWAYS_INLINE ~KScopedSpinLock() {
                this->lock_ptr->Unlock();
            }

            explicit ALWAYS_INLINE KScopedSpinLock(KSpinLock &l) : KScopedSpinLock(std::addressof(l)) { /* ... */ }
    };

    class KScopedAlignedSpinLock {
        private:
            KAlignedSpinLock *lock_ptr;
        public:
            explicit ALWAYS_INLINE KScopedAlignedSpinLock(KAlignedSpinLock *l) : lock_ptr(l) {
                this->lock_ptr->Lock();
            }
            ALWAYS_INLINE ~KScopedAlignedSpinLock() {
                this->lock_ptr->Unlock();
            }
            explicit ALWAYS_INLINE KScopedAlignedSpinLock(KAlignedSpinLock &l) : KScopedAlignedSpinLock(std::addressof(l)) { /* ... */ }
    };

    class KScopedNotAlignedSpinLock {
        private:
            KNotAlignedSpinLock *lock_ptr;
        public:
            explicit ALWAYS_INLINE KScopedNotAlignedSpinLock(KNotAlignedSpinLock *l) : lock_ptr(l) {
                this->lock_ptr->Lock();
            }
            ALWAYS_INLINE ~KScopedNotAlignedSpinLock() {
                this->lock_ptr->Unlock();
            }

            explicit ALWAYS_INLINE KScopedNotAlignedSpinLock(KNotAlignedSpinLock &l) : KScopedNotAlignedSpinLock(std::addressof(l)) { /* ... */ }
    };

}
