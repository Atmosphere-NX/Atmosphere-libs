/**
 * @file sm_ams.h
 * @brief Service manager (sm) IPC wrapper for Atmosphere extensions.
 * @author SciresM
 * @copyright libnx Authors
 */
#pragma once
#include <switch.h>

#ifdef __cplusplus
extern "C" {
#endif

Result smAtmosphereHasService(bool *out, const char *name);
Result smAtmosphereWaitService(const char *name);
Result smAtmosphereHasMitm(bool *out, const char *name);
Result smAtmosphereWaitMitm(const char *name);

Result smAtmosphereMitmInitialize(void);
void smAtmosphereMitmExit(void);

Result smAtmosphereMitmInstall(Handle *handle_out, Handle *query_out, const char *name);
Result smAtmosphereMitmUninstall(const char *name);
Result smAtmosphereMitmAssociateProcessIdAndTitleId(u64 pid, u64 tid);
Result smAtmosphereMitmAcknowledgeSession(Service *srv_out, u64 *pid_out, const char *name);

#ifdef __cplusplus
}
#endif