#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"

void display_agent_main_menu(const User *user){
    int choice;

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Agendamento e Gestão de Visitas\n");
    printf("2. Gestão de Filas de Espera\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            // estate_menu();
            break;
        case 2:
            // agent_menu();
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}