#include "process_core.h"

void shell_blterm(const char *pid_str) {
    // Directly forwards the argument straight to your main term logic
    shell_term(pid_str);
}
