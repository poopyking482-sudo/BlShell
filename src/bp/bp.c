#include <stdio.h>
#include <stdlib.h> // REQUIRED for malloc and free memory
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

// 1MB Buffer Size (1024 * 1024 bytes)
#define BUFFER_SIZE 1048576

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "error: missing arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "error: source and destination are the same.\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        fprintf(stderr, "error opening source: %s\n", strerror(errno));
        return 1;
    }

    FILE *dest = fopen(argv[2], "wb");
    if (!dest) {
        fprintf(stderr, "error creating destination: %s\n", strerror(errno));
        fclose(src);
        return 1;
    }

    // SAFE: Dynamically allocate 1MB on the Heap instead of the Stack
    uint8_t *buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "error: System out of memory! Could not allocate 1MB buffer.\n");
        fclose(src);
        fclose(dest);
        return 1;
    }

    size_t bytes_read;
    bool copy_failed = false;

    // Copies files in massive 1MB streams
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest);

        if (bytes_written < bytes_read) {
            fprintf(stderr, "error: write failed mid-transfer: %s\n", strerror(errno));
            copy_failed = true;
            break;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "error: read failed mid-transfer: %s\n", strerror(errno));
        copy_failed = true;
    }

    // CRITICAL: Always free heap memory when you are done to prevent memory leaks
    free(buffer);

    fclose(src);
    fclose(dest);

    if (!copy_failed) {
        printf("copied %s to %s successfully\n", argv[1], argv[2]);
        return 0;
    }

    return 1;
}
// everyone is fricking crazy