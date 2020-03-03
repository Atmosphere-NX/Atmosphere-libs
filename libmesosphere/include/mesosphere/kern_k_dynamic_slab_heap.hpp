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
#include <mesosphere/kern_k_slab_heap.hpp>
#include <mesosphere/kern_k_page_group.hpp>
#include <mesosphere/kern_k_memory_block.hpp>

namespace ams::kern {

    namespace impl {

        class DynamicSlabHeapPage {
            private:
                u8 buffer[PageSize];
        };
        static_assert(sizeof(DynamicSlabHeapPage) == PageSize);

    };

    template<typename T>
    class KDynamicSlabHeap {
        NON_COPYABLE(KDynamicSlabHeap);
        NON_MOVEABLE(KDynamicSlabHeap);
        private:
            using Impl       = impl::KSlabHeapImpl;
            using PageBuffer = impl::DynamicSlabHeapPage;
        private:
            Impl impl;
            KDynamicSlabHeap<PageBuffer> *next_allocator;
            std::atomic<size_t> used;
            std::atomic<size_t> peak;
            std::atomic<size_t> count;
            KVirtualAddress address;
            size_t size;
        private:
            ALWAYS_INLINE Impl *GetImpl() {
                return std::addressof(this->impl);
            }
            ALWAYS_INLINE const Impl *GetImpl() const {
                return std::addressof(this->impl);
            }
        public:
            constexpr KDynamicSlabHeap() : impl(), next_allocator(), used(), peak(), count(), address(), size() { /* ... */ }

            constexpr KVirtualAddress GetAddress() const { return this->address; }
            constexpr size_t GetSize() const { return this->size; }
            constexpr size_t GetUsed() const { return this->used; }
            constexpr size_t GetPeak() const { return this->peak; }
            constexpr size_t GetCount() const { return this->count; }

            constexpr bool IsInRange(KVirtualAddress addr) const {
                return this->GetAddress() <= addr && addr <= this->GetAddress() + this->GetSize() - 1;
            }

            void Initialize(KVirtualAddress memory, size_t sz) {
                /* Set tracking fields. */
                this->address = memory;
                this->count   = sz / sizeof(T);
                this->size    = this->count * sizeof(T);

                /* Free blocks to memory. */
                u8 *cur = GetPointer<u8>(this->address + this->size);
                for (size_t i = 0; i < this->count; i++) {
                    cur -= sizeof(T);
                    this->GetImpl()->Free(cur);
                }
            }

            void Initialize(KDynamicSlabHeap<PageBuffer> *next) {
                this->next_allocator = next;
                this->address = next->GetAddress();
                this->size = next->GetSize();
            }

            T *Allocate() {
                T *allocated = reinterpret_cast<T *>(this->GetImpl()->Allocate());

                /* If we fail to allocate, try to get a new page from our next allocator. */
                if (AMS_UNLIKELY(allocated == nullptr)) {
                    if (this->next_allocator != nullptr) {
                        allocated = reinterpret_cast<T *>(this->next_allocator->Allocate());
                        if (allocated != nullptr) {
                            /* If we succeeded in getting a page, free the rest to our slab. */
                            for (size_t i = 1; i < sizeof(PageBuffer) / sizeof(T); i++) {
                                this->GetImpl()->Free(allocated + i);
                            }
                            this->count += sizeof(PageBuffer) / sizeof(T);
                        }
                    }
                }

                if (AMS_LIKELY(allocated != nullptr)) {
                    /* Construct the object. */
                    new (allocated) T();

                    /* Update our tracking. */
                    size_t used = ++this->used;
                    size_t peak = this->peak;
                    while (peak < used) {
                        if (this->peak.compare_exchange_weak(peak, used, std::memory_order_relaxed)) {
                            break;
                        }
                    }
                }

                return allocated;
            }

            void Free(T *t) {
                this->GetImpl()->Free(t);
                --this->used;
            }
    };

    class KDynamicPageManager     : public KDynamicSlabHeap<impl::DynamicSlabHeapPage>{};
    class KBlockInfoManager       : public KDynamicSlabHeap<KBlockInfo>{};
    class KMemoryBlockSlabManager : public KDynamicSlabHeap<KMemoryBlock>{};

}
