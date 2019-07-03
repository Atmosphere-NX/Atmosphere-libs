/*
 * Copyright (c) 2018-2019 Atmosphère-NX
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
#include <switch.h>
#include <stratosphere.hpp>
#include "../ncm.hpp"

namespace MitmQueryUtils {
    Result GetAssociatedTidForPid(u64 pid, sts::ncm::TitleId *tid);

    void AssociatePidToTid(u64 pid, sts::ncm::TitleId tid);
}

template <typename T>
class MitmQueryService : public IServiceObject {
    private:
        enum class CommandId {
            ShouldMitm      = 65000,
            AssociatePidToTid = 65001,
        };
    protected:
        void ShouldMitm(Out<bool> should_mitm, u64 pid) {
            should_mitm.SetValue(false);
            sts::ncm::TitleId tid = sts::ncm::TitleId::Invalid;
            if (R_SUCCEEDED(MitmQueryUtils::GetAssociatedTidForPid(pid, &tid))) {
                should_mitm.SetValue(T::ShouldMitm(pid, tid));
            }
        }
        void AssociatePidToTid(u64 pid, sts::ncm::TitleId tid) {
            MitmQueryUtils::AssociatePidToTid(pid, tid);
        }
    public:
        DEFINE_SERVICE_DISPATCH_TABLE {
            MAKE_SERVICE_COMMAND_META(MitmQueryService<T>, ShouldMitm),
            MAKE_SERVICE_COMMAND_META(MitmQueryService<T>, AssociatePidToTid),
        };
};