#include <stdio.h>
#include <string.h>
#include "shell_link.h"

// declare the external functions from your other C files
// so this file knows they exist at link time
extern void shell_kill(const char *pid_str);

void route_command(const char *cmd, char **tokens) {
    if (cmd == NULL) return;

    // Route: kill
    if (strcmp(cmd, "kill") == 0) {
        // pass tokens[1] (the PID argument) to your kill function
        shell_kill(tokens[1]);
    } 
    
    // route: future commands can be chained here easily
    // fallback: Unknown command
    else {
        printf("blsh: %s: command not found\n", cmd);
    }
}
