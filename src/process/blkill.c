#include "process_core.h"

void shell_blkill(const char *pid_str) {
    // Directly forwards the argument straight to your main kill logic
    shell_kill(pid_str);
}
