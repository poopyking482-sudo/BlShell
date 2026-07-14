#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "rusttypes.h"
#include "colors.h"

#define MAX_LINE 1024
#define MAX_ARGS 64

int main(void) {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    // 1. Instantly clear the screen and home the cursor on boot
    printf(ANSI_CLEAR_SCREEN ANSI_CURSOR_HOME);

    // 2. Print your raw _XCORP_ signature block
    printf(ANSI_WHITE ANSI_BOLD "blsh v1.1 " ANSI_CYAN "_XCORP_" ANSI_RESET "\n");

    // 3. Print your Arch-style system matrix block right underneath
    PRINT_COLOR_MATRIX();
    printf("\n"); // Generates a clean space block before the prompt loop begins

    while (1) {
        printf("blsh> ");
        fflush(stdout);

        // Read input from the user
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        // Remove the trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the input string into arguments
        int i = 0;
        args[i] = strtok(line, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, " ");
        }
        args[i] = NULL; // Array must be NULL-terminated for exec

        if (args[0] == NULL) continue; // If empty command, loop back
        if (strcmp(args[0], "exit") == 0) break; // Built-in exit command

        // Fork a child process to run the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process: try standard PATH execution first
            if (execvp(args[0], args) < 0) {
                // FALLBACK: Try executing from the current local directory
                char local_path[MAX_LINE];
                snprintf(local_path, sizeof(local_path), "./%s", args[0]);

                execvp(local_path, args); 

                // If both standard PATH and local folder checks fail
                fprintf(stderr, "blsh: %s: command not found\n", args[0]);
            }
            exit(1); // Exit child process if exec fails
        } else if (pid > 0) {
            // Parent process: wait for the child to finish running
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }
    return 0;
}
