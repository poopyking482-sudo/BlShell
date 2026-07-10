#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process_core.h"

void shell_call(char *tokens[], int token_count) {
    if (token_count == 0) return;

    if (strcmp(tokens[0], "fork") == 0) {
        shell_fork();
    } 
    else if (strcmp(tokens[0], "kill") == 0) {
        shell_kill(tokens[1]);
    } 
    else if (strcmp(tokens[0], "exit") == 0) {
        exit(0);
    } 
    else {
        printf("Unknown: %s\n", tokens[0]);
    }
}
// calls
// pid:your not my type
// me:fairs