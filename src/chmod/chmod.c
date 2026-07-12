#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <io.h>
#define CHMOD _chmod
#else
#include <unistd.h>
#define CHMOD chmod
#endif

void print_help(const char *prog_name) {
    printf("=== Portable blutils chmod utility ===\n");
    printf("Usage: %s [octal_mode] [filename]\n", prog_name);
    printf("Options:\n  --help    Display this menu\n\n");
    printf("Example:\n  %s 755 script.sh\n", prog_name);
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return 0;
    }

    if (argc != 3) {
        fprintf(stderr, "Error: Invalid arguments.\n");
        fprintf(stderr, "Try '%s --help' for details.\n", argv[0]);
        return 1;
    }

    char *mode_str = argv[1];
    char *filename = argv[2];
    char *endptr;

    long mode = strtol(mode_str, &endptr, 8);

    if (*endptr != '\0') {
        fprintf(stderr, "Error: Invalid mode format '%s'.\n", mode_str);
        return 1;
    }

    if (mode < 0 || mode > 07777) {
        fprintf(stderr, "Error: Mode '%s' out of range.\n", mode_str);
        return 1;
    }

    // Portable system execution call mapped per OS
    if (CHMOD(filename, (mode_t)mode) < 0) {
        perror("chmod failed");
        return 1;
    }

    printf("Success: Permissions set to %s for '%s'\n", mode_str, filename);
    return 0;
}
