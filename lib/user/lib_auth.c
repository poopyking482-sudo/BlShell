#include <string.h>
#include "bl_auth.h"

// define the global state variables
char current_user[MAX_LEN] = "guest";
int current_uid = 1000;

// internal in-memory user database
static BlUser user_db[MAX_USERS];
static int user_count = 0;

// creates default system accounts on boot
void init_user_system(void) {
    // add root (UID 0)
    strcpy(user_db[0].username, "root");
    strcpy(user_db[0].password, "root");
    user_db[0].uid = 0;
    
    user_count = 1;
}

// add a new user dynamically during runtime
int register_user(const char *username, const char *password) {
    if (user_count >= MAX_USERS || !username || !password) return -1;

    // check if username already exists
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_db[i].username, username) == 0) return -1;
    }

    strncpy(user_db[user_count].username, username, MAX_LEN - 1);
    strncpy(user_db[user_count].password, password, MAX_LEN - 1);
    user_db[user_count].uid = 1000 + user_count; // Assign non-root UID
    user_count++;
    
    return 0;
}

// authenticates and switches the active shell identity
int login_user(const char *username, const char *password) {
    if (!username || !password) return -1;

    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_db[i].username, username) == 0 && 
            strcmp(user_db[i].password, password) == 0) {
            
            // identity switch
            strncpy(current_user, user_db[i].username, MAX_LEN - 1);
            current_uid = user_db[i].uid;
            return 0; // success
        }
    }
    return -1; // authentication error
}

// drops back down to the default guest account
void logout_user(void) {
    strcpy(current_user, "guest");
    current_uid = 1000;
}
