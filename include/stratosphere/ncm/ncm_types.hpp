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

#include <type_traits>

namespace sts::ncm {

    /* Storage IDs. */
    enum class StorageId : u8 {
        None        = 0,
        Host        = 1,
        GameCard    = 2,
        NandSystem  = 3,
        NandUser    = 4,
        SdCard      = 5,
    };

    /* Title IDs. */
    struct TitleId {
        u64 value;

        inline explicit operator u64() const {
            return this->value;
        }
    };
    static constexpr TitleId InvalidTitleId = {};

    inline bool operator==(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value == rhs.value;
    }

    inline bool operator!=(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value != rhs.value;
    }

    inline bool operator<(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value < rhs.value;
    }

    inline bool operator<=(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value <= rhs.value;
    }

    inline bool operator>(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value > rhs.value;
    }

    inline bool operator>=(const TitleId &lhs, const TitleId &rhs) {
        return lhs.value >= rhs.value;
    }

    static_assert(sizeof(TitleId) == sizeof(u64) && std::is_pod<TitleId>::value, "TitleId definition!");

    /* Title Location. */
    struct TitleLocation {
        TitleId title_id;
        u8 storage_id;
    };

    constexpr TitleLocation MakeTitleLocation(TitleId title_id, StorageId storage_id) {
        TitleLocation loc = { .title_id = title_id, .storage_id = static_cast<u8>(storage_id) };
        return loc;
    }

    static_assert(sizeof(TitleLocation) == 0x10 && std::is_pod<TitleLocation>::value, "TitleLocation definition!");

}
