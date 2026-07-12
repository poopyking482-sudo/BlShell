#include "process_core.h"

void shell_blkill(const char *pid_str) {
    // directly forwards the argument straight to main kill logic
    shell_kill(pid_str);
}
