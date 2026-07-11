#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "process_core.h"

void shell_term(const char *pid_str) {
    if (!pid_str) {
        printf("error: PID not found\n");
        return;
    }

    pid_t target_pid = (pid_t)atoi(pid_str);
    if (kill(target_pid, SIGTERM) == 0) {
        printf("terminated process %d\n", target_pid);
    } else {
        perror("terminationbfailed:critical");
    }
}
// !usr/bin/Blshell/process/term.c