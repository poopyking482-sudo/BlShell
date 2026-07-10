#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "process_core.h"

void shell_kill(const char *pid_str) {
    if (!pid_str) {
        printf("error: PID not found\n");
        return;
    }
    
    pid_t target_pid = (pid_t)atoi(pid_str);
    if (kill(target_pid, SIGKILL) == 0) {
        printf("killed process %d\n", target_pid);
    } else {
        perror("kill failed:critical");
    }
}
// if you see this error:your probrably trying to kill init as sudo or just going crazy