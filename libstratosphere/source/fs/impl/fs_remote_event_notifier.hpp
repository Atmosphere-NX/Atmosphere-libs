/*
 * Copyright (c) Atmosphère-NX
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
#include <stratosphere.hpp>

namespace ams::fs::impl {

    #if defined(ATMOSPHERE_OS_HORIZON)
    class RemoteEventNotifier {
        private:
            ::FsEventNotifier m_notifier;
        public:
            RemoteEventNotifier(::FsEventNotifier &n) : m_notifier(n) { /* ... */ }

            virtual ~RemoteEventNotifier() {
                fsEventNotifierClose(std::addressof(m_notifier));
            }
        public:
            Result GetEventHandle(ams::sf::OutCopyHandle out) {
                ::Event e;
                R_TRY(fsEventNotifierGetEventHandle(std::addressof(m_notifier), std::addressof(e), false));

                out.SetValue(e.revent, true);
                R_SUCCEED();
            }
    };
    static_assert(fssrv::sf::IsIEventNotifier<RemoteEventNotifier>);
    #endif

}
