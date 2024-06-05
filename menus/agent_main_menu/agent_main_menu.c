#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"

void display_agent_main_menu(const User *user){
    int choice;

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Gerir Clientes\n");
    printf("2. Listar clientes por ordem alfabética de nome\n");
    printf("3. Listar cliente pelo NIF\n");
    printf("4. Agendar uma visita\n");
    printf("5. Listar todas as visitas de hoje ou de um determinado dia\n");
    printf("6. Listar todas as visitas de um determinado cliente\n");
    printf("7. Listar todas as visitas a uma determinada propriedade\n");
    printf("8. Listar todas as visitas onde cliente não compareceu\n");
    printf("9. Faturamento hoje e este mês\n");
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