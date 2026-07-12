#include <string.h>
#include "bl_auth.h"
#include "process_core.h"

// check if the current user has sudo rights
int is_allowed_sudo(const char *username) {
    // strcmp returns 0 if the strings are identical!
    if (strcmp(username, "guest") == 0 ||
        strcmp(username, "user") == 0 ||
        strcmp(username, "root") == 0) {
        return 1; // allowed
    }
    return 0; // denied
}

void shell_sudo(char *tokens[], int token_count) {
    if (token_count < 2 || !tokens[1]) return;

    if (!is_allowed_sudo(current_user)) {
        return; 
    }

    // 1. save original identity state
    int saved_uid = current_uid;
    char saved_user[MAX_LEN];
    strcpy(saved_user, current_user);

    // 2. escalate to root privileges
    current_uid = 0;
    strcpy(current_user, "root");

    // 3. execute the command behind "sudo"
    shell_call(&tokens[1], token_count - 1);

    // 4. instantly drop privileges back down
    current_uid = saved_uid;
    strcpy(current_user, saved_user);
}
