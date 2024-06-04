#include <stdio.h>
#include "../../utils/utils.h"
#include "../../data_base/data_base.h"

void display_database_menu(const User *user){
    int choice;
    
    clearScreen();

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Listagem de Utilizadores Criados\n");
    printf("2. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            display_all_users_data(user);
            break;
        case 2:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}