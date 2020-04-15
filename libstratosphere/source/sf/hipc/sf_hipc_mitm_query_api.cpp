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
#include "sf_hipc_mitm_query_api.hpp"

namespace ams::sf::hipc::impl {

    namespace {

        class MitmQueryService : public IServiceObject {
            private:
                enum class CommandId {
                    ShouldMitm = 65000,
                };
            private:
                ServerManagerBase::MitmQueryFunction query_function;
            public:
                MitmQueryService(ServerManagerBase::MitmQueryFunction qf) : query_function(qf) { /* ... */ }

                void ShouldMitm(sf::Out<bool> out, const sm::MitmProcessInfo &client_info) {
                    out.SetValue(this->query_function(client_info));
                }
            public:
                DEFINE_SERVICE_DISPATCH_TABLE {
                    MAKE_SERVICE_COMMAND_META(ShouldMitm),
                };
        };

        /* Globals. */
        os::Mutex g_query_server_lock(false);
        bool g_constructed_server = false;
        bool g_registered_any = false;

        void QueryServerProcessThreadMain(void *query_server) {
            reinterpret_cast<ServerManagerBase *>(query_server)->LoopProcess();
        }

        constexpr size_t QueryServerProcessThreadStackSize = 0x4000;
        constexpr s32    QueryServerProcessThreadPriority  = -1;
        alignas(os::ThreadStackAlignment) u8 g_server_process_thread_stack[QueryServerProcessThreadStackSize];
        os::ThreadType g_query_server_process_thread;

        constexpr size_t MaxServers = 0;
        TYPED_STORAGE(sf::hipc::ServerManager<MaxServers>) g_query_server_storage;

    }

    void RegisterMitmQueryHandle(Handle query_handle, ServerManagerBase::MitmQueryFunction query_func) {
        std::scoped_lock lk(g_query_server_lock);


        if (AMS_UNLIKELY(!g_constructed_server)) {
            new (GetPointer(g_query_server_storage)) sf::hipc::ServerManager<MaxServers>();
            g_constructed_server = true;
        }

        R_ABORT_UNLESS(GetPointer(g_query_server_storage)->RegisterSession(query_handle, cmif::ServiceObjectHolder(std::make_shared<MitmQueryService>(query_func))));

        if (AMS_UNLIKELY(!g_registered_any)) {
            R_ABORT_UNLESS(os::CreateThread(std::addressof(g_query_server_process_thread), &QueryServerProcessThreadMain, GetPointer(g_query_server_storage), g_server_process_thread_stack, sizeof(g_server_process_thread_stack), QueryServerProcessThreadPriority));
            os::StartThread(std::addressof(g_query_server_process_thread));
            g_registered_any = true;
        }
    }

}
