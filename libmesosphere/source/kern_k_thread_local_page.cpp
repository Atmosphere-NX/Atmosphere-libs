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
#include <mesosphere.hpp>

namespace ams::kern {

    Result KThreadLocalPage::Initialize(KProcess *process) {
        MESOSPHERE_ASSERT_THIS();

        /* Set that this process owns us. */
        this->owner = process;

        /* Allocate a new page. */
        KPageBuffer *page_buf = KPageBuffer::Allocate();
        R_UNLESS(page_buf != nullptr, svc::ResultOutOfMemory());
        auto page_buf_guard = SCOPE_GUARD { KPageBuffer::Free(page_buf); };

        /* Map the address in. */
        R_TRY(this->owner->GetPageTable().MapPages(std::addressof(this->virt_addr), 1, PageSize, page_buf->GetPhysicalAddress(), KMemoryState_ThreadLocal, KMemoryPermission_UserReadWrite));

        /* We succeeded. */
        page_buf_guard.Cancel();
        return ResultSuccess();
    }

    Result KThreadLocalPage::Finalize() {
        MESOSPHERE_ASSERT_THIS();

        /* Get the physical address of the page. */
        KPhysicalAddress phys_addr = Null<KPhysicalAddress>;
        MESOSPHERE_ABORT_UNLESS(this->owner->GetPageTable().GetPhysicalAddress(&phys_addr, this->GetAddress()));

        /* Unmap the page. */
        R_TRY(this->owner->GetPageTable().UnmapPages(this->GetAddress(), 1, KMemoryState_ThreadLocal));

        /* Free the page. */
        KPageBuffer::Free(KPageBuffer::FromPhysicalAddress(phys_addr));
        return ResultSuccess();
    }

    KProcessAddress KThreadLocalPage::Reserve() {
        MESOSPHERE_ASSERT_THIS();

        for (size_t i = 0; i < util::size(this->is_region_free); i++) {
            if (this->is_region_free[i]) {
                this->is_region_free[i] = false;
                return this->GetRegionAddress(i);
            }
        }

        return Null<KProcessAddress>;
    }

    void KThreadLocalPage::Release(KProcessAddress addr) {
        MESOSPHERE_ASSERT_THIS();

        this->is_region_free[this->GetRegionIndex(addr)] = true;
    }

    void *KThreadLocalPage::GetPointer() const {
        MESOSPHERE_ASSERT_THIS();

        KPhysicalAddress phys_addr;
        MESOSPHERE_ABORT_UNLESS(this->owner->GetPageTable().GetPhysicalAddress(std::addressof(phys_addr), this->GetAddress()));
        return static_cast<void *>(KPageBuffer::FromPhysicalAddress(phys_addr));
    }

}
