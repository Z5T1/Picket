#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <imp/Console.h>

#include <api/PicketAPI.h>

/** Runs a command from the console
 * @param command	The command to run
 */
void runCommand(char* command) {
	char* full_cmd;
	
	full_cmd = malloc(strlen(command) + strlen(picketScreen) + 48);
	sprintf(full_cmd, "screen -p 0 -S %s -X stuff \"%s\"$(printf \\\\r)", picketScreen, command);
	printf("%s\n", full_cmd);
	system(full_cmd);
	free(full_cmd);
}
