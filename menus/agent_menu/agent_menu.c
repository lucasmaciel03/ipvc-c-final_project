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
    printf("4. Listar Agentes \n");
    printf("5. Listar Agente por username \n");
    printf("6. Listar Agentes por ordem alfabética do nome \n");
    printf("7. Listar Agentes por idade ascendente \n");
    printf("8. Colocar Agente como Indisponível \n");
    printf("9. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
switch(choice){
        case 1:
            createAgent(); //funciona
            break;
        case 2:
            editAgent(); //ainda não funciona
            break;
        case 3:
            deleteAgent(); //funciona
            break;
        case 4:
            loadAgents(); //funciona
            break;
        case 5:
            list_agent_by_name(); //funciona
            break;
        case 6:
            list_agent_by_name(); //funciona
            break;
        case 7:
            list_agent_by_age(); //funciona
            break;
        case 8:
            set_agent_unavailable(); //funciona
            break;
        case 9:
            display_menu(user);
            break;
        case 0:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
    
    
}