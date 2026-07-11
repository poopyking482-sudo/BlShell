#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "process_core.h"

void shell_fork(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("[parent]:error:fork failed reason:0 pid");
    } else if (pid == 0) {
        printf("child PID: %d\n", getpid());
        while (1) { 
            sleep(1); // Infinite loop until killed
// wydm infinite loop
// I said so loser
        }
    } else {
        printf("[parent]: spawned child PID: %d\n", pid);
    }
}
// !usr/bin/blshell/process/fork.c