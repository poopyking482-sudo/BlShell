#ifndef PROCESS_CORE_H
#define PROCESS_CORE_H

void shell_fork(void);
void shell_kill(const char *pid_str);
void shell_call(char *tokens[], int token_count);

#endif
// !usr/bin/Blshell/process/process_core.h