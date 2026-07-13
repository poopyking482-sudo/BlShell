#include <string.h>
#include "bl_auth.h"
#include "process_core.h"

// Check if the current user has sudo rights
int is_allowed_sudo(const char *username) {
    // Only root is allowed to use sudo by default
    if (strcmp(username, "root") == 0) {
        return 1; // allowed
    }
    return 0; // denied
}

void shell_sudo(char *tokens[], int token_count) {
    if (token_count < 2 || !tokens[1]) return;

    if (!is_allowed_sudo(current_user)) {
        // print an error message here so the user knows they are denied
        return; 
    }

    // 1. save original identity state safely
    int saved_uid = current_uid;
    char saved_user[MAX_LEN];
    strncpy(saved_user, current_user, MAX_LEN - 1);
    saved_user[MAX_LEN - 1] = '\0'; // Ensure safe null-termination

    // 2. escalate to root privileges
    current_uid = 0;
    strncpy(current_user, "root", MAX_LEN - 1);
    current_user[MAX_LEN - 1] = '\0';

    // 3. execute the command behind "sudo"
    shell_call(&tokens[1], token_count - 1);

    // 4. instantly drop privileges back down safely
    current_uid = saved_uid;
    strncpy(current_user, saved_user, MAX_LEN - 1);
    current_user[MAX_LEN - 1] = '\0';
}
