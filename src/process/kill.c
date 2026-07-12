#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include "process_core.h"

// bring in the external privilege state tracking from your shell core
extern int is_root; 

void shell_kill(const char *pid_str) {
    // guard the command behind sudo, user can abuse!
    if (!is_root) {
        printf("error: permission denied. 'kill' requires sudo privileges.\n");
        return;
    }

    if (!pid_str) {
        printf("error: missing PID argument\n");
        return;
    }

    // atoi returns 0 on failure. kill(0, SIGKILL) kills the shell's entire process group
    int target = atoi(pid_str);
    if (target == 0 && pid_str[0] != '0') {
        printf("error: invalid PID '%s'\n", pid_str);
        return;
    }

    pid_t target_pid = (pid_t)target;

    // prevent the user from killing INIT/Systemd
    if (target_pid == 1) {
        printf("Blshell error: Killing init (PID 1) is forbidden. nice try!\n");
        return;
    }

    if (kill(target_pid, SIGKILL) == 0) {
        printf("killed process %d\n", target_pid);
    } else {
        // let perror print the exact reason (Permission Denied vs Process Not Found)
        perror("kill");
    }
}
