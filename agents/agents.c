#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "agents.h"
#include "../utils/utils.h"
#include "../auth/users/user.h"
#include "../menus/agent_menu/agent_menu.h"
#define FILENAME_TXT "../data/agents.txt"
#define FILENAME_DAT "../data/users.dat"
#define FILENAME_PROPS "../data/properties.txt"
#define FILENAME_REPORT "../data/agents_report.txt"

Agent agents[MAX_AGENTS];
int numAgents = 0;

int agentExistsv2(const char* username) {
    FILE* file = fopen(FILENAME_DAT, "rb");
    if (file == NULL) {
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (strcmp(user.username, username) == 0 && user.role == AGENT) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// function to verify if user is available
int isAgentAvailable(const char* username) {
    FILE* file = fopen(FILENAME_TXT, "r");
    if (file == NULL) {
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        if (strcmp(token, username) == 0) {
            // Check if the agent is available
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            token = strtok(NULL, ";");
            if (atoi(token) == DISPONIVEL) {
                fclose(file);
                return 1;
            }
        }
    }
    
    fclose(file);
    return 0;
}

int countAgents(){
    FILE  *file = fopen(FILENAME_DAT, "r");
    if(file == NULL){
        return 0;
    }
    
    User user;
    int count = 0;
    while(fread(&user, sizeof(User), 1, file) == 1){
        if(user.role == AGENT){
            count++;
        }
    }
    fclose(file);
    return count;
}

void calculateAge(const char *dataNascimento, char *idade) {
    
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int currentYear = local->tm_year + 1900;
    int currentMonth = local->tm_mon + 1;
    int currentDay = local->tm_mday;

    int birthYear, birthMonth, birthDay;
    sscanf(dataNascimento, "%d/%d/%d", &birthDay, &birthMonth, &birthYear);

    int age = currentYear - birthYear;
    if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
        age--;
    }

    sprintf(idade, "%d", age);
}

void createAgent(const User *user) {
    if (countAgents() == MAX_AGENTS) {
        printf("Número máximo de agentes atingido\n");
        return;
    }
    
    User  newUser;
    Agent  newAgent;

    printf("Insira os dados do Agente (0 para voltar)\n");
    printf("============================================\n");
    
    // Solicitar username e password
    do {
        printf("Insira o Username do agente: ");
        if (fgets(newUser.username, sizeof(newUser.username), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newUser.username[strcspn(newUser.username, "\n")] = 0;
        trimWhitespace(newUser.username);
        if (strcmp(newUser.username, "0") == 0) {
            display_agent_menu(user);
        }
        if (strlen(newUser.username) == 0 || newUser.username[0] == ' ') {
            printf("Erro: O username deve ser definido\n");
        }
        if (agentExistsv2(newUser.username)) {
            printf("Erro: O username já existe\n");
        }
    } while (strlen(newUser.username) == 0 || newUser.username[0] == ' ' || agentExistsv2(newUser.username));
    
    do {
        printf("Insira a Password do Agente: ");
        if (fgets(newUser.password, sizeof(newUser.password), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newUser.password[strcspn(newUser.password, "\n")] = 0;
        trimWhitespace(newUser.password);
        if (strlen(newUser.password) == 0 || newUser.password[0] == ' ') {
            printf("Erro: A password deve ser definida\n");
        }
    } while (strlen(newUser.password) == 0 || newUser.password[0] == ' ');
    
    newUser.role = AGENT;
    
    // Solicitar os restantes dados
    do {
        printf("Insira o Nome do Agente: ");
        if (fgets(newAgent.name, sizeof(newAgent.name), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.name[strcspn(newAgent.name, "\n")] = 0;
        trimWhitespace(newAgent.name);
        if (strlen(newAgent.name) == 0 || newAgent.name[0] == ' ') {
            printf("Erro: O nome deve ser definido\n");
        }
    } while (strlen(newAgent.name) == 0 || newAgent.name[0] == ' ');
    
    do {
        printf("Insira o NIF do Agente: ");
        if (fgets(newAgent.nif, sizeof(newAgent.nif), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.nif[strcspn(newAgent.nif, "\n")] = 0;
        trimWhitespace(newAgent.nif);
        if (strlen(newAgent.nif) == 0 || newAgent.nif[0] == ' ') {
            printf("Erro: O NIF deve ser definido\n");
        }
    } while (strlen(newAgent.nif) == 0 || newAgent.nif[0] == ' ');
    
    do {
        printf("Insira a Morada do Agente: ");
        if (fgets(newAgent.morada, sizeof(newAgent.morada), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.morada[strcspn(newAgent.morada, "\n")] = 0;
        trimWhitespace(newAgent.morada);
        if (strlen(newAgent.morada) == 0 || newAgent.morada[0] == ' ') {
            printf("Erro: A morada deve ser definida\n");
        }
    } while (strlen(newAgent.morada) == 0 || newAgent.morada[0] == ' ');
    
    do {
        printf("Insira o Contacto do Agente: ");
        if (fgets(newAgent.contacto, sizeof(newAgent.contacto), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.contacto[strcspn(newAgent.contacto, "\n")] = 0;
        trimWhitespace(newAgent.contacto);
        if (strlen(newAgent.contacto) == 0 || newAgent.contacto[0] == ' ') {
            printf("Erro: O contacto deve ser definido\n");
        }
    } while (strlen(newAgent.contacto) == 0 || newAgent.contacto[0] == ' ');
    
    do {
        printf("Insira a Data de Nascimento do Agente: ");
        if (fgets(newAgent.dataNascimento, sizeof(newAgent.dataNascimento), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.dataNascimento[strcspn(newAgent.dataNascimento, "\n")] = 0;
        trimWhitespace(newAgent.dataNascimento);
        if (strlen(newAgent.dataNascimento) == 0 || newAgent.dataNascimento[0] == ' ' || !isValidDate(newAgent.dataNascimento)) {
            printf("Erro: A data de nascimento deve ser válida no formato dd/mm/aaaa\n");
        }
    } while (strlen(newAgent.dataNascimento) == 0 || newAgent.dataNascimento[0] == ' ' || !isValidDate(newAgent.dataNascimento));
    
    calculateAge(newAgent.dataNascimento, newAgent.idade);
    
    newAgent.status = DISPONIVEL;
    
    // Guardar os dados no ficheiro .dat
    FILE* file = fopen(FILENAME_DAT, "ab");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        return;
    } else {
        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);
    }
    
    // Guardar os dados no ficheiro .txt
    file = fopen(FILENAME_TXT, "a");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        return;
    } else {
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%d\n",
                newUser.username, newAgent.name, newAgent.nif,
                newAgent.morada, newAgent.contacto, newAgent.dataNascimento,
                newAgent.idade, newAgent.status);
        fclose(file);
    } 
    
    printf("Agente criado com sucesso!\n");
    
    // Perguntar ao utilizador se deseja criar outro agente
    int choice;
    printf("============================================\n");
    printf("1. Criar outro agente\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        createAgent(user);
    } else if (choice == 2) {
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

void printAgents(const User* user, int showMenu){
    clearScreen();
    
    FILE *file = fopen(FILENAME_TXT, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }

    printf("Listagem de Agentes\n");
    printf("============================================\n");
    char line[1024];
    while(fgets(line, sizeof(line), file)){
        char* token = strtok(line, ";");
        printf("Username: %s\n", token);
        token = strtok(NULL, ";");
        printf("Nome: %s\n", token);
        token = strtok(NULL, ";");
        printf("NIF: %s\n", token);
        token = strtok(NULL, ";");
        printf("Morada: %s\n", token);
        token = strtok(NULL, ";");
        printf("Contacto: %s\n", token);
        token = strtok(NULL, ";");
        printf("Data de Nascimento: %s\n", token);
        token = strtok(NULL, ";");
        printf("Idade: %s\n", token);
        token = strtok(NULL, ";");
        // Verificar se o agente está disponível ou indisponível
        if (atoi(token) == DISPONIVEL) {
            printf("Estado: Disponível\n");
        } else {
            printf("Estado: Indisponível\n");
        }
        printf("============================================\n");
    }
    
    fclose(file);
    
    if(showMenu){
        int choice;
        printf("1. Voltar\n");
        printf("0. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();
        
        if(choice == 1){
            display_agent_menu(user);
        } else {
            exit_system();
        }
    }
    
}

void editAgent(const User* user) {
    clearScreen();

    // Chama a função printAgents sem mostrar o menu
    printAgents(user, 0);

    char username[20];
    int attempts = 0;
    do {
        if (attempts > 0) {
            printf("============================================\n");
            printf("Erro: O username do agente escolhido não existe\n");
        } else {
            printf("\n");
        }
        printf("============================================\n");
        printf("Insira o username do agente que deseja editar (0 para voltar): ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove newline character

        if (strcmp(username, "0") == 0) {
            display_agent_menu(user);
            return;
        }

        if (!agentExistsv2(username)) {
            attempts++;
        } else {
            break;
        }
    } while (1);

    FILE* file = fopen(FILENAME_TXT, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de agentes\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro: Não foi possível criar o ficheiro temporário\n");
        fclose(file);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char lineCopy[1024];
        strcpy(lineCopy, line);

        char* token = strtok(lineCopy, ";");
        if (strcmp(token, username) == 0) {
            // Editar o agente
            printf("============================================\n");
            printf("1. Editar Nome\n");
            printf("2. Editar NIF\n");
            printf("3. Editar Morada\n");
            printf("4. Editar Contacto\n");
            printf("5. Editar Data de Nascimento\n");
            printf("0. Sair\n");
            printf("============================================\n");
            printf("O que deseja editar? ");
            int choice;
            scanf("%d", &choice);
            clearBuffer();

            Agent agent;
            strcpy(agent.username, token);
            token = strtok(NULL, ";");
            strcpy(agent.name, token);
            token = strtok(NULL, ";");
            strcpy(agent.nif, token);
            token = strtok(NULL, ";");
            strcpy(agent.morada, token);
            token = strtok(NULL, ";");
            strcpy(agent.contacto, token);
            token = strtok(NULL, ";");
            strcpy(agent.dataNascimento, token);
            token = strtok(NULL, ";");
            strcpy(agent.idade, token);
            token = strtok(NULL, ";");
            agent.status = (AgentStatus)atoi(token);

            switch (choice) {
                case 1:
                    do {
                        printf("Nome atual: %s\n", agent.name);
                        printf("Insira o novo nome: ");
                        if (fgets(agent.name, sizeof(agent.name), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        agent.name[strcspn(agent.name, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(agent.name);
                        if (strlen(agent.name) == 0 || agent.name[0] == ' ') {
                            printf("Erro: O nome deve ser definido\n");
                        }
                    } while (strlen(agent.name) == 0 || agent.name[0] == ' ');
                    break;
                case 2:
                    do {
                        printf("NIF atual: %s\n", agent.nif);
                        printf("Insira o novo NIF: ");
                        if (fgets(agent.nif, sizeof(agent.nif), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        agent.nif[strcspn(agent.nif, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(agent.nif);
                        if (strlen(agent.nif) == 0 || agent.nif[0] == ' ') {
                            printf("Erro: O NIF deve ser definido\n");
                        }
                    } while (strlen(agent.nif) == 0 || agent.nif[0] == ' ');
                    break;
                case 3:
                    do {
                        printf("Morada atual: %s\n", agent.morada);
                        printf("Insira a nova morada: ");
                        if (fgets(agent.morada, sizeof(agent.morada), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        agent.morada[strcspn(agent.morada, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(agent.morada);
                        if (strlen(agent.morada) == 0 || agent.morada[0] == ' ') {
                            printf("Erro: A morada deve ser definida\n");
                        }
                    } while (strlen(agent.morada) == 0 || agent.morada[0] == ' ');
                    break;
                case 4:
                    do {
                        printf("Contacto atual: %s\n", agent.contacto);
                        printf("Insira o novo contacto: ");
                        if (fgets(agent.contacto, sizeof(agent.contacto), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        agent.contacto[strcspn(agent.contacto, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(agent.contacto);
                        if (strlen(agent.contacto) == 0 || agent.contacto[0] == ' ') {
                            printf("Erro: O contacto deve ser definido\n");
                        }
                    } while (strlen(agent.contacto) == 0 || agent.contacto[0] == ' ');
                    break;
                case 5:
                    do {
                        printf("Data de nascimento atual: %s\n", agent.dataNascimento);
                        char newDataNascimento[11];
                        printf("Insira a nova data de nascimento: ");
                        if (fgets(newDataNascimento, sizeof(newDataNascimento), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        newDataNascimento[strcspn(newDataNascimento, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(newDataNascimento);
                        if (strlen(newDataNascimento) == 0 || newDataNascimento[0] == ' ' || !isValidDate(newDataNascimento)) {
                            printf("Erro: A data de nascimento deve ser válida no formato dd/mm/aaaa\n");
                        } else {
                            strcpy(agent.dataNascimento, newDataNascimento);
                            calculateAge(agent.dataNascimento, agent.idade);
                            break;
                        }
                    } while (1);
                    break;
                case 0:
                    fclose(file);
                    fclose(tempFile);
                    remove("temp.txt");
                    display_agent_menu(user);
                    return;
                default:
                    printf("Opção inválida\n");
                    continue;
            }

            // Remonta a linha com as atualizações
            fprintf(tempFile, "%s;%s;%s;%s;%s;%s;%s;%d\n", agent.username, agent.name, agent.nif, agent.morada, agent.contacto, agent.dataNascimento, agent.idade, agent.status);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME_TXT);
    rename("temp.txt", FILENAME_TXT);

    printf("Agente editado com sucesso!\n");

    // Pergunta ao usuário se deseja editar outro agente
    int choice;
    printf("============================================\n");
    printf("1. Editar outro agente\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        editAgent(user);
    } else if (choice == 2) {
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

void deleteAgent(const User* user) {
    clearScreen();

    while (1) {
        // Chama a função printAgents sem mostrar o menu
        printAgents(user, 0);

        char username[20];
        int attempts = 0;
        do {
            if (attempts > 0) {
                printf("============================================\n");
                printf("Erro: O username do agente escolhido não existe\n");
            } else {
                printf("\n");
            }
            printf("============================================\n");
            printf("Insira o username do agente que deseja eliminar (0 para voltar): ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0; // Remove newline character

            if (strcmp(username, "0") == 0) {
                display_agent_menu(user);
                return;
            }

            if (!agentExistsv2(username)) {
                attempts++;
            } else {
                break;
            }
        } while (1);

        // Verificar se o agente tem propriedades associadas
        FILE* propertiesFile = fopen(FILENAME_PROPS, "r");
        if (propertiesFile == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
            return;
        }

        int agentHasProperties = 0;
        char propertiesLine[1024];
        while (fgets(propertiesLine, sizeof(propertiesLine), propertiesFile)) {
            char* propId = strtok(propertiesLine, ";");
            char* morada = strtok(NULL, ";");
            char* descricao = strtok(NULL, ";");
            strtok(NULL, ";"); // Skip preço
            strtok(NULL, ";"); // Skip data
            char* agente = strtok(NULL, "\n");

            if (strcmp(agente, username) == 0) {
                agentHasProperties = 1;
                printf("O Agente \"%s\" tem a propriedade com o ID \"%s\" e com a descrição \"%s\" associada, não pode ser eliminado agora\n", username, propId, descricao);
                break;
            }
        }

        fclose(propertiesFile);

        if (agentHasProperties) {
            continue;
        }

        // Remover agente do arquivo .txt
        FILE* file = fopen(FILENAME_TXT, "r");
        if (file == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de agentes\n");
            return;
        }

        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Erro: Não foi possível criar o ficheiro temporário\n");
            fclose(file);
            return;
        }

        char line[1024];
        int agentFound = 0;
        while (fgets(line, sizeof(line), file)) {
            char lineCopy[1024];
            strcpy(lineCopy, line);

            char* token = strtok(lineCopy, ";");
            if (strcmp(token, username) == 0) {
                agentFound = 1;
                continue;
            } else {
                fprintf(tempFile, "%s", line);
            }
        }

        fclose(file);
        fclose(tempFile);

        if (!agentFound) {
            printf("Erro: O agente não foi encontrado\n");
            remove("temp.txt");
            display_agent_menu(user);
            return;
        }

        remove(FILENAME_TXT);
        rename("temp.txt", FILENAME_TXT);

        // Remover o agente do ficheiro .dat
        FILE* dataFile = fopen(FILENAME_DAT, "rb");
        if (dataFile == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de dados dos agentes\n");
            return;
        }

        FILE* tempDataFile = fopen("temp.dat", "wb");
        if (tempDataFile == NULL) {
            printf("Erro: Não foi possível criar o ficheiro temporário de dados\n");
            fclose(dataFile);
            return;
        }

        Agent agent;
        agentFound = 0;
        while (fread(&agent, sizeof(Agent), 1, dataFile)) {
            if (strcmp(agent.username, username) != 0) {
                fwrite(&agent, sizeof(Agent), 1, tempDataFile);
            } else {
                agentFound = 1;
            }
        }

        fclose(dataFile);
        fclose(tempDataFile);

        if (!agentFound) {
            printf("Erro: O agente não foi encontrado no ficheiro .dat\n");
            remove("temp.dat");
            return;
        }

        remove(FILENAME_DAT);
        rename("temp.dat", FILENAME_DAT);

        printf("Agente eliminado com sucesso!\n");
        clearBuffer();

        // Pergunta ao usuário se deseja eliminar outro agente
        int choice;
        printf("============================================\n");
        printf("1. Eliminar outro agente\n");
        printf("2. Voltar\n");
        printf("0. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            continue;
        } else if (choice == 2) {
            display_agent_menu(user);
            return;
        } else {
            exit_system();
        }
    }
}

void listAgentByUsername(const User* user) {
    clearScreen();

    char username[20];
    int attempts = 0;
    do {
        if (attempts > 0) {
            printf("============================================\n");
            printf("Erro: O username do agente escolhido não existe\n");
        } else {
            printf("\n");
        }
        printf("============================================\n");
        printf("Insira o username do agente que deseja listar (0 para voltar): ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove newline character

        if (strcmp(username, "0") == 0) {
            display_agent_menu(user);
            return;
        }

        if (!agentExistsv2(username)) {
            printf("Erro: O username não existe\n");
            attempts++;
        } else {
            break;
        }
    } while (1);

    FILE* file = fopen(FILENAME_TXT, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de agentes\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char lineCopy[1024];
        strcpy(lineCopy, line);

        char* token = strtok(lineCopy, ";");
        if (strcmp(token, username) == 0) {
            printf("============================================\n");
            printf("Username: %s\n", token);
            token = strtok(NULL, ";");
            printf("Nome: %s\n", token);
            token = strtok(NULL, ";");
            printf("NIF: %s\n", token);
            token = strtok(NULL, ";");
            printf("Morada: %s\n", token);
            token = strtok(NULL, ";");
            printf("Contacto: %s\n", token);
            token = strtok(NULL, ";");
            printf("Data de Nascimento: %s\n", token);
            token = strtok(NULL, ";");
            printf("Idade: %s\n", token);
            token = strtok(NULL, ";");
            if (atoi(token) == DISPONIVEL) {
                printf("Estado: Disponível\n");
            } else {
                printf("Estado: Indisponível\n");
            }
            printf("============================================\n");
            break;
        }
    }

    fclose(file);
    
    // Pergunta ao usuário se deseja listar outro agente
    
    int choice;
    printf("============================================\n");
    printf("1. Listar outro agente\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if (choice == 1) {
        listAgentByUsername(user);
    } else if (choice == 2) {
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

//(Algoritmo de ordenação)
void orderAgentsByName(const User *user){
    clearScreen();
    
    FILE *file = fopen(FILENAME_TXT, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    
    Agent agents[MAX_AGENTS];
    int numAgents = 0;
    
    char line[1024];
    while(fgets(line, sizeof(line), file)){
        char* token = strtok(line, ";");
        strcpy(agents[numAgents].username, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].name, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].nif, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].morada, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].contacto, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].dataNascimento, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].idade, token);
        token = strtok(NULL, ";");
        agents[numAgents].status = (AgentStatus)atoi(token);
        
        numAgents++;
    }
    
    fclose(file);
    
    // Ordenar os agentes por ordem alfabética do nome
    for(int i = 0; i < numAgents - 1; i++){
        for(int j = i + 1; j < numAgents; j++){
            if(strcmp(agents[i].name, agents[j].name) > 0){
                Agent temp = agents[i];
                agents[i] = agents[j];
                agents[j] = temp;
            }
        }
    }
    
    // Imprimir os agentes ordenados
    for(int i = 0; i < numAgents; i++){
        printf("Username: %s\n", agents[i].username);
        printf("Nome: %s\n", agents[i].name);
        printf("NIF: %s\n", agents[i].nif);
        printf("Morada: %s\n", agents[i].morada);
        printf("Contacto: %s\n", agents[i].contacto);
        printf("Data de Nascimento: %s\n", agents[i].dataNascimento);
        printf("Idade: %s\n", agents[i].idade);
        if(agents[i].status == DISPONIVEL ){
            printf("Estado: Disponível\n");
        } else {
            printf("Estado: Indisponível\n");
        }
        printf("============================================\n");
    }
    
    int choice;
    printf("1. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if(choice == 1){
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

//(Algoritmo de ordenação)
void orderAgentByAge(const User *user){
    clearScreen();
    
    FILE *file = fopen(FILENAME_TXT, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    
    Agent agents[MAX_AGENTS];
    int numAgents = 0;
    
    char line[1024];
    while(fgets(line, sizeof(line), file)){
        char* token = strtok(line, ";");
        strcpy(agents[numAgents].username, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].name, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].nif, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].morada, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].contacto, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].dataNascimento, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].idade, token);
        token = strtok(NULL, ";");
        agents[numAgents].status = (AgentStatus)atoi(token);
        
        numAgents++;
    }
    
    fclose(file);
    
    // Ordenar os agentes por idade ascendente
    for(int i = 0; i < numAgents - 1; i++){
        for(int j = i + 1; j < numAgents; j++){
            if(atoi(agents[i].idade) > atoi(agents[j].idade)){
                Agent temp = agents[i];
                agents[i] = agents[j];
                agents[j] = temp;
            }
        }
    }
    
    // Imprimir os agentes ordenados
    for(int i = 0; i < numAgents; i++){
        printf("Username: %s\n", agents[i].username);
        printf("Nome: %s\n", agents[i].name);
        printf("NIF: %s\n", agents[i].nif);
        printf("Morada: %s\n", agents[i].morada);
        printf("Contacto: %s\n", agents[i].contacto);
        printf("Data de Nascimento: %s\n", agents[i].dataNascimento);
        printf("Idade: %s\n", agents[i].idade);
        if(agents[i].status == DISPONIVEL ){
            printf("Estado: Disponível\n");
        } else {
            printf("Estado: Indisponível\n");
        }
        printf("============================================\n");
    }
    
    int choice;
    printf("1. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if(choice == 1){
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

void setAgentUnavailable(const User *user) {
    clearScreen();

    FILE *file = fopen(FILENAME_TXT, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }

    Agent agents[MAX_AGENTS];
    int numAgents = 0;

    char line[1024];
    while(fgets(line, sizeof(line), file)){
        char* token = strtok(line, ";");
        strcpy(agents[numAgents].username, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].name, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].nif, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].morada, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].contacto, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].dataNascimento, token);
        token = strtok(NULL, ";");
        strcpy(agents[numAgents].idade, token);
        token = strtok(NULL, ";");
        agents[numAgents].status = (AgentStatus)atoi(token);

        numAgents++;
    }

    fclose(file);

    // Listar os agentes disponíveis
    printf("Agentes Disponíveis\n");
    printf("============================================\n");
    for(int i = 0; i < numAgents; i++){
        if(agents[i].status == DISPONIVEL){
            printf("Username: %s\n", agents[i].username);
            printf("Nome: %s\n", agents[i].name);
            printf("NIF: %s\n", agents[i].nif);
            printf("Morada: %s\n", agents[i].morada);
            printf("Contacto: %s\n", agents[i].contacto);
            printf("Data de Nascimento: %s\n", agents[i].dataNascimento);
            printf("Idade: %s\n", agents[i].idade);
            printf("Estado: Disponível\n");
            printf("============================================\n");
        }
    }

    char username[20];
    int attempts = 0;
    int agentFound = 0;
    do {
        if (attempts > 0) {
            printf("============================================\n");
            printf("Erro: O username do agente escolhido não existe ou não está disponível\n");
        } else {
            printf("\n");
        }
        printf("============================================\n");
        printf("Insira o username do agente que deseja colocar como indisponível (0 para voltar): ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0; // Remove newline character

        if (strcmp(username, "0") == 0) {
            display_agent_menu(user);
            return;
        }

        for(int i = 0; i < numAgents; i++){
            if(strcmp(agents[i].username, username) == 0 && agents[i].status == DISPONIVEL){
                agents[i].status = INDISPONIVEL;
                agentFound = 1;
                break;
            }
        }

        if(agentFound){
            break;
        } else {
            attempts++;
        }
    } while (1);

    if (!agentFound) {
        printf("Erro: O agente não foi encontrado ou não está disponível\n");
        return;
    }

    // Atualizar o ficheiro .txt
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro: Não foi possível criar o ficheiro temporário\n");
        return;
    }

    for(int i = 0; i < numAgents; i++) {
        fprintf(tempFile, "%s;%s;%s;%s;%s;%s;%s;%d\n",
                agents[i].username, agents[i].name, agents[i].nif,
                agents[i].morada, agents[i].contacto, agents[i].dataNascimento,
                agents[i].idade, agents[i].status);
    }

    fclose(tempFile);
    remove(FILENAME_TXT);
    rename("temp.txt", FILENAME_TXT);

    printf("Agente colocado como indisponível com sucesso!\n");

    // Pergunta ao usuário se deseja colocar outro agente como indisponível
    int choice;
    printf("============================================\n");
    printf("1. Colocar outro agente como indisponível\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        setAgentUnavailable(user);
    } else if (choice == 2) {
        display_agent_menu(user);
    } else {
        exit_system();
    }
}

void generateReport(const User *user) {
    clearScreen();

    FILE *file = fopen(FILENAME_TXT, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }

    FILE *reportFile = fopen(FILENAME_REPORT, "w");
    if(reportFile == NULL){
        printf("Erro ao criar ficheiro\n");
        fclose(file);
        return;
    }

    fprintf(reportFile, "Relatório de Agentes\n");
    fprintf(reportFile, "============================================\n");

    char line[1024];
    while(fgets(line, sizeof(line), file)){
        char* token = strtok(line, ";");
        fprintf(reportFile, "Username: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "Nome: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "NIF: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "Morada: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "Contacto: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "Data de Nascimento: %s\n", token);
        token = strtok(NULL, ";");
        fprintf(reportFile, "Idade: %s\n", token);
        token = strtok(NULL, ";");
        if(atoi(token) == DISPONIVEL){
            fprintf(reportFile, "Estado: Disponível\n");
        } else {
            fprintf(reportFile, "Estado: Indisponível\n");
        }
        fprintf(reportFile, "============================================\n");
    }

    fclose(file);
    fclose(reportFile);

    printf("Relatório gerado com sucesso!\n");

    display_agent_menu(user);
   
}


