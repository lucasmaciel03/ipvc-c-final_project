#include <stdio.h>
#include <string.h>
#include "../utils/utils.h"
#include "../auth/users/user.h"
#include "../menus/admin_main_menu/admin_main_menu.h"


#define FILENAME "../data/users.dat"
#define FILENAME_TXT "../data/agents.txt"


void display_all_users_data(const User* user){
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
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

// function to clear all users in .dat
// - except the users with username equals to "lucasmaciel03" and "andremaia95" 
// - add a message (Deseja mesmo apagar todos os utilizadores? (S/N): ) to confirm the action
// - after the action is confirmed, display a message "Utilizadores apagados com sucesso"
void clear_all_users_data(const User* user){
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE *temp_file = fopen("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.dat", "wb");
    if (temp_file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    User users;
    while(fread(&users, sizeof(User), 1, file)){
        if(strcmp(users.username, "lucasmaciel03") == 0 || strcmp(users.username, "andremaia95") == 0){
            fwrite(&users, sizeof(User), 1, temp_file);
        }
    }
    

    fclose(file);
    fclose(temp_file);

    remove(FILENAME);
    rename("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.dat", FILENAME);
    
    // Apaga também toda a informação presente no ficheiro TXT
    FILE *file_txt = fopen(FILENAME_TXT, "w");
    if (file_txt == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fclose(file_txt);
    
    
    printf("Utilizadores apagados com sucesso\n");

    int choice;
    printf("1. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 1){
        display_admin_main_menu(user);
    } else {
        exit_system();
    }
}