#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"
#include "../../role_agents/role_agents.h"

void display_agent_main_menu(const User *user){
    int choice;
    
    VisitList visitList;
    initVisitList(&visitList);
    loadVisitsFromFile(&visitList);

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Listar clientes por ordem alfabética de nome\n");
    printf("2. Listar cliente pelo NIF\n");
    printf("3. Agendar uma visita\n");
    printf("4. Listar todas as visitas de hoje ou de um determinado dia\n");
    printf("5. Listar todas as visitas de um determinado cliente\n");
    printf("6. Listar todas as visitas a uma determinada propriedade\n");
    printf("7. Listar todas as visitas onde cliente não compareceu\n");
    printf("8. Faturamento hoje e este mês\n");
    printf("9. Gerar relatório com o total de receitas\n");
    printf("10. Atualizar Visitas\n");
    printf("11. Total de visitas por agente\n");
    printf("12. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            listClientsAlphabetically(user);
            break;
        case 2:
            searchClientByNIF(user);
            break;
        case 3:
            scheduleVisit(&visitList, user);
            break;
        case 4:
            listVisits(&visitList, user);
            break;
        case 5:
            listVisitsByClient(&visitList, user);
            break;
        case 6:
            listVisitsByPropertyType(&visitList, user);
            break;
        case 7:
            listNoShowVisits(&visitList, user);
            break;
        case 8:
            calculateRevenue(&visitList, user);
            break;
        case 9:
            generateFinancialReport(&visitList, user);
            break;
        case 10:
            simulateVisit(&visitList, user);
            break;
        case 11:
            totalVisitsByAgent(&visitList, user);
            break;
        case 12:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}