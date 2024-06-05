#ifndef USER_H
#define USER_H

typedef enum {
    ADMIN, // 0
    AGENT, // 1
    CLIENT, // 2
} UserRole;

typedef struct {
    char username[20];
    char password[20];
    UserRole role;
} User;

void display_menu(const User *user);

void createUser(const char* username, const char* password, UserRole role);

#endif