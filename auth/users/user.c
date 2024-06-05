#include <stdio.h>
#include <string.h>
#include "user.h"
#include "../../menus/admin_main_menu/admin_main_menu.h"
#include "../../menus/agent_main_menu/agent_main_menu.h"
#include "../../menus/client_main_menu/client_main_menu.h"

#include "../../utils/utils.h"

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/users.dat"

void display_menu(const User  *user){
    
    switch (user->role) {
        case ADMIN:
            display_admin_main_menu(user);
            break;
        case AGENT:
            display_agent_main_menu(user);
            break;
        case CLIENT:
            display_client_main_menu(user);
            break;
    }
}

int isUsernameAvailable(const char* username){
    FILE  *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    
    User user;
    while(fread(&user, sizeof(User), 1, file)){
        if(strcmp(user.username, username) == 0){
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

// Function to create a user
void createUser(const char* username, const char* password, UserRole role) {
    if (!isUsernameAvailable(username)) {
        printf("Error: Username '%s' is already taken.\n", username);
        return;
    }
    
    User newUser;
    strncpy(newUser.username, username, sizeof(newUser.username) -1);
    newUser.username[sizeof(newUser.username) - 1] = '\0'; // Ensure null-terminated string
    strncpy(newUser.password, password, sizeof(newUser.password) -1);
    newUser.password[sizeof(newUser.password) - 1] = '\0'; // Ensure null-terminated string
    newUser.role = role;
    
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);
}

// 
