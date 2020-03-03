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
#include <mesosphere/kern_k_typed_address.hpp>

namespace ams::kern::arch::arm64 {

    constexpr size_t L1BlockSize           = 1_GB;
    constexpr size_t L1ContiguousBlockSize = 0x10 * L1BlockSize;
    constexpr size_t L2BlockSize           = 2_MB;
    constexpr size_t L2ContiguousBlockSize = 0x10 * L2BlockSize;
    constexpr size_t L3BlockSize           = PageSize;
    constexpr size_t L3ContiguousBlockSize = 0x10 * L3BlockSize;

    class PageTableEntry {
        public:
            struct InvalidTag{};

            enum Permission : u64 {
                Permission_KernelRWX = ((0ul << 53) | (1ul << 54) | (0ul << 6)),
                Permission_KernelRX  = ((0ul << 53) | (1ul << 54) | (2ul << 6)),
                Permission_KernelR   = ((1ul << 53) | (1ul << 54) | (2ul << 6)),
                Permission_KernelRW  = ((1ul << 53) | (1ul << 54) | (0ul << 6)),

                Permission_UserRX    = ((1ul << 53) | (0ul << 54) | (3ul << 6)),
                Permission_UserR     = ((1ul << 53) | (1ul << 54) | (3ul << 6)),
                Permission_UserRW    = ((1ul << 53) | (1ul << 54) | (1ul << 6)),
            };

            enum Shareable : u64 {
                Shareable_NonShareable   = (0 << 8),
                Shareable_OuterShareable = (2 << 8),
                Shareable_InnerShareable = (3 << 8),
            };

            /* Official attributes are: */
            /*    0x00, 0x04, 0xFF, 0x44. 4-7 are unused. */
            enum PageAttribute : u64 {
                PageAttribute_Device_nGnRnE            = (0 << 2),
                PageAttribute_Device_nGnRE             = (1 << 2),
                PageAttribute_NormalMemory             = (2 << 2),
                PageAttribute_NormalMemoryNotCacheable = (3 << 2),
            };

            enum AccessFlag : u64 {
                AccessFlag_NotAccessed = (0 << 10),
                AccessFlag_Accessed    = (1 << 10),
            };

            enum Type : u64 {
                Type_None    = 0x0,
                Type_L1Block = 0x1,
                Type_L1Table = 0x3,
                Type_L2Block = 0x1,
                Type_L2Table = 0x3,
                Type_L3Block = 0x3,
            };

            enum ContigType : u64 {
                ContigType_NotContiguous = (0x0ul << 52),
                ContigType_Contiguous    = (0x1ul << 52),
            };
        protected:
            u64 attributes;
        public:
            /* Take in a raw attribute. */
            constexpr ALWAYS_INLINE PageTableEntry() : attributes() { /* ... */ }
            constexpr ALWAYS_INLINE PageTableEntry(u64 attr) : attributes(attr) { /* ... */ }

            constexpr ALWAYS_INLINE PageTableEntry(InvalidTag) : attributes(0) { /* ... */ }

            /* Extend a previous attribute. */
            constexpr ALWAYS_INLINE PageTableEntry(const PageTableEntry &rhs, u64 new_attr) : attributes(rhs.attributes | new_attr) { /* ... */ }

            /* Construct a new attribute. */
            constexpr ALWAYS_INLINE PageTableEntry(Permission perm, PageAttribute p_a, Shareable share)
                : attributes(static_cast<u64>(perm) | static_cast<u64>(AccessFlag_Accessed) | static_cast<u64>(p_a) | static_cast<u64>(share))
            {
                /* ... */
            }
        protected:
            constexpr ALWAYS_INLINE u64 GetBits(size_t offset, size_t count) const {
                return (this->attributes >> offset) & ((1ul << count) - 1);
            }

            constexpr ALWAYS_INLINE u64 SelectBits(size_t offset, size_t count) const {
                return this->attributes & (((1ul << count) - 1) << offset);
            }

            constexpr ALWAYS_INLINE void SetBits(size_t offset, size_t count, u64 value) {
                const u64 mask = ((1ul << count) - 1) << offset;
                this->attributes &= ~mask;
                this->attributes |= (value & (mask >> offset)) << offset;
            }

            constexpr ALWAYS_INLINE void SetBitsDirect(size_t offset, size_t count, u64 value) {
                const u64 mask = ((1ul << count) - 1) << offset;
                this->attributes &= ~mask;
                this->attributes |= (value & mask);
            }

            constexpr ALWAYS_INLINE void SetBit(size_t offset, bool enabled) {
                const u64 mask = 1ul << offset;
                if (enabled) {
                    this->attributes |= mask;
                } else {
                    this->attributes &= ~mask;
                }
            }
        public:
            constexpr ALWAYS_INLINE bool IsContiguousAllowed()       const { return this->GetBits(55, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsUserExecuteNever()        const { return this->GetBits(54, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsPrivilegedExecuteNever()  const { return this->GetBits(53, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsContiguous()              const { return this->GetBits(52, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsGlobal()                  const { return this->GetBits(11, 1) == 0; }
            constexpr ALWAYS_INLINE AccessFlag GetAccessFlag()       const { return static_cast<AccessFlag>(this->GetBits(10, 1)); }
            constexpr ALWAYS_INLINE Shareable GetShareable()         const { return static_cast<Shareable>(this->GetBits(8, 2)); }
            constexpr ALWAYS_INLINE PageAttribute GetPageAttribute() const { return static_cast<PageAttribute>(this->GetBits(2, 3)); }
            constexpr ALWAYS_INLINE bool IsReadOnly()                const { return this->GetBits(7, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsUserAccessible()          const { return this->GetBits(6, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsNonSecure()               const { return this->GetBits(5, 1) != 0; }
            constexpr ALWAYS_INLINE bool IsBlock()                   const { return this->GetBits(0, 2) == 0x1; }
            constexpr ALWAYS_INLINE bool IsTable()                   const { return this->GetBits(0, 2) == 0x3; }

            constexpr ALWAYS_INLINE decltype(auto) SetContiguousAllowed(bool en)      { this->SetBit(55, !en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetUserExecuteNever(bool en)       { this->SetBit(54, en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetPrivilegedExecuteNever(bool en) { this->SetBit(53, en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetContiguous(bool en)             { this->SetBit(52, en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetGlobal(bool en)                 { this->SetBit(11, !en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetAccessFlag(AccessFlag f)        { this->SetBitsDirect(10, 1, f); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetShareable(Shareable s)          { this->SetBitsDirect(8, 2, s); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetReadOnly(bool en)               { this->SetBit(7, en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetUserAccessible(bool en)         { this->SetBit(6, en); return *this; }
            constexpr ALWAYS_INLINE decltype(auto) SetPageAttribute(PageAttribute a)  { this->SetBitsDirect(2, 3, a); return *this; }

            constexpr ALWAYS_INLINE u64 GetEntryTemplate() const {
                constexpr u64 Mask = (0xFFF0000000000FFFul & ~u64(0x3ul | (0x1ul << 52)));
                return this->attributes & Mask;
            }

            constexpr ALWAYS_INLINE bool Is(u64 attr) const {
                return this->attributes == attr;
            }

        protected:
            constexpr ALWAYS_INLINE u64 GetRawAttributes() const {
                return this->attributes;
            }
    };

    static_assert(sizeof(PageTableEntry) == sizeof(u64));

    constexpr inline PageTableEntry InvalidPageTableEntry = PageTableEntry(PageTableEntry::InvalidTag{});

    constexpr inline size_t MaxPageTableEntries = PageSize / sizeof(PageTableEntry);

    class L1PageTableEntry : public PageTableEntry {
        public:
            constexpr ALWAYS_INLINE L1PageTableEntry(InvalidTag) : PageTableEntry(InvalidTag{}) { /* ... */ }

            constexpr ALWAYS_INLINE L1PageTableEntry(KPhysicalAddress phys_addr, bool pxn)
                : PageTableEntry((0x3ul << 60) | (static_cast<u64>(pxn) << 59) | GetInteger(phys_addr) | 0x3)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE L1PageTableEntry(KPhysicalAddress phys_addr, bool is_kernel, bool pxn)
                : PageTableEntry(((is_kernel ? 0x3ul : 0) << 60) | (static_cast<u64>(pxn) << 59) | GetInteger(phys_addr) | 0x3)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE L1PageTableEntry(KPhysicalAddress phys_addr, const PageTableEntry &attr, bool contig)
                : PageTableEntry(attr, (static_cast<u64>(contig) << 52) | GetInteger(phys_addr) | 0x1)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE KPhysicalAddress GetBlock() const {
                return this->SelectBits(30, 18);
            }

            constexpr ALWAYS_INLINE KPhysicalAddress GetTable() const {
                return this->SelectBits(12, 36);
            }

            constexpr ALWAYS_INLINE bool GetTable(KPhysicalAddress &out) const {
                if (this->IsTable()) {
                    out = this->GetTable();
                    return true;
                } else {
                    return false;
                }
            }

            constexpr ALWAYS_INLINE bool IsCompatibleWithAttribute(const PageTableEntry &rhs, bool contig) const {
                /* Check whether this has the same permission/etc as the desired attributes. */
                return L1PageTableEntry(this->GetBlock(), rhs, contig).GetRawAttributes() == this->GetRawAttributes();
            }
    };

    class L2PageTableEntry : public PageTableEntry {
        public:
            constexpr ALWAYS_INLINE L2PageTableEntry(InvalidTag) : PageTableEntry(InvalidTag{}) { /* ... */ }

            constexpr ALWAYS_INLINE L2PageTableEntry(KPhysicalAddress phys_addr, bool pxn)
                : PageTableEntry((0x3ul << 60) | (static_cast<u64>(pxn) << 59) | GetInteger(phys_addr) | 0x3)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE L2PageTableEntry(KPhysicalAddress phys_addr, bool is_kernel, bool pxn)
                : PageTableEntry(((is_kernel ? 0x3ul : 0) << 60) | (static_cast<u64>(pxn) << 59) | GetInteger(phys_addr) | 0x3)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE L2PageTableEntry(KPhysicalAddress phys_addr, const PageTableEntry &attr, bool contig)
                : PageTableEntry(attr, (static_cast<u64>(contig) << 52) | GetInteger(phys_addr) | 0x1)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE KPhysicalAddress GetBlock() const {
                return this->SelectBits(21, 27);
            }

            constexpr ALWAYS_INLINE KPhysicalAddress GetTable() const {
                return this->SelectBits(12, 36);
            }

            constexpr ALWAYS_INLINE bool GetTable(KPhysicalAddress &out) const {
                if (this->IsTable()) {
                    out = this->GetTable();
                    return true;
                } else {
                    return false;
                }
            }

            constexpr ALWAYS_INLINE bool IsCompatibleWithAttribute(const PageTableEntry &rhs, bool contig) const {
                /* Check whether this has the same permission/etc as the desired attributes. */
                return L2PageTableEntry(this->GetBlock(), rhs, contig).GetRawAttributes() == this->GetRawAttributes();
            }
    };

    class L3PageTableEntry : public PageTableEntry {
        public:
            constexpr ALWAYS_INLINE L3PageTableEntry(InvalidTag) : PageTableEntry(InvalidTag{}) { /* ... */ }

            constexpr ALWAYS_INLINE L3PageTableEntry(KPhysicalAddress phys_addr, const PageTableEntry &attr, bool contig)
                : PageTableEntry(attr, (static_cast<u64>(contig) << 52) | GetInteger(phys_addr) | 0x3)
            {
                /* ... */
            }

            constexpr ALWAYS_INLINE bool IsBlock() const { return this->GetBits(0, 2) == 0x3; }

            constexpr ALWAYS_INLINE KPhysicalAddress GetBlock() const {
                return this->SelectBits(12, 36);
            }

            constexpr ALWAYS_INLINE bool IsCompatibleWithAttribute(const PageTableEntry &rhs, bool contig) const {
                /* Check whether this has the same permission/etc as the desired attributes. */
                return L3PageTableEntry(this->GetBlock(), rhs, contig).GetRawAttributes() == this->GetRawAttributes();
            }
    };

    constexpr inline L1PageTableEntry InvalidL1PageTableEntry = L1PageTableEntry(PageTableEntry::InvalidTag{});
    constexpr inline L2PageTableEntry InvalidL2PageTableEntry = L2PageTableEntry(PageTableEntry::InvalidTag{});
    constexpr inline L3PageTableEntry InvalidL3PageTableEntry = L3PageTableEntry(PageTableEntry::InvalidTag{});

}
