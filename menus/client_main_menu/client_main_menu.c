#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"

void display_client_main_menu(const User *user){
    int choice;

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Procurar Propriedadea\n");
    printf("2. Simulação de Visita\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            // estate_menu();
            break;
        case 2:
            // visit_simulation();
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}