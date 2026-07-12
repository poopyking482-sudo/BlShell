#ifndef BL_AUTH_H
#define BL_AUTH_H

#define MAX_USERS 50
#define MAX_LEN 50

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    int uid;
} User;

// global tracking variables to be read by main.c or process commands
extern char current_user[MAX_LEN];
extern int current_uid;

// core functions
void init_user_system(void);
int register_user(const char *username, const char *password);
int login_user(const char *username, const char *password);
void logout_user(void);

#endif
