#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    // we need at least the search pattern
    if (argc < 2) {
        printf("Usage: %s <pattern> [file]\n", argv[0]);
        return 1;
    }

    char *pattern = argv[1];
    FILE *stream = stdin;

    // if they passed a file argument, open it. otherwise, default to stdin (for piping!)
    if (argc >= 3) {
        stream = fopen(argv[2], "r");
        if (!stream) {
            printf("Error: Could not open file %s\n", argv[2]);
            return 1;
        }
    }

    char line[1024];
    // read line by line until EOF
    while (fgets(line, sizeof(line), stream)) {
        // if the pattern exists anywhere in this line, print it
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    if (stream != stdin) {
        fclose(stream);
    }

    return 0;
}
