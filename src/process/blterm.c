#include "process_core.h"

void shell_blterm(const char *pid_str) {
    // directly forwards the argument straight to main term logic
    shell_term(pid_str);
}
