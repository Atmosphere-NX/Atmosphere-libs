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
#include <stratosphere.hpp>
#include "erpt_srv_attachment_impl.hpp"
#include "erpt_srv_attachment.hpp"

namespace ams::erpt::srv {

    AttachmentImpl::AttachmentImpl() : attachment(nullptr) {
        /* ... */
    }

    AttachmentImpl::~AttachmentImpl() {
        R_ABORT_UNLESS(this->Close());
    }

    Result AttachmentImpl::Open(const AttachmentId &attachment_id) {
        R_UNLESS(this->attachment == nullptr, erpt::ResultAlreadyInitialized());

        JournalRecord<AttachmentInfo> *record = Journal::Retrieve(attachment_id);
        R_UNLESS(record != nullptr, erpt::ResultNotFound());

        this->attachment = new Attachment(record);
        R_UNLESS(this->attachment != nullptr, erpt::ResultOutOfMemory());
        auto attachment_guard = SCOPE_GUARD { delete this->attachment; this->attachment = nullptr; };

        R_TRY(this->attachment->Open(AttachmentOpenType_Read));
        attachment_guard.Cancel();

        return ResultSuccess();
    }

    Result AttachmentImpl::Read(ams::sf::Out<u32> out_count, const ams::sf::OutBuffer &out_buffer)  {
        R_UNLESS(this->attachment != nullptr, erpt::ResultNotInitialized());

        return this->attachment->Read(out_count.GetPointer(), static_cast<u8 *>(out_buffer.GetPointer()), static_cast<u32>(out_buffer.GetSize()));
    }

    Result AttachmentImpl::SetFlags(AttachmentFlagSet flags)  {
        R_UNLESS(this->attachment != nullptr, erpt::ResultNotInitialized());

        return this->attachment->SetFlags(flags);
    }

    Result AttachmentImpl::GetFlags(ams::sf::Out<AttachmentFlagSet> out)  {
        R_UNLESS(this->attachment != nullptr, erpt::ResultNotInitialized());

        return this->attachment->GetFlags(out.GetPointer());
    }

    Result AttachmentImpl::Close()  {
        if (this->attachment != nullptr) {
            this->attachment->Close();
            delete this->attachment;
            this->attachment = nullptr;
        }
        return ResultSuccess();
    }

    Result AttachmentImpl::GetSize(ams::sf::Out<s64> out)  {
        R_UNLESS(this->attachment != nullptr, erpt::ResultNotInitialized());

        return this->attachment->GetSize(out.GetPointer());
    }

}
