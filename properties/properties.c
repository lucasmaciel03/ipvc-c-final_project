#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "properties.h"
#include "../agents/agents.h"
#include "../auth/users/user.h"
#include "../menus/properties_menu/properties_menu.h"

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/properties.txt"

void savePropertyToFile(Property* property);

int calculateNextId() {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        return 1; // Start IDs from 1
    }

    int id = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        id = atoi(token);
    }

    fclose(file);
    return id + 1;
}

int checkPropertyId(int id) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        int currentId = atoi(token);
        if (currentId == id) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Function to initialize the property list
void initPropertiesList(PropertiesList* list){
    list->head = NULL;
    list->tail = NULL;
    list->nextId = calculateNextId();
}

// Function to create a new property
Property* createProperty(const User* user, const char* owner){
    clearScreen();
    Property* newProperty = (Property*)malloc(sizeof(Property));

    double price;
    char priceStr[50];

    if (!newProperty) {
        printf("Erro: Não foi possível alocar memória para a nova propriedade!\n");
        return NULL;
    }

    newProperty->id = calculateNextId();

    printf("Insira os dados da propriedade (0 para voltar)\n");
    printf("============================================\n");

    // Input Morada
    do {
        printf("Insira a morada da propriedade: ");
        if (fgets(newProperty->morada, sizeof(newProperty->morada), stdin) == NULL) {
            // Handle error or EOF
            clearBuffer();
            continue;
        }
        newProperty->morada[strcspn(newProperty->morada, "\n")] = '\0'; // Remove newline character
        trimWhitespace(newProperty->morada);
        if (strcmp(newProperty->morada, "0") == 0) {
            display_properties_menu(user);
            free(newProperty);
            return NULL; // Return NULL to stop the execution of the current function
        }
        if (strlen(newProperty->morada) == 0 || newProperty->morada[0] == ' ') {
            printf("Erro: A propriedade deve ter uma morada definida\n");
        }
    } while (strlen(newProperty->morada) == 0 || newProperty->morada[0] == ' ');

    // Input Descrição da Propriedade
    do {
        printf("Insira a descrição da propriedade: ");
        if (fgets(newProperty->descricao, sizeof(newProperty->descricao), stdin) == NULL) {
            // Handle error or EOF
            clearBuffer();
            continue;
        }
        newProperty->descricao[strcspn(newProperty->descricao, "\n")] = '\0'; // Remove newline character
        trimWhitespace(newProperty->descricao);
        if (strlen(newProperty->descricao) == 0) {
            printf("Erro: A propriedade deve ter uma descrição definida\n");
        }
    } while (strlen(newProperty->descricao) == 0 || newProperty->descricao[0] == ' ');

    // Input Preço da Propriedade
    do {
        printf("Insira o preço da propriedade: ");
        if (fgets(priceStr, sizeof(priceStr), stdin) == NULL) {
            // Handle error or EOF
            clearBuffer();
            continue;
        }
        trimWhitespace(priceStr);
        if (strlen(priceStr) == 0) {
            printf("Erro: O preço não pode ser vazio.\n");
            price = -1; // Force the loop to ask again
        } else {
            price = atof(priceStr);
            if (price <= 0) {
                printf("Erro: O preço definido não é valido\n");
                price = -1; // Force the loop to ask again
            }
        }
    } while (price < 0);
    newProperty->preco = price;

    // Input Data da Propriedade
    getCurrentDate(newProperty->data);

    // Input Agente da Propriedade
    do {
        printf("Insira o agente da propriedade: ");
        if (fgets(newProperty->agente, sizeof(newProperty->agente), stdin) == NULL) {
            // Handle error or EOF
            clearBuffer();
            continue;
        }
        newProperty->agente[strcspn(newProperty->agente, "\n")] = '\0'; // Remove newline character
        trimWhitespace(newProperty->agente);
        if (strlen(newProperty->agente) == 0) {
            printf("Erro: A propriedade deve ter um agente definido\n");
        } else {
            // utilizar função agentExists para verificar se o agente existe
            if (!agentExistsv2(newProperty->agente)) {
                printf("Erro: O agente inserido não existe\n");
                newProperty->agente[0] = ' '; // Force the loop to ask again
            }
            if (!isAgentAvailable(newProperty->agente)) {
                printf("Erro: O agente inserido não está disponível\n");
                newProperty->agente[0] = ' '; // Force the loop to ask again
            }
        }
    } while (strlen(newProperty->agente) == 0 || newProperty->agente[0] == ' ');

    strcpy(newProperty->proprietario, owner);

    // Definir o status
    newProperty->status = ANUNCIADA;

    newProperty->next = NULL;
    newProperty->prev = NULL;

    // Save the property to the file
    savePropertyToFile(newProperty);

    return newProperty;
}

// Function to add a property to the list
void addProperty(PropertiesList* list, Property* newProperty){
    if (list->head == NULL) {
        list->head = newProperty;
        list->tail = newProperty;
    } else {
        list->tail->next = newProperty;
        newProperty->prev = list->tail;
        list->tail = newProperty;
    }
}

// Function to save property details to a file
void savePropertyToFile(Property* property) {
    FILE* file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    fprintf(file, "%d;%s;%s;%.2f;%s;%s;%s;%d\n",
            property->id, 
            property->morada,
            property->descricao,
            property->preco,
            property->data,
            property->agente,
            property->proprietario,
            property->status
            );

    printf("Propriedade guardada com sucesso!\n");
    
    fclose(file);
}

void printProperties(const User* user, int showMenu) {
    clearScreen();

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    printf("Propriedades cadastradas:\n");
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        printf("============================================\n");

        printf("ID: %s\n", token);

        token = strtok(NULL, ";");
        printf("Morada: %s\n", token);

        token = strtok(NULL, ";");
        printf("Descrição: %s\n", token);

        token = strtok(NULL, ";");
        printf("Preço: %s €\n", token);

        token = strtok(NULL, ";");
        printf("Data: %s\n", token);
        
        token = strtok(NULL, ";");
        printf("Agente: %s\n", token);
        
        token = strtok(NULL, ";");
        printf("Proprietário: %s\n", token);
        
        token = strtok(NULL, ";");
        int status = atoi(token);
        if (status == ANUNCIADA) {
            printf("Status: Anunciada\n");
        } else if (status == ARRENDADA) {
            printf("Status: Arrendada\n");
        } else if (status == VENDIDA) {
            printf("Status: Vendida\n");
        } else {
            printf("Status: Indefinido\n");
        }
    }

    fclose(file);

    if (showMenu) {
        int choice;
        printf("\n");
        printf("============================================\n");
        printf("1. Voltar\n");
        printf("0. Sair\n");
        printf("============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if(choice == 1) {
            display_properties_menu(user);
        } else {
            exit_system();
        }
    }
}

void removeProperty(PropertiesList* list, const User* user) {
    clearScreen();

    // Chama a função printProperties sem mostrar o menu
    printProperties(user, 0);

    int id;
    printf("\n");
    printf("============================================\n");
    printf("Insira o ID da propriedade que deseja remover (0 para voltar): ");
    scanf("%d", &id);
    clearBuffer();

    if (id == 0) {
        display_properties_menu(user);
        return;
    }

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    FILE* tempFile = fopen("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.txt", "w");
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
        int currentId = atoi(token);
        if (currentId != id) {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.txt", FILENAME);

    printf("Propriedade removida com sucesso!\n");

    // Pergunta ao usuário se deseja remover outra propriedade
    int choice;
    printf("============================================\n");
    printf("1. Remover outra propriedade\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        removeProperty(list, user);
    } else if (choice == 2) {
        display_properties_menu(user);
    } else {
        exit_system();
    }
}

void editProperty(PropertiesList* list, const User* user) {
    clearScreen();

    // Chama a função printProperties sem mostrar o menu
    printProperties(user, 0);

    int id;
    // Numero de tentativas que usuario falhou ao inserir o ID
    int attempts = 0;

    while (1) {
        if (attempts > 0) {
            printf("============================================\n");
            printf("Erro: O ID da propriedade escolhida não existe ou não está disponível para edição\n");
        } else {
            printf("\n");
        }
        printf("============================================\n");
        printf("Insira o ID da propriedade que deseja editar (0 para voltar): ");
        scanf("%d", &id);
        clearBuffer();

        if (id == 0) {
            display_properties_menu(user);
            return;
        }

        if (!checkPropertyId(id)) {
            attempts++;
        } else {
            break;
        }
    }

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro: Não foi possível criar o ficheiro temporário\n");
        fclose(file);
        return;
    }

    char line[1024];
    int propertyFound = 0;
    int propertyEdited = 0;
    while (fgets(line, sizeof(line), file)) {
        char lineCopy[1024];
        strcpy(lineCopy, line);

        char* token = strtok(lineCopy, ";");
        int currentId = atoi(token);
        if (currentId == id) {
            // Ler os detalhes da propriedade
            char idStr[50], address[256], description[256], price[50], date[50], agent[256], owner[50];
            int status;

            strcpy(idStr, token);
            token = strtok(NULL, ";");
            strcpy(address, token);
            token = strtok(NULL, ";");
            strcpy(description, token);
            token = strtok(NULL, ";");
            strcpy(price, token);
            token = strtok(NULL, ";");
            strcpy(date, token);
            token = strtok(NULL, ";");
            strcpy(agent, token);
            token = strtok(NULL, ";");
            strcpy(owner, token);
            token = strtok(NULL, ";");
            status = atoi(token);

            // Verifica se a propriedade está disponível para venda
            if (status != ANUNCIADA) {
                printf("Erro: A propriedade escolhida não está disponível para edição\n");
                propertyFound = 1;
                fprintf(tempFile, "%s", line);  // Escreve a linha original de volta no arquivo temporário
                continue;
            }

            // Editar a propriedade
            propertyFound = 1;
            printf("============================================\n");
            printf("1. Editar Morada\n");
            printf("2. Editar Descrição\n");
            printf("3. Editar Preço\n");
            printf("4. Editar Agente\n");
            printf("0. Sair\n");
            printf("============================================\n");
            printf("O que deseja editar? ");
            int choice;
            scanf("%d", &choice);
            clearBuffer();

            switch (choice) {
                case 1:
                    do {
                        printf("Morada atual: %s\n", address);
                        printf("Insira a nova morada: ");
                        if (fgets(address, sizeof(address), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        address[strcspn(address, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(address);
                        if (strlen(address) == 0 || address[0] == ' ') {
                            printf("Erro: A propriedade deve ter uma morada definida\n");
                        }
                    } while (strlen(address) == 0 || address[0] == ' ');
                    propertyEdited = 1;
                    break;
                case 2:
                    do {
                        printf("Descrição atual: %s\n", description);
                        printf("Insira a nova descrição: ");
                        if (fgets(description, sizeof(description), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        description[strcspn(description, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(description);
                        if (strlen(description) == 0) {
                            printf("Erro: A propriedade deve ter uma descrição definida\n");
                        }
                    } while (strlen(description) == 0 || description[0] == ' ');
                    propertyEdited = 1;
                    break;
                case 3:
                    do {
                        printf("Preço atual: %s €\n", price);
                        printf("Insira o novo preço: ");
                        if (fgets(price, sizeof(price), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        price[strcspn(price, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(price);
                        if (strlen(price) == 0) {
                            printf("Erro: O preço não pode ser vazio.\n");
                        } else {
                            double priceValue = atof(price);
                            if (priceValue <= 0) {
                                printf("Erro: O preço definido não é válido\n");
                                price[0] = '\0'; // Force the loop to ask again
                            }
                        }
                    } while (strlen(price) == 0 || atof(price) <= 0);
                    propertyEdited = 1;
                    break;
                case 4:
                    do {
                        printf("Agente atual: %s\n", agent);
                        printf("Insira o novo agente da propriedade: ");
                        if (fgets(agent, sizeof(agent), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        agent[strcspn(agent, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(agent);
                        if (strlen(agent) == 0) {
                            printf("Erro: A propriedade deve ter um agente definido\n");
                        } else {
                            if (!agentExistsv2(agent)) {
                                printf("Erro: O agente inserido não existe ou não está disponível\n");
                                agent[0] = ' '; // Force the loop to ask again
                            }
                        }
                    } while (strlen(agent) == 0 || agent[0] == ' ');
                    propertyEdited = 1;
                    break;
                case 0:
                    fclose(file);
                    fclose(tempFile);
                    remove("temp.txt");
                    display_properties_menu(user);
                    return;
                default:
                    printf("Opção inválida\n");
                    break;
            }

            // Remonta a linha com as atualizações
            fprintf(tempFile, "%s;%s;%s;%s;%s;%s;%s;%d\n", idStr, address, description, price, date, agent, owner, status);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (propertyEdited) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Propriedade editada com sucesso!\n");
    } else {
        remove("temp.txt");
    }

    // Pergunta ao usuário se deseja editar outra propriedade
    int choice;
    printf("============================================\n");
    printf("1. Editar outra propriedade\n");
    printf("2. Voltar\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        editProperty(list, user);
    } else if (choice == 2) {
        display_properties_menu(user);
    } else {
        exit_system();
    }
}

void printPropertiesToSale(const User* user, int showMenu) {
    clearScreen();

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    printf("Propriedades para venda:\n");
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        int id = atoi(token);

        token = strtok(NULL, ";");
        char address[256];
        strcpy(address, token);

        token = strtok(NULL, ";");
        char description[256];
        strcpy(description, token);

        token = strtok(NULL, ";");
        double price = atof(token);

        token = strtok(NULL, ";");
        char date[50];
        strcpy(date, token);

        token = strtok(NULL, ";");
        char agent[256];
        strcpy(agent, token);

        token = strtok(NULL, ";");
        char owner[256];
        strcpy(owner, token);

        token = strtok(NULL, ";");
        int status = atoi(token);

        if (status == ANUNCIADA && strcmp(owner, user->username) != 0) {
            printf("============================================\n");
            printf("ID: %d\n", id);
            printf("Morada: %s\n", address);
            printf("Descrição: %s\n", description);
            printf("Preço: %.2f €\n", price);
            printf("Data: %s\n", date);
            printf("Agente: %s\n", agent);
            printf("Proprietário: %s\n", owner);
        }
    }

    fclose(file);
}

// Criar função que retorna as propriedades do proprietário atual
void printPropertiesByOwner(const User* user) {
    clearScreen();

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
        return;
    }

    printf("As suas propriedades:\n");
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");
        int id = atoi(token);

        token = strtok(NULL, ";");
        char address[256];
        strcpy(address, token);

        token = strtok(NULL, ";");
        char description[256];
        strcpy(description, token);

        token = strtok(NULL, ";");
        double price = atof(token);

        token = strtok(NULL, ";");
        char date[50];
        strcpy(date, token);

        token = strtok(NULL, ";");
        char agent[256];
        strcpy(agent, token);

        token = strtok(NULL, ";");
        char owner[256];
        strcpy(owner, token);

        token = strtok(NULL, ";");
        int status = atoi(token);

        if (strcmp(owner, user->username) == 0) {
            printf("============================================\n");
            printf("ID: %d\n", id);
            printf("Morada: %s\n", address);
            printf("Descrição: %s\n", description);
            printf("Preço: %.2f €\n", price);
            printf("Data: %s\n", date);
            printf("Agente: %s\n", agent);
            printf("Proprietário: %s\n", owner);
            if (status == ANUNCIADA) {
                printf("Status: Anunciada\n");
            } else if (status == ARRENDADA) {
                printf("Status: Arrendada\n");
            } else if (status == VENDIDA) {
                printf("Status: Vendida\n");
            } else {
                printf("Status: Indefinido\n");
            }
        }
    }

    fclose(file);
}

