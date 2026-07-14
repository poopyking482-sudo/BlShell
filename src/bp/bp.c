#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: bp <source_file> <dest_file>\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        printf("bp:cannot open source file %s\n", argv[1]);
        return 1;
    }

    FILE *dest = fopen(argv[2], "wb");
    if (!dest) {
        printf("bp:cannot create destination file %s\n", argv[2]);
        fclose(src);
        return 1;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest);
        
        if (bytes_written < bytes_read) {
            printf("bp:failed to write all bytes to destination\n");
            fclose(src);
            fclose(dest);
            return 1;
        }
    }

    fclose(src);
    fclose(dest);

    printf("Copied %s to %s successfully.\n", argv[1], argv[2]);
    return 0;
}
