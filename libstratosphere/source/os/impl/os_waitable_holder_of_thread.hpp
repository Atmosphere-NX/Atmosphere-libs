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
#include "os_waitable_holder_base.hpp"

namespace ams::os::impl {

    class WaitableHolderOfThread : public WaitableHolderOfUserObject {
        private:
            ThreadType *thread;
        private:
            TriBool IsSignaledImpl() const {
                return this->thread->state == ThreadType::State_Terminated ? TriBool::True : TriBool::False;
            }
        public:
            explicit WaitableHolderOfThread(ThreadType *t) : thread(t) { /* ... */ }

            /* IsSignaled, Link, Unlink implemented. */
            virtual TriBool IsSignaled() const override {
                std::scoped_lock lk(GetReference(this->thread->cs_thread));
                return this->IsSignaledImpl();
            }

            virtual TriBool LinkToObjectList() override {
                std::scoped_lock lk(GetReference(this->thread->cs_thread));

                GetReference(this->thread->waitlist).LinkWaitableHolder(*this);
                return this->IsSignaledImpl();
            }

            virtual void UnlinkFromObjectList() override {
                std::scoped_lock lk(GetReference(this->thread->cs_thread));

                GetReference(this->thread->waitlist).UnlinkWaitableHolder(*this);
            }
    };

}
