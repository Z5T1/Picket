#pragma once

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

/** Runs a command from the console
 * @param command	The command to run
 */
void (*runCommand)(char* command);

#ifdef __cplusplus
}
#endif
