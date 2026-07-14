#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

// Explicitly defining our buffer size using a standard 4KB chunk
#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "error: missing arguments. (syntax error?)\n");
        fprintf(stderr, "Usage: bp <source_file> <dest_file>\n");
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "error: '%s' and '%s' are the same file.\n", argv[1], argv[2]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        fprintf(stderr, "error: cannot open source '%s': %s\n", argv[1], strerror(errno));
        return 1;
    }

    FILE *dest = fopen(argv[2], "wb");
    if (!dest) {
        fprintf(stderr, "error: cannot create destination '%s': %s\n", argv[2], strerror(errno));
        fclose(src);
        return 1;
    }

    // Using uint8_t ensures this is an array of exact 1-byte raw binary blocks
    uint8_t buffer[BUFFER_SIZE];
    size_t bytes_read;
    
    // Using a real boolean flag thanks to <stdbool.h>
    bool copy_failed = false;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest);
        
        if (bytes_written < bytes_read) {
            fprintf(stderr, "error: write failed mid-transfer (Disk full?): %s\n", strerror(errno));
            copy_failed = true;
            break;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "error: read failed mid-transfer: %s\n", strerror(errno));
        copy_failed = true;
    }

    if (fclose(src) != 0) {
        fprintf(stderr, "warning: failed to close source file cleanly.\n");
    }
    
    if (fclose(dest) != 0) {
        fprintf(stderr, error: failed to close destination file cleanly: %s\n", strerror(errno));
        copy_failed = true;
    }

    if (!copy_failed) {
        printf("copied %s to %s successfully.\n", argv[1], argv[2]);
        return 0;
    }

    return 1;
}
