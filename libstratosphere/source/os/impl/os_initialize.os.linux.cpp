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
#include <stratosphere.hpp>
#include "os_resource_manager.hpp"

namespace ams {

    void Main();

    namespace init {

        void InitializeDefaultAllocator();

    }

    /* TODO: This should probably instead be a custom init::Initialize*()? */
    namespace fs {

        void InitializeForHostTool();

    }

}

namespace ams::os {

    void SetHostArgc(int argc);
    void SetHostArgv(char **argv);

    [[gnu::constructor(101)]] void Initialize() {
        /* Only allow os::Initialize to be called once. */
        AMS_FUNCTION_LOCAL_STATIC_CONSTINIT(bool, s_initialized, false);
        if (s_initialized) {
            return;
        }
        s_initialized = true;

        /* Initialize the global os resource manager. */
        os::impl::ResourceManagerHolder::InitializeResourceManagerInstance();

        /* Initialize virtual address memory. */
        os::InitializeVirtualAddressMemory();

        /* Ensure that the init library's allocator has been setup. */
        init::InitializeDefaultAllocator();
    }

}

extern "C" int main(int argc, char **argv) {
    /* Ensure os library is initialized. */
    ::ams::os::Initialize();

    /* Set argc/argv. */
    ::ams::os::SetHostArgc(argc);
    ::ams::os::SetHostArgv(argv);

    /* Ensure filesystem library is initialized. */
    ::ams::fs::InitializeForHostTool();

    /* Call main. */
    ::ams::Main();

    /* TODO: Should we try to implement a custom exit here? */
    return 0;
}