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
#include "results_common.hpp"

namespace ams::capsrv {

    R_DEFINE_NAMESPACE_RESULT_MODULE(206);

    R_DEFINE_ERROR_RESULT(InvalidArgument,              2);
    R_DEFINE_ERROR_RESULT(OutOfMemory,                  3);

    R_DEFINE_ERROR_RESULT(OutOfRange,                   8);

    R_DEFINE_ERROR_RESULT(InvalidFileId,                12);
    R_DEFINE_ERROR_RESULT(InvalidStorageId,             13);
    R_DEFINE_ERROR_RESULT(InvalidContentType,           14);

    R_DEFINE_ERROR_RESULT(FailedToMountImageDirectory,  21);

    R_DEFINE_ERROR_RESULT(FileTooBig,                   23);
    R_DEFINE_ERROR_RESULT(InvalidFileData,              24);

    R_DEFINE_ERROR_RESULT(BufferInsufficient,           30);

    R_DEFINE_ERROR_RESULT(TooManyFiles,                 1401);

}