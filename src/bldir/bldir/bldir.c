#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    // make sure they actually gave a directory name, else start a except 
    if (argc < 2) {
        fprintf(stderr, "error: please specify directory name\n");
        return 1;
    }

    // argv[1] is the target directory path, yes
    // 0777 gives standard read/write/execute permissions (modified by umask)
    if (mkdir(argv[1], 0777) != 0) {
        perror("error"); // automatically prints why it failed because it's called error handling (e.g., File exists)
        return 1;
    }

    printf("[bldir] successfully created: %s\n", argv[1]);
    return 0;
}
// use /bin/blshell
