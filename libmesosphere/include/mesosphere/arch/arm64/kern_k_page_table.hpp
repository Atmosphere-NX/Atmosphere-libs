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
#include <mesosphere/kern_k_page_table_base.hpp>
#include <mesosphere/kern_k_page_group.hpp>
#include <mesosphere/kern_k_page_table_manager.hpp>

namespace ams::kern::arm64 {

    class KPageTable : public KPageTableBase {
        NON_COPYABLE(KPageTable);
        NON_MOVEABLE(KPageTable);
        private:
            KPageTableManager *manager;
            u64 ttbr;
            u8 asid;
        public:
            constexpr KPageTable() : KPageTableBase(), manager(), ttbr(), asid() { /* ... */ }

            static NOINLINE void Initialize(s32 core_id);

            NOINLINE Result InitializeForKernel(void *table, KVirtualAddress start, KVirtualAddress end);
            Result Finalize();
    };

}
