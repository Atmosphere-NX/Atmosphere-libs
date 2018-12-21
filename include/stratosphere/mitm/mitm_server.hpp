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

#include "mitm_query_service.hpp"
#include "sm_mitm.h"
#include "mitm_session.hpp"

template <typename T, typename... Args>
class MitmServer : public IWaitable {          
    static_assert(std::is_base_of<IMitmServiceObject, T>::value, "MitM Service Objects must derive from IMitmServiceObject");
    private:
        Handle port_handle;
        unsigned int max_sessions;
        char mitm_name[9];
    
        std::tuple<Args...> args;

        template<std::size_t... I>
        static std::shared_ptr<T> ConstructionDetailHelper(std::shared_ptr<Service> forward_service, u64 client_pid, std::tuple<Args...> &&tuple, std::index_sequence<I...>) {
            return std::make_shared<T>(forward_service, client_pid, std::forward<Args>(std::get<I>(std::forward<std::tuple<Args...>>(tuple)))...);
        }
    public:
        MitmServer(Handle *out_query_h, const char *service_name, unsigned int max_s, Args... args) : port_handle(0), max_sessions(max_s), args(std::forward_as_tuple<Args>(std::forward<Args>(args))...) {
            Handle tmp_hnd;
            Result rc = smMitMInitialize();
            if (R_FAILED(rc)) {
                fatalSimple(rc);
            }
            
            if (R_SUCCEEDED((rc = smGetServiceOriginal(&tmp_hnd, smEncodeName(service_name))))) {
                svcCloseHandle(tmp_hnd);
            } else {
                fatalSimple(rc);
            }
            strncpy(mitm_name, service_name, 8);
            mitm_name[8] = '\x00';
            if (R_FAILED((rc = smMitMInstall(&this->port_handle, out_query_h, mitm_name)))) {
                fatalSimple(rc);           
            }
            
            smMitMExit();
        }
        
        virtual ~MitmServer() override {
            if (this->port_handle) {
                if (R_FAILED(smMitMUninstall(this->mitm_name))) {
                    std::abort();
                }
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
            
            /* Create a forward service for this instance. */
            std::shared_ptr<Service>forward_service(new Service(), [](Service *s) {
                /* Custom deleter to ensure service is open as long as necessary. */
                serviceClose(s);
                delete s;
            });
            
            rc = smMitMInitialize();
            if (R_FAILED(rc)) {
                fatalSimple(rc);
            }
            
            u64 client_pid;
            
            if (R_FAILED(smMitMAcknowledgeSession(forward_service.get(), &client_pid, mitm_name))) {
                /* TODO: Panic. */
            }
            
            smMitMExit();
                        
            this->GetSessionManager()->AddWaitable(new MitmSession(session_h, client_pid, forward_service, ConstructionDetailHelper(forward_service, client_pid, std::forward<std::tuple<Args...>>(args), std::index_sequence_for<Args...>())));
            return 0;
        }

};

template<typename T, typename... Args>
static void AddMitmServerToManager(SessionManagerBase *manager, const char *srv_name, unsigned int max_sessions, Args... args) {
    Handle query_h;
    auto *srv = new MitmServer<T, Args...>(&query_h, srv_name, max_sessions, std::forward<Args>(args)...);
    manager->AddSession(query_h, std::move(ServiceObjectHolder(std::move(std::make_shared<MitmQueryService<T>>()))));
    manager->AddWaitable(srv);
}


