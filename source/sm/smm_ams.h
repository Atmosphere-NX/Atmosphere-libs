/**
 * @file smm_ams.h
 * @brief Service manager manager (sm:m) IPC wrapper for Atmosphere extensions.
 * @author SciresM
 * @copyright libnx Authors
 */
#pragma once
#include <switch.h>

#ifdef __cplusplus
extern "C" {
#endif

Result smManagerAtmosphereEndInitialDefers(void);
Result smManagerAtmosphereHasMitm(bool *out, const char* name);

#ifdef __cplusplus
}
#endif