#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/utils.h"
#include "../auth/users/user.h"
#include "../clients/clients.h"
#include "../menus/agent_main_menu/agent_main_menu.h"
#include "role_agents.h"

#define FILENAME_TXT "../data/agents.txt"
#define FILENAME_DAT "../data/users.dat"
#define FILENAME_PROPS "../data/properties.txt"
#define FILENAME_REPORT "../data/agents_report.txt"
#define FILENAME_VISITS "../data/visits.txt"
#define FILENAME_CLIENTS "../data/clients.txt"
#define FILENAME_REPORT_FINANCIAL "../data/financial_report.txt"


void swapClients(Client* a, Client* b) {
    Client temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortClients(Client* clients, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(clients[j].name, clients[j + 1].name) > 0) {
                swapClients(&clients[j], &clients[j + 1]);
            }
        }
    }
}

void bubbleSortClientsByNIF(Client* clients, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(clients[j].nif, clients[j + 1].nif) > 0) {
                swapClients(&clients[j], &clients[j + 1]);
            }
        }
    }
}

int binarySearchClientByNIF(Client* clients, int n, const char* nif) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(clients[mid].nif, nif);
        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int propertyExists(int propertyId) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return 0;
    }

    char line[256];
    int id;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%*[^;];%*[^;];%*d", &id);
        if (id == propertyId) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int clientExists(const char* username) {
    FILE* file = fopen(FILENAME_DAT, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de usuários.\n");
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && user.role == CLIENT) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Algoritmo de ordenação de bolha
void listClientsAlphabetically(const User* user) {
    FILE* file = fopen(FILENAME_CLIENTS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }

    Client clients[100];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%19[^;];%19[^;];%9[^;];%49[^;];%8[^;];%10[^;];%3[^;]",
               clients[count].username, clients[count].name, clients[count].nif, clients[count].morada,
               clients[count].contacto, clients[count].dataNascimento, clients[count].idade);
        count++;
    }

    fclose(file);

    bubbleSortClients(clients, count);

    printf("Clientes ordenados por nome:\n");
    printf("============================================\n");
    for (int i = 0; i < count; i++) {
        printf("Username: %s\n", clients[i].username);
        printf("Nome: %s\n", clients[i].name);
        printf("NIF: %s\n", clients[i].nif);
        printf("Morada: %s\n", clients[i].morada);
        printf("Contacto: %s\n", clients[i].contacto);
        printf("Data de Nascimento: %s\n", clients[i].dataNascimento);
        printf("Idade: %s\n", clients[i].idade);
        printf("============================================\n");
    }
    
    
    int choice;
    printf("============================================\n");
    printf("1. Voltar ao menu principal\n");
    printf("2. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            display_agent_main_menu(user);
            break;
        case 2:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}

// Algoritmo de pesquisa binária
void searchClientByNIF(const User* user) {
    FILE* file = fopen(FILENAME_CLIENTS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }

    Client clients[100];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%19[^;];%19[^;];%9[^;];%49[^;];%8[^;];%10[^;];%3[^;]",
               clients[count].username, clients[count].name, clients[count].nif, clients[count].morada,
               clients[count].contacto, clients[count].dataNascimento, clients[count].idade);
        count++;
    }

    fclose(file);

    // Ordenar os clientes por NIF
    bubbleSortClientsByNIF(clients, count);

    char nif[10];
    printf("Insira o NIF que deseja buscar: ");
    scanf("%9s", nif);
    clearBuffer();

    int index = binarySearchClientByNIF(clients, count, nif);
    if (index != -1) {
        printf("Cliente encontrado:\n");
        printf("============================================\n");
        printf("Username: %s\n", clients[index].username);
        printf("Nome: %s\n", clients[index].name);
        printf("NIF: %s\n", clients[index].nif);
        printf("Morada: %s\n", clients[index].morada);
        printf("Contacto: %s\n", clients[index].contacto);
        printf("Data de Nascimento: %s\n", clients[index].dataNascimento);
        printf("Idade: %s\n", clients[index].idade);
    } else {
        printf("============================================\n");
        printf("Cliente com NIF %s não encontrado.\n", nif);
    }
    
    int choice;
    printf("============================================\n");
    printf("1. Procurar outro cliente\n");
    printf("2. Voltar ao menu principal\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            searchClientByNIF(user);
            break;
        case 2:
            display_agent_main_menu(user);
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
    
}

void initVisitList(VisitList* visitList) {
    visitList->head = NULL;
    visitList->tail = NULL;
}

void addVisit(VisitList* visitList, const char* date, const char* time, int propertyId, const char* clientUsername, VisitStatus status, VisitType tipo, const char* agentUsername) {
    Visit* newVisit = (Visit*)malloc(sizeof(Visit));
    if (!newVisit) {
        printf("Erro ao alocar memória para a nova visita.\n");
        return;
    }

    strcpy(newVisit->date, date);
    strcpy(newVisit->time, time);
    newVisit->propertyId = propertyId;
    strcpy(newVisit->clientUsername, clientUsername);
    newVisit->status = status;
    newVisit->tipo = tipo;
    strcpy(newVisit->agentUsername, agentUsername);
    newVisit->next = NULL;
    newVisit->prev = visitList->tail;

    if (visitList->tail) {
        visitList->tail->next = newVisit;
    } else {
        visitList->head = newVisit;
    }
    visitList->tail = newVisit;
}

void loadVisitsFromFile(VisitList* visitList) {
    FILE* file = fopen(FILENAME_VISITS, "r");
    if (file == NULL) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Visit* newVisit = (Visit*)malloc(sizeof(Visit));
        if (!newVisit) {
            printf("Erro ao alocar memória para a visita.\n");
            fclose(file);
            return;
        }
        sscanf(line, "%19[^;];%10[^;];%5[^;];%d;%19[^;];%d;%d",
               newVisit->agentUsername, newVisit->date, newVisit->time, &newVisit->propertyId, newVisit->clientUsername, (int*)&newVisit->status, (int*)&newVisit->tipo);
        newVisit->next = NULL;
        newVisit->prev = visitList->tail;

        if (visitList->tail) {
            visitList->tail->next = newVisit;
        } else {
            visitList->head = newVisit;
        }
        visitList->tail = newVisit;
    }

    fclose(file);
}

void saveVisitsToFile(VisitList* visitList) {
    FILE* file = fopen(FILENAME_VISITS, "w");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de visitas.\n");
        return;
    }

    Visit* current = visitList->head;
    while (current) {
        fprintf(file, "%s;%s;%s;%d;%s;%d;%d\n",
                current->agentUsername,
                current->date,
                current->time,
                current->propertyId,
                current->clientUsername,
                current->status,
                current->tipo);
        current = current->next;
    }

    fclose(file);
}

int isVisitSlotAvailable(VisitList* visitList, const char* date, const char* time, const char* agentUsername, int propertyId) {
    Visit* current = visitList->head;
    while (current) {
        if (strcmp(current->date, date) == 0 && strcmp(current->time, time) == 0) {
            if (strcmp(current->agentUsername, agentUsername) == 0 || current->propertyId == propertyId) {
                return 0; // Slot ocupado pelo mesmo agente ou na mesma propriedade
            }
        }
        current = current->next;
    }
    return 1; // Slot disponível
}

int countVisitsOnDate(VisitList* visitList, const char* date, const char* agentUsername) {
    int count = 0;
    Visit* current = visitList->head;
    while (current) {
        if (strcmp(current->date, date) == 0 && strcmp(current->agentUsername, agentUsername) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int isPropertyAnunciada(int propertyId) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return 0;
    }

    char line[256];
    int id, status;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%*[^;];%*[^;];%d", &id, &status);
        if (id == propertyId && status == 1) { // 1 represents ANUNCIADA
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int isAgentAssociatedWithProperty(int propertyId, const char* agentUsername) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return 0;
    }

    char line[256];
    int id;
    char agente[20];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%19[^;];%*[^;];%*d", &id, agente);
        if (id == propertyId && strcmp(agente, agentUsername) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

int isClientPropertyOwner(int propertyId, const char* clientUsername) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return 0;
    }

    char line[256];
    int id;
    char proprietario[20];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%*[^;];%19[^;];%*d", &id, proprietario);
        if (id == propertyId && strcmp(proprietario, clientUsername) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void scheduleVisit(VisitList* visitList, const User* user) {
    char currentDate[11];
    getCurrentDate(currentDate);

    while (1) {
        char date[11], visitTime[6], clientUsername[20];
        int propertyId;

        printf("Agendar uma visita\n");
        printf("============================================\n");

        // Verificação da data da visita
        while (1) {
            printf("Insira a data da visita (dd/mm/aaaa): ");
            scanf("%10s", date);
            clearBuffer();

            if (!isValidDate(date)) {
                printf("Data inválida. Por favor, insira uma data válida no formato dd/mm/aaaa.\n");
                continue;
            }

            if (compareDates(date, currentDate) < 0) {
                printf("A data da visita não pode ser anterior à data de hoje.\n");
                continue;
            }
            break;
        }

        // Verificação da hora da visita
        while (1) {
            printf("Insira a hora da visita (hh:mm): ");
            scanf("%5s", visitTime);
            clearBuffer();

            if (!isValidTime(visitTime)) {
                printf("Hora inválida. Por favor, insira uma hora válida no formato hh:mm.\n");
                continue;
            }

            if (compareDates(date, currentDate) == 0) { // Se a data é hoje, verificar hora
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                char currentTime[6];
                sprintf(currentTime, "%02d:%02d", local->tm_hour, local->tm_min);
                if (strcmp(visitTime, currentTime) <= 0) {
                    printf("A hora da visita não pode ser anterior à hora atual.\n");
                    continue;
                }
            }
            break;
        }

        // Verificação do ID da propriedade
        while (1) {
            printf("Insira o ID da propriedade a visitar: ");
            scanf("%d", &propertyId);
            clearBuffer();

            if (!propertyExists(propertyId)) {
                printf("ID da propriedade não encontrado. Por favor, insira um ID de propriedade válido.\n");
                continue;
            }

            if (!isPropertyAnunciada(propertyId)) {
                printf("A propriedade não está anunciada. Por favor, escolha uma propriedade anunciada.\n");
                continue;
            }

            // Verificar se o agente é o mesmo associado à propriedade
            if (!isAgentAssociatedWithProperty(propertyId, user->username)) {
                printf("Você não é o agente associado a esta propriedade. Apenas o agente responsável pode marcar visitas.\n");
                continue;
            }
            break;
        }

        // Verificação do username do cliente
        while (1) {
            printf("Insira o username do cliente: ");
            scanf("%19s", clientUsername);
            clearBuffer();

            if (!clientExists(clientUsername)) {
                printf("Username do cliente não encontrado. Por favor, insira um username válido.\n");
                continue;
            }

            // Verificar se o cliente não é o proprietário da propriedade
            if (isClientPropertyOwner(propertyId, clientUsername)) {
                printf("O cliente é o proprietário da propriedade. Não é possível agendar uma visita para o proprietário.\n");
                continue;
            }
            break;
        }

        // Verificação de sobreposição de visitas, permitindo visitas no mesmo horário se o agente for diferente e a propriedade for diferente
        if (!isVisitSlotAvailable(visitList, date, visitTime, user->username, propertyId)) {
            printf("Já existe uma visita agendada para este horário com o mesmo agente ou na mesma propriedade. Por favor, escolha outro horário.\n");
            continue;
        }

        // Verificação do limite de visitas por dia
        if (countVisitsOnDate(visitList, date, user->username) >= 4) {
            printf("O agente já tem 4 visitas agendadas para esta data. Por favor, escolha outra data.\n");
            continue;
        }

        addVisit(visitList, date, visitTime, propertyId, clientUsername, AGENDADA, POR_ANUNCIO, user->username);
        saveVisitsToFile(visitList);

        printf("Visita agendada com sucesso!\n");

        int choice;
        printf("============================================\n");
        printf("1. Agendar outra visita\n");
        printf("2. Voltar ao menu principal\n");
        printf("3. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            continue;
        } else if (choice == 2) {
            display_agent_main_menu(user);
            break;
        } else if (choice == 3) {
            exit_system();
            break;
        } else {
            printf("Opção inválida\n");
        }
    }
}

int compareTimes(const char* time1, const char* time2) {
    int hour1, minute1, hour2, minute2;
    sscanf(time1, "%d:%d", &hour1, &minute1);
    sscanf(time2, "%d:%d", &hour2, &minute2);

    if (hour1 != hour2) {
        return hour1 - hour2;
    }
    return minute1 - minute2;
}

void loadProperties(Property** properties, int* propertyCount) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Property* newProperty = (Property*)malloc(sizeof(Property));
        sscanf(line, "%d;%49[^;];%54[^;];%lf;%10[^;];%19[^;];%19[^;];%d",
               &newProperty->id, newProperty->morada, newProperty->descricao, &newProperty->preco,
               newProperty->data, newProperty->agente, newProperty->proprietario, (int*)&newProperty->status);
        properties[(*propertyCount)++] = newProperty;
    }

    fclose(file);
}

void loadClients(Client** clients, int* clientCount) {
    FILE* file = fopen(FILENAME_CLIENTS, "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Client* newClient = (Client*)malloc(sizeof(Client));
        sscanf(line, "%19[^;];%19[^;];%9[^;];%49[^;];%8[^;];%10[^;];%3s",
               newClient->username, newClient->name, newClient->nif, newClient->morada,
               newClient->contacto, newClient->dataNascimento, newClient->idade);
        clients[(*clientCount)++] = newClient;
    }

    fclose(file);
}

void listVisits(VisitList* visitList, const User* user) {
    char date[11];
    int today;

    printf("Listar visitas\n");
    printf("============================================\n");
    printf("1. Listar visitas de hoje\n");
    printf("2. Listar visitas de um determinado dia\n");
    printf("3. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &today);
    clearBuffer();

    if (today == 1) {
        getCurrentDate(date);
    } else if (today == 2) {
        while (1) {
            printf("Insira a data (dd/mm/aaaa): ");
            scanf("%10s", date);
            clearBuffer();
            if (isValidDate(date)) {
                break;
            } else {
                printf("Data inválida. Por favor, insira uma data válida no formato dd/mm/aaaa.\n");
            }
        }
    } else if (today == 3) {
        display_agent_main_menu(user);
        return;
    } else {
        printf("Opção inválida. Retornando ao menu principal.\n");
        return;
    }

    // Carregar propriedades e clientes
    Property* properties[100];
    int propertyCount = 0;
    loadProperties(properties, &propertyCount);

    Client* clients[100];
    int clientCount = 0;
    loadClients(clients, &clientCount);

    // Filtrar e ordenar visitas
    Visit* visits[100];
    int visitCount = 0;
    Visit* current = visitList->head;
    while (current) {
        if (strcmp(current->date, date) == 0 && strcmp(current->agentUsername, user->username) == 0) {
            visits[visitCount++] = current;
        }
        current = current->next;
    }

    // Ordenar visitas por hora
    for (int i = 0; i < visitCount - 1; i++) {
        for (int j = i + 1; j < visitCount; j++) {
            if (compareTimes(visits[i]->time, visits[j]->time) > 0) {
                Visit* temp = visits[i];
                visits[i] = visits[j];
                visits[j] = temp;
            }
        }
    }

    // Exibir visitas
    printf("============================================\n");
    printf("Visitas para %s\n", date);
    printf("============================================\n");
    for (int i = 0; i < visitCount; i++) {
        Visit* visit = visits[i];
        Property* property = NULL;
        Client* client = NULL;

        // Buscar propriedade
        for (int j = 0; j < propertyCount; j++) {
            if (properties[j]->id == visit->propertyId) {
                property = properties[j];
                break;
            }
        }

        // Buscar cliente
        for (int j = 0; j < clientCount; j++) {
            if (strcmp(clients[j]->username, visit->clientUsername) == 0) {
                client = clients[j];
                break;
            }
        }

        if (property && client) {
            printf("Hora: %s\n", visit->time);
            printf("Propriedade: %s, %s, %.2f €, Proprietário: %s\n", property->morada, property->descricao, property->preco, property->proprietario);
            printf("Cliente: %s, %s anos, NIF: %s\n", client->name, client->idade, client->nif);
            printf("============================================\n");
        }
    }

    // Liberar memória alocada
    for (int i = 0; i < propertyCount; i++) {
        free(properties[i]);
    }
    for (int i = 0; i < clientCount; i++) {
        free(clients[i]);
    }

    listVisits(visitList, user);
}

void listVisitsByClient(VisitList* visitList, const User* user) {
    char clientUsername[20];

    printf("Listar visitas por cliente\n");
    printf("============================================\n");
    printf("Insira o username do cliente: ");
    scanf("%19s", clientUsername);
    clearBuffer();

    // Verificar se o cliente existe
    if (!clientExists(clientUsername)) {
        while (1) {
            printf("Cliente não encontrado. Deseja tentar novamente?\n");
            printf("1. Sim\n");
            printf("2. Não\n");
            int choice;
            scanf("%d", &choice);
            clearBuffer();
            if (choice == 1) {
                listVisitsByClient(visitList, user);
            } else if (choice == 2) {
                display_agent_main_menu(user);
            } else {
                printf("Opção inválida\n");
            }
        }
    }

    // Carregar propriedades e clientes
    Property* properties[100];
    int propertyCount = 0;
    loadProperties(properties, &propertyCount);

    Client* clients[100];
    int clientCount = 0;
    loadClients(clients, &clientCount);

    // Filtrar visitas por cliente e agente
    Visit* visits[100];
    int visitCount = 0;
    Visit* current = visitList->head;
    while (current) {
        if (strcmp(current->clientUsername, clientUsername) == 0 && strcmp(current->agentUsername, user->username) == 0) {
            visits[visitCount++] = current;
        }
        current = current->next;
    }

    // Ordenar visitas por data e hora
    for (int i = 0; i < visitCount - 1; i++) {
        for (int j = i + 1; j < visitCount; j++) {
            if (compareDates(visits[i]->date, visits[j]->date) > 0 ||
                (compareDates(visits[i]->date, visits[j]->date) == 0 && compareTimes(visits[i]->time, visits[j]->time) > 0)) {
                Visit* temp = visits[i];
                visits[i] = visits[j];
                visits[j] = temp;
            }
        }
    }

    // Exibir visitas
    printf("Visitas do cliente %s\n", clientUsername);
    printf("============================================\n");
    for (int i = 0; i < visitCount; i++) {
        Visit* visit = visits[i];
        Property* property = NULL;
        Client* client = NULL;

        // Buscar propriedade
        for (int j = 0; j < propertyCount; j++) {
            if (properties[j]->id == visit->propertyId) {
                property = properties[j];
                break;
            }
        }

        // Buscar cliente
        for (int j = 0; j < clientCount; j++) {
            if (strcmp(clients[j]->username, visit->clientUsername) == 0) {
                client = clients[j];
                break;
            }
        }

        if (property && client) {
            printf("Data: %s, Hora: %s\n", visit->date, visit->time);
            printf("Propriedade: %s, %s, %.2f €, Proprietário: %s\n", property->morada, property->descricao, property->preco, property->proprietario);
            printf("Cliente: %s, %s anos, NIF: %s\n", client->name, client->idade, client->nif);
            printf("============================================\n");
        }
    }

    // Liberar memória alocada
    for (int i = 0; i < propertyCount; i++) {
        free(properties[i]);
    }
    for (int i = 0; i < clientCount; i++) {
        free(clients[i]);
    }

    int choice;
    printf("============================================\n");
    printf("1. Listar visitas de outro cliente\n");
    printf("2. Voltar ao menu principal\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    switch (choice) {
        case 1:
            listVisitsByClient(visitList, user);
            break;
        case 2:
            display_agent_main_menu(user);
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}

void listVisitsByPropertyType(VisitList* visitList, const User* user) {
    int statusChoice;

    printf("Listar visitas por tipo de propriedade\n");
    printf("============================================\n");
    printf("1. Listar visitas para propriedades ANUNCIADAS\n");
    printf("2. Listar visitas para propriedades CASA_ABERTA\n");
    printf("Escolha uma opção: ");
    scanf("%d", &statusChoice);
    clearBuffer();

    if (statusChoice != 1 && statusChoice != 2) {
        printf("Opção inválida. Retornando ao menu principal.\n");
        return;
    }

    PropertyStatus selectedStatus = (statusChoice == 1) ? ANUNCIADA : CASA_ABERTA;

    // Carregar propriedades e clientes
    Property* properties[100];
    int propertyCount = 0;
    loadProperties(properties, &propertyCount);

    Client* clients[100];
    int clientCount = 0;
    loadClients(clients, &clientCount);

    // Filtrar visitas por tipo de propriedade e agente
    Visit* visits[100];
    int visitCount = 0;
    Visit* current = visitList->head;
    while (current) {
        for (int i = 0; i < propertyCount; i++) {
            if (properties[i]->id == current->propertyId && properties[i]->status == selectedStatus && strcmp(current->agentUsername, user->username) == 0) {
                visits[visitCount++] = current;
                break;
            }
        }
        current = current->next;
    }

    // Ordenar visitas por data e hora
    for (int i = 0; i < visitCount - 1; i++) {
        for (int j = i + 1; j < visitCount; j++) {
            if (compareDates(visits[i]->date, visits[j]->date) > 0 ||
                (compareDates(visits[i]->date, visits[j]->date) == 0 && compareTimes(visits[i]->time, visits[j]->time) > 0)) {
                Visit* temp = visits[i];
                visits[i] = visits[j];
                visits[j] = temp;
            }
        }
    }

    // Exibir visitas
    printf("Visitas para propriedades %s\n", (selectedStatus == ANUNCIADA) ? "ANUNCIADAS" : "CASA_ABERTA");
    printf("============================================\n");
    for (int i = 0; i < visitCount; i++) {
        Visit* visit = visits[i];
        Property* property = NULL;
        Client* client = NULL;

        // Buscar propriedade
        for (int j = 0; j < propertyCount; j++) {
            if (properties[j]->id == visit->propertyId) {
                property = properties[j];
                break;
            }
        }

        // Buscar cliente
        for (int j = 0; j < clientCount; j++) {
            if (strcmp(clients[j]->username, visit->clientUsername) == 0) {
                client = clients[j];
                break;
            }
        }

        if (property && client) {
            printf("Data: %s, Hora: %s\n", visit->date, visit->time);
            printf("Propriedade: %s, %s, %.2f €, Proprietário: %s\n", property->morada, property->descricao, property->preco, property->proprietario);
            printf("Cliente: %s, %s anos, NIF: %s\n", client->name, client->idade, client->nif);
            printf("============================================\n");
        }
    }

    // Liberar memória alocada
    for (int i = 0; i < propertyCount; i++) {
        free(properties[i]);
    }
    for (int i = 0; i < clientCount; i++) {
        free(clients[i]);
    }

    int choice;
    printf("============================================\n");
    printf("1. Listar visitas de outro tipo de propriedade\n");
    printf("2. Voltar ao menu principal\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            listVisitsByPropertyType(visitList, user);
            break;
        case 2:
            display_agent_main_menu(user);
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}

void updatePropertyStatus(int propertyId, PropertyStatus newStatus, const char* newOwner) {
    FILE* file = fopen(FILENAME_PROPS, "r");
    FILE* tempFile = fopen("temp_props.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Property property;
        sscanf(line, "%d;%49[^;];%54[^;];%lf;%10[^;];%19[^;];%19[^;];%d",
               &property.id, property.morada, property.descricao, &property.preco,
               property.data, property.agente, property.proprietario, (int*)&property.status);

        if (property.id == propertyId) {
            property.status = newStatus;
            strcpy(property.proprietario, newOwner);
        }

        fprintf(tempFile, "%d;%s;%s;%.2f;%s;%s;%s;%d\n", property.id, property.morada, property.descricao,
                property.preco, property.data, property.agente, property.proprietario, property.status);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME_PROPS);
    rename("temp_props.txt", FILENAME_PROPS);
}

void simulateVisit(VisitList* visitList, const User* user) {
    char date[11], visitTime[6], currentDate[11];
    int propertyId;

    getCurrentDate(currentDate);

    while (1) {
        printf("Simular uma visita\n");
        printf("============================================\n");

        // Verificação da data da visita
        while (1) {
            printf("Insira a data da visita (dd/mm/aaaa): ");
            scanf("%10s", date);
            clearBuffer();

            if (!isValidDate(date)) {
                printf("Data inválida. Por favor, insira uma data válida no formato dd/mm/aaaa.\n");
                continue;
            }

            if (compareDates(date, currentDate) > 0) {
                printf("A data da visita não pode ser futura.\n");
                continue;
            }
            break;
        }

        // Verificação da hora da visita
        while (1) {
            printf("Insira a hora da visita (hh:mm): ");
            scanf("%5s", visitTime);
            clearBuffer();

            if (!isValidTime(visitTime)) {
                printf("Hora inválida. Por favor, insira uma hora válida no formato hh:mm.\n");
                continue;
            }

            if (compareDates(date, currentDate) == 0) {
                // Verificação se a hora é no futuro no dia de hoje
                time_t now = time(NULL);
                struct tm *now_tm = localtime(&now);
                char currentTime[6];
                sprintf(currentTime, "%02d:%02d", now_tm->tm_hour, now_tm->tm_min);

                if (compareTimes(visitTime, currentTime) > 0) {
                    printf("A hora da visita não pode ser futura no dia de hoje.\n");
                    continue;
                }
            }

            break;
        }

        // Verificação do ID da propriedade
        while (1) {
            printf("Insira o ID da propriedade a visitar: ");
            scanf("%d", &propertyId);
            clearBuffer();

            if (!propertyExists(propertyId)) {
                printf("ID da propriedade não encontrado. Por favor, insira um ID de propriedade válido.\n");
                continue;
            }
            break;
        }

        // Encontrar a visita correspondente
        Visit* current = visitList->head;
        Visit* targetVisit = NULL;
        while (current) {
            if (strcmp(current->date, date) == 0 && strcmp(current->time, visitTime) == 0 && current->propertyId == propertyId) {
                targetVisit = current;
                break;
            }
            current = current->next;
        }

        if (!targetVisit) {
            printf("Visita não encontrada para a data, hora e propriedade especificadas.\n");
            continue;
        }

        // Verificar se a visita é do agente logado
        if (strcmp(targetVisit->agentUsername, user->username) != 0) {
            printf("Você não tem permissão para alterar esta visita. Esta visita pertence a outro agente.\n");
            continue;
        }

        // Verificar se a visita já foi atualizada anteriormente
        if (targetVisit->status != AGENDADA) {
            printf("A visita já foi atualizada anteriormente. Status atual: %d\n", targetVisit->status);
            printf("A retomar ao menu principal...\n");
            printf("============================================\n");
            display_agent_main_menu(user);
            return;
        }

        // Atualizar o status da visita
        int choice;
        printf("============================================\n");
        printf("Qual foi o resultado da visita?\n");
        printf("1. Finalizada\n");
        printf("2. Cliente não compareceu\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            targetVisit->status = FINALIZADA;

            // Perguntar o resultado da visita finalizada
            printf("Qual foi o resultado da visita finalizada?\n");
            printf("1. Cliente comprou a propriedade\n");
            printf("2. Cliente arrendou a propriedade\n");
            printf("3. Cliente não fez nenhuma transação\n");
            printf("Escolha uma opção: ");
            int resultChoice;
            scanf("%d", &resultChoice);
            clearBuffer();

            if (resultChoice == 1) {
                updatePropertyStatus(propertyId, VENDIDA, targetVisit->clientUsername);
                printf("Propriedade atualizada para o estado VENDIDA.\n");
            } else if (resultChoice == 2) {
                updatePropertyStatus(propertyId, ARRENDADA, targetVisit->clientUsername);
                printf("Propriedade atualizada para o estado ARRENDADA.\n");
            } else if (resultChoice == 3) {
                printf("Propriedade mantém o estado atual.\n");
            } else {
                printf("Opção inválida. A propriedade mantém o estado atual.\n");
            }
        } else if (choice == 2) {
            targetVisit->status = NAO_COMPARECEU;
        } else {
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
            continue;
        }

        // Salvar as visitas atualizadas no arquivo
        saveVisitsToFile(visitList);

        printf("Status da visita atualizado com sucesso!\n");

        int choice2;
        printf("============================================\n");
        printf("1. Simular outra visita\n");
        printf("2. Voltar ao menu principal\n");
        printf("3. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice2);
        clearBuffer();

        if (choice2 == 1) {
            continue;
        } else if (choice2 == 2) {
            display_agent_main_menu(user);
            break;
        } else if (choice2 == 3) {
            exit_system();
            break;
        } else {
            printf("Opção inválida\n");
        }
    }
}

void listNoShowVisits(VisitList* visitList, const User* user) {
    while (1) {
        printf("Listar visitas onde o cliente não compareceu\n");
        printf("============================================\n");

        // Carregar propriedades e clientes
        Property* properties[100];
        int propertyCount = 0;
        loadProperties(properties, &propertyCount);

        Client* clients[100];
        int clientCount = 0;
        loadClients(clients, &clientCount);

        // Filtrar visitas onde o cliente não compareceu e agente atual
        Visit* visits[100];
        int visitCount = 0;
        Visit* current = visitList->head;
        while (current) {
            if (current->status == NAO_COMPARECEU && strcmp(current->agentUsername, user->username) == 0) {
                visits[visitCount++] = current;
            }
            current = current->next;
        }

        if (visitCount == 0) {
            printf("Nenhuma visita encontrada onde o cliente não compareceu.\n");
            display_agent_main_menu(user);
        }

        // Ordenar visitas por data e hora
        for (int i = 0; i < visitCount - 1; i++) {
            for (int j = i + 1; j < visitCount; j++) {
                if (compareDates(visits[i]->date, visits[j]->date) > 0 ||
                    (compareDates(visits[i]->date, visits[j]->date) == 0 && compareTimes(visits[i]->time, visits[j]->time) > 0)) {
                    Visit* temp = visits[i];
                    visits[i] = visits[j];
                    visits[j] = temp;
                }
            }
        }

        // Exibir visitas
        printf("Visitas onde o cliente não compareceu\n");
        printf("============================================\n");
        for (int i = 0; i < visitCount; i++) {
            Visit* visit = visits[i];
            Property* property = NULL;
            Client* client = NULL;

            // Buscar propriedade
            for (int j = 0; j < propertyCount; j++) {
                if (properties[j]->id == visit->propertyId) {
                    property = properties[j];
                    break;
                }
            }

            // Buscar cliente
            for (int j = 0; j < clientCount; j++) {
                if (strcmp(clients[j]->username, visit->clientUsername) == 0) {
                    client = clients[j];
                    break;
                }
            }

            if (property && client) {
                printf("Data: %s, Hora: %s\n", visit->date, visit->time);
                printf("Propriedade: %s, %s, %.2f €, Proprietário: %s\n", property->morada, property->descricao, property->preco, property->proprietario);
                printf("Cliente: %s, %s anos, NIF: %s\n", client->name, client->idade, client->nif);
                printf("============================================\n");
            }
        }

        // Liberar memória alocada
        for (int i = 0; i < propertyCount; i++) {
            free(properties[i]);
        }
        for (int i = 0; i < clientCount; i++) {
            free(clients[i]);
        }

        int choice;
        printf("============================================\n");
        printf("1. Listar novamente\n");
        printf("2. Voltar ao menu principal\n");
        printf("3. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            continue;
        } else if (choice == 2) {
            display_agent_main_menu(user);
            break;
        } else if (choice == 3) {
            exit_system();
            break;
        } else {
            printf("Opção inválida. Retornando ao menu principal.\n");
            display_agent_main_menu(user);
            break;
        }
    }
}

void calculateRevenue(VisitList* visitList, const User* user) {
    char currentDate[11], currentMonth[8];
    getCurrentDate(currentDate);
    strncpy(currentMonth, currentDate + 3, 7);
    currentMonth[7] = '\0';

    double todayRevenue = 0.0;
    double monthRevenue = 0.0;

    Property* properties[100];
    int propertyCount = 0;
    loadProperties(properties, &propertyCount);

    Visit* current = visitList->head;
    while (current) {
        if (current->status == FINALIZADA) {
            Property* property = NULL;
            for (int i = 0; i < propertyCount; i++) {
                if (properties[i]->id == current->propertyId) {
                    property = properties[i];
                    break;
                }
            }

            if (property && (property->status == VENDIDA || property->status == ARRENDADA)) {
                if (compareDates(current->date, currentDate) == 0) {
                    if (property->status == VENDIDA) {
                        todayRevenue += property->preco;
                    } else if (property->status == ARRENDADA) {
                        todayRevenue += property->preco / 12;
                    }
                }

                if (strncmp(current->date + 3, currentMonth, 7) == 0) {
                    if (property->status == VENDIDA) {
                        monthRevenue += property->preco;
                    } else if (property->status == ARRENDADA) {
                        monthRevenue += property->preco / 12;
                    }
                }
            }
        }
        current = current->next;
    }

    printf("============================================\n");
    printf("Faturamento de hoje (%s): %.2f €\n", currentDate, todayRevenue);
    printf("Faturamento do mês (%s): %.2f €\n", currentMonth, monthRevenue);
    printf("============================================\n");

    for (int i = 0; i < propertyCount; i++) {
        free(properties[i]);
    }
    
    display_agent_main_menu(user);
}

void totalVisitsByAgent(VisitList* visitList, const User* user) {
    typedef struct {
        char agentName[20];
        int visitCount;
    } AgentVisitCount;

    AgentVisitCount agents[100];
    int agentCount = 0;

    // Carregar agentes
    FILE* file = fopen(FILENAME_DAT, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de usuários.\n");
        return;
    }

    User tempUser;
    while (fread(&tempUser, sizeof(User), 1, file)) {
        if (tempUser.role == AGENT) {
            strcpy(agents[agentCount].agentName, tempUser.username);
            agents[agentCount].visitCount = 0;
            agentCount++;
        }
    }
    fclose(file);

    // Contar visitas finalizadas realizadas por cada agente
    Visit* current = visitList->head;
    while (current) {
        if (current->status == FINALIZADA) {
            for (int i = 0; i < agentCount; i++) {
                if (strcmp(current->agentUsername, agents[i].agentName) == 0) {
                    agents[i].visitCount++;
                    break;
                }
            }
        }
        current = current->next;
    }

    // Ordenar agentes por número de visitas (ordem decrescente)
    for (int i = 0; i < agentCount - 1; i++) {
        for (int j = i + 1; j < agentCount; j++) {
            if (agents[i].visitCount < agents[j].visitCount) {
                AgentVisitCount temp = agents[i];
                agents[i] = agents[j];
                agents[j] = temp;
            }
        }
    }

    // Exibir o total de visitas realizadas por cada agente
    printf("Total de visitas finalizadas por cada agente\n");
    printf("============================================\n");
    for (int i = 0; i < agentCount; i++) {
        printf("Agente: %s, Total de visitas: %d\n", agents[i].agentName, agents[i].visitCount);
    }
    printf("============================================\n");
    
    display_agent_main_menu(user);
}

void loadUsers(User** users, int* userCount) {
    FILE* file = fopen(FILENAME_DAT, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro de usuários.\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        users[(*userCount)++] = (User*)malloc(sizeof(User));
        memcpy(users[*userCount - 1], &user, sizeof(User));
    }

    fclose(file);
}

void generateFinancialReport(VisitList* visitList, const User* user) {
    int reportType, propertyType;
    char currentDate[11], currentMonth[8];
    getCurrentDate(currentDate);
    strncpy(currentMonth, currentDate + 3, 7);
    currentMonth[7] = '\0';

    printf("Gerar relatório financeiro\n");
    printf("============================================\n");
    printf("1. Relatório de hoje\n");
    printf("2. Relatório do mês\n");
    printf("Escolha uma opção: ");
    scanf("%d", &reportType);
    clearBuffer();

    printf("1. Propriedades VENDIDAS\n");
    printf("2. Propriedades ARRENDADAS\n");
    printf("Escolha uma opção: ");
    scanf("%d", &propertyType);
    clearBuffer();

    PropertyStatus selectedStatus = (propertyType == 1) ? VENDIDA : ARRENDADA;

    double totalRevenue = 0.0;

    Property* properties[100];
    int propertyCount = 0;
    loadProperties(properties, &propertyCount);

    User* users[100];
    int userCount = 0;
    loadUsers(users, &userCount);

    FILE* reportFile = fopen(FILENAME_REPORT_FINANCIAL, "w");
    if (reportFile == NULL) {
        printf("Erro ao abrir o ficheiro de relatório.\n");
        return;
    }

    Visit* current = visitList->head;
    while (current) {
        if (current->status == FINALIZADA) {
            Property* property = NULL;
            for (int i = 0; i < propertyCount; i++) {
                if (properties[i]->id == current->propertyId && properties[i]->status == selectedStatus) {
                    property = properties[i];
                    break;
                }
            }

            if (property) {
                if ((reportType == 1 && compareDates(current->date, currentDate) == 0) ||
                    (reportType == 2 && strncmp(current->date + 3, currentMonth, 7) == 0)) {
                    User* agent = NULL;
                    for (int i = 0; i < userCount; i++) {
                        if (strcmp(users[i]->username, current->agentUsername) == 0) {
                            agent = users[i];
                            break;
                        }
                    }

                    if (selectedStatus == VENDIDA) {
                        totalRevenue += property->preco;
                    } else if (selectedStatus == ARRENDADA) {
                        totalRevenue += property->preco / 12;
                    }

                    fprintf(reportFile, "Relatório gerado no dia %s sobre as propriedades %s\n", currentDate, (selectedStatus == VENDIDA) ? "VENDIDAS" : "ARRENDADAS");
                    fprintf(reportFile, "============================================\n");
                    fprintf(reportFile, "Data: %s, Hora: %s\n", current->date, current->time);
                    fprintf(reportFile, "Propriedade: %s, %s, %.2f €, Proprietário: %s\n", property->morada, property->descricao, property->preco, property->proprietario);
                    fprintf(reportFile, "Agente: %s\n", agent ? agent->username : "Desconhecido");
                    fprintf(reportFile, "============================================\n");
                }
            }
        }
        current = current->next;
    }

    fprintf(reportFile, "Total de receitas: %.2f €\n", totalRevenue);

    fclose(reportFile);

    printf("Relatório gerado com sucesso!\n");

    for (int i = 0; i < propertyCount; i++) {
        free(properties[i]);
    }
    for (int i = 0; i < userCount; i++) {
        free(users[i]);
    }
}