#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"
#include "../../agents/agents.h"

void display_agent_menu(const User *user){
    int choice;

    printf("Gestão de Agentes\n");
    printf("============================================\n");
    printf("1. Criar novo Agente \n");
    printf("2. Editar Agente \n");
    printf("3. Remover Agente \n");
    printf("4. Listar Agente por ID \n");
    printf("5. Listar Agentes por ordem alfabética do nome \n");
    printf("6. Listar Agentes por idade ascendente \n");
    printf("7. Colocar Agente como Indisponível \n");
    printf("8. Voltar\n");
    printf("9. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
switch(choice){
        case 1:
            createAgent();
            break;
        case 2:
            // edit_agent();
            break;
        case 3:
            // remove_agent();
            break;
        case 4:
            // list_agent_by_id();
            break;
        case 5:
            // list_agent_by_name();
            break;
        case 6:
            // list_agent_by_age();
            break;
        case 7:
            // set_agent_unavailable();
            break;
        case 8:
            display_menu(user);
            break;
        case 9:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
    
    
}