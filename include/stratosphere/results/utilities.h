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

#ifdef __cplusplus
}
#endif
