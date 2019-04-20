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

#include <switch.h>
#include <stratosphere.hpp>
#include <random>

/* Official HOS uses TinyMT. This is high effort. Let's just use XorShift. */
/* https://en.wikipedia.org/wiki/Xorshift */
class XorShiftGenerator {
    public:
        using result_type = uint32_t;
        static constexpr result_type (min)() { return 0; }
        static constexpr result_type (max)() { return UINT32_MAX; }
        static constexpr size_t num_seed_dwords = 4;
    private:
        result_type random_state[num_seed_dwords];
    public:

        explicit XorShiftGenerator() {
            /* Seed using process entropy. */
            u64 val = 0;
            for (size_t i = 0; i < num_seed_dwords; i++) {
                if (R_FAILED(svcGetInfo(&val, 0xB, 0, i))) {
                    std::abort();
                }
                this->random_state[i] = result_type(val);
            }
        }

        explicit XorShiftGenerator(std::random_device &rd) {
            for (size_t i = 0; i < num_seed_dwords; i++) {
                this->random_state[i] = result_type(rd());
            }
        }

        result_type operator()() {
            result_type s, t = this->random_state[3];
            t ^= t << 11;
            t ^= t >> 8;
            this->random_state[3] = this->random_state[2]; this->random_state[2] = this->random_state[1]; this->random_state[1] = (s = this->random_state[0]);
            t ^= s;
            t ^= s >> 19;
            this->random_state[0] = t;
            return t;
        }

        void discard(size_t n) {
            for (size_t i = 0; i < n; i++) {
                operator()();
            }
        }
};

static XorShiftGenerator g_rnd_generator;

template<typename T>
T StratosphereRandomUtils::GetRandom(T max) {
    std::uniform_int_distribution<T> rnd(0, max);
    return rnd(g_rnd_generator);
}

/* These are slightly biased, but I think that's totally okay. */
u32 StratosphereRandomUtils::GetRandomU32(u32 max) {
    return GetRandom<u32>(max);
}

u64 StratosphereRandomUtils::GetRandomU64(u64 max) {
    return GetRandom<u64>(max);
}

