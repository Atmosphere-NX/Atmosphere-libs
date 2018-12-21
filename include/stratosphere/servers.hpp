/*
 * Copyright (c) 2018 Atmosphère-NX
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

#include<tuple>

#include "iwaitable.hpp"
#include "ipc.hpp"

template<typename T, typename... Args>
class IServer : public IWaitable {
    static_assert(std::is_base_of<IServiceObject, T>::value, "Service Objects must derive from IServiceObject");
    protected:
        Handle port_handle;
        unsigned int max_sessions;

    private:
        std::tuple<Args...> args;

        template<std::size_t... I>
        static std::shared_ptr<T> ConstructionDetailHelper(std::tuple<Args...> &&tuple, std::index_sequence<I...>) {
            return std::make_shared<T>(std::forward<Args>(std::get<I>(std::forward<std::tuple<Args...>>(tuple)))...);
        }
    public:        
        IServer(unsigned int max_s, Args... args) : port_handle(0), max_sessions(max_s), args(std::forward_as_tuple<Args>(std::forward<Args>(args))...) { }
        
        virtual ~IServer() {            
            if (port_handle) {
                svcCloseHandle(port_handle);
            }
        }

        SessionManagerBase *GetSessionManager() {
            return static_cast<SessionManagerBase *>(this->GetManager());
        }
        
        /* IWaitable */                        
        virtual Handle GetHandle() override {
            return this->port_handle;
        }
        
        virtual Result HandleSignaled(u64 timeout) override {
            /* If this server's port was signaled, accept a new session. */
            Handle session_h;
            Result rc = svcAcceptSession(&session_h, this->port_handle);
            if (R_FAILED(rc)) {
                return rc;
            }
            
            this->GetSessionManager()->AddSession(session_h, std::move(ServiceObjectHolder(std::move(ConstructionDetailHelper(std::forward<std::tuple<Args...>>(args), std::index_sequence_for<Args...>())))));
            return 0;
        }
};

template <typename T, typename... Args>
class ServiceServer : public IServer<T, Args...> {    
    public:
        ServiceServer(const char *service_name, unsigned int max_s, Args... args) : IServer<T, Args...>(max_s, std::forward<Args>(args)...) { 
            if (R_FAILED(smRegisterService(&this->port_handle, service_name, false, this->max_sessions))) {
                /* TODO: Panic. */
            }
        }
};

template <typename T, typename... Args>
class ExistingPortServer : public IServer<T, Args...> {
    public:
        ExistingPortServer(Handle port_h, unsigned int max_s, Args... args) : IServer<T, Args...>(max_s, args...) {
            this->port_handle = port_h;
        }
};

template <typename T, typename... Args>
class ManagedPortServer : public IServer<T, Args...> {
    public:
        ManagedPortServer(const char *service_name, unsigned int max_s, Args... args) : IServer<T, Args...>(max_s, args...) { 
            if (R_FAILED(svcManageNamedPort(&this->port_handle, service_name, this->max_sessions))) {
                /* TODO: panic */
            }
        }
};
