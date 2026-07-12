#include <stdio.h>
#include <string.h>

void stream_file(FILE *file, int number_lines) {
    char line[1024];
    int line_count = 1;

    // Read line by line until End-Of-File
    while (fgets(line, sizeof(line), file) != NULL) {
        if (number_lines) {
            printf("%6d  %s", line_count++, line);
        } else {
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    int number_lines = 0;
    int file_index = 1;

    // Check for the line numbering option
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        number_lines = 1;
        file_index = 2;
    }

    // Default to standard input if no files are passed
    if (file_index >= argc) {
        stream_file(stdin, number_lines);
        return 0;
    }

    // Loop through and print every file passed
    for (int i = file_index; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "see: cannot open '%s'\n", argv[i]);
            continue;
        }
        stream_file(file, number_lines);
        fclose(file);
    }

    return 0;
}
