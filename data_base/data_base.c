#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"
#include "../auth/users/user.h"
#include "../menus/admin_main_menu/admin_main_menu.h"


#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/users.dat"


void display_all_users_data(const User* user){
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("User logeed in: %s\n", user->username);

    User users;
    while(fread(&users, sizeof(User), 1, file)){
        printf("Username: %s\n", users.username);
        printf("Password: %s\n", users.password);
        printf("Role: %d\n", users.role);
        printf("============================================\n");
    }

//    fclose(file);

    int choice;
    printf("1. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1){
        fclose(file);
        display_admin_main_menu(user);
    } else {
        exit_system();
    }
}
