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
#include <atomic>

#include <stratosphere.hpp>
#include "../ncm.hpp"
#include "mitm_query_service.hpp"

class IMitmServiceObject : public IServiceObject {
    protected:
        std::shared_ptr<Service> forward_service;
        u64 process_id = 0;
        sts::ncm::TitleId title_id = sts::ncm::TitleId::Invalid;
    public:
        IMitmServiceObject(std::shared_ptr<Service> s, u64 pid) : forward_service(s), process_id(pid) {
            MitmQueryUtils::GetAssociatedTidForPid(this->process_id, &this->title_id);
        }

        virtual sts::ncm::TitleId GetTitleId() const {
            return this->title_id;
        }

        virtual u64 GetProcessId() const {
            return this->process_id;
        }

        virtual bool IsMitmObject() const override { return true; }

        static bool ShouldMitm(u64 pid, u64 tid);

    protected:
        virtual ~IMitmServiceObject() = default;
};
