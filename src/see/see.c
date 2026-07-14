#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

// Format and output the file stream to the terminal
void stream_file(FILE *file, bool number_lines, bool show_ends, bool show_tabs) {
    char line[1024];
    int line_count = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        // 1. Print line numbers if requested (-n)
        if (number_lines) {
            printf("%6d  ", line_count++);
        }

        // 2. Step through each character to handle special formatting flags
        for (int i = 0; line[i] != '\0'; i++) {
            // Handle trailing newline character for end-of-line marking (-E)
            if (line[i] == '\n') {
                if (show_ends) {
                    putchar('$'); // Mark the literal end of the string block
                }
                putchar('\n');
            } 
            // Convert raw tab characters to visible symbols (-T)
            else if (line[i] == '\t' && show_tabs) {
                printf("^I");
            } 
            // Pass standard characters straight through
            else {
                putchar(line[i]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    bool number_lines = false;
    bool show_ends = false;
    bool show_tabs = false;
    int file_index = 1;

    // Parse command line flags sequentially
    while (file_index < argc && argv[file_index][0] == '-') {
        char *flag = argv[file_index];
        
        // Loop through flag characters to allow combined flags (e.g., -nE)
        for (int j = 1; flag[j] != '\0'; j++) {
            if (flag[j] == 'n') {
                number_lines = true;
            } else if (flag[j] == 'E') {
                show_ends = true;
            } else if (flag[j] == 'T') {
                show_tabs = true;
            } else {
                fprintf(stderr, "see: unknown option '-%c'\n", flag[j]);
                fprintf(stderr, "Usage: see [-nET] [file...]\n");
                return 1;
            }
        }
        file_index++;
    }

    // Default to stdin if no target files are specified
    if (file_index >= argc) {
        stream_file(stdin, number_lines, show_ends, show_tabs);
        return 0;
    }

    // Process every file passed into the argument list
    int exit_status = 0;
    for (int i = file_index; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "see: cannot open '%s': %s\n", argv[i], strerror(errno));
            exit_status = 1; // Track failure but keep processing remaining files
            continue;
        }
        
        stream_file(file, number_lines, show_ends, show_tabs);
        fclose(file);
    }

    return exit_status;
}
