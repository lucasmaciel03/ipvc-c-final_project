#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"
#include "../agent_menu/agent_menu.h"
#include "../properties_menu/properties_menu.h"
#include "../database_menu/database_menu.h"

void display_admin_main_menu(const User *user){
    int choice;

    clearScreen();
    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Gestão de Propriedades\n");
    printf("2. Cestão de Agentes\n");
    printf("3. Gestão Base de Dados\n");
    printf("4. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            display_properties_menu(user);
            break;
        case 2:
            display_agent_menu(user);
            break;
        case 3:
            display_database_menu(user);
            break;
        case 4:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}