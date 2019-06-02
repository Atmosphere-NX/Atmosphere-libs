/**
 * @file result_utilities.h
 * @brief Utilities for handling Results.
 * @author SciresM
 * @copyright libnx Authors
 */
#pragma once
#include <switch/result.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Evaluates an expression that returns a result, and returns the result if it would fail.
#define R_TRY(res_expr) \
    do { \
        const Result _tmp_r_try_rc = res_expr; \
        if (R_FAILED(_tmp_r_try_rc)) { \
            return _tmp_r_try_rc; \
        } \
    } while (0)

/// Helpers for pattern-matching on a result expression, if the result would fail.
#define R_TRY_CATCH(res_expr) \
    do { \
        const Result _tmp_r_try_catch_rc = res_expr; \
        if (R_FAILED(_tmp_r_try_catch_rc)) { \
            if (false)

#define R_CATCH(catch_result) \
            } else if (_tmp_r_try_catch_rc == catch_result) { \
                _Static_assert(R_FAILED(catch_result), "Catch result must be constexpr error Result!"); \
                if (false) { } \
                else

#define R_CATCH_RANGE(catch_result_start, catch_result_end) \
            } else if (catch_result_start <= _tmp_r_try_catch_rc && _tmp_r_try_catch_rc <= catch_result_end) { \
                _Static_assert(R_FAILED(catch_result_start), "Catch start result must be constexpr error Result!"); \
                _Static_assert(R_FAILED(catch_result_end), "Catch end result must be constexpr error Result!");  \
                _Static_assert(R_MODULE(catch_result_start) == R_MODULE(catch_result_end), "Catch range modules must be equal!"); \
                if (false) { } \
                else

#define R_CATCH_MODULE(module) \
            } else if (R_MODULE(_tmp_r_try_catch_rc) == module) { \
                _Static_assert(module != 0, "Catch module must be error!"); \
                if (false) { } \
                else

#define R_END_TRY_CATCH \
        } else if (R_FAILED(_tmp_r_try_catch_rc)) { \
            return _tmp_r_try_catch_rc; \
        } \
    } while (0)

#ifdef __cplusplus
}
#endif
