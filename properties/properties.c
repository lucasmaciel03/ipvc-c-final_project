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

// Function to calculate the property ID by reading the last ID from the file
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

// function to use in removeProperty and editProperty to check if the ID of the property exists
// - read the file and check if the ID exists
// - return 1 if the ID exists and 0 if not

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
Property* createProperty(PropertiesList* list, const User* user){
    clearScreen();
    Property* newProperty = (Property*)malloc(sizeof(Property));
    
    double price;
    char priceStr[50];

    if (!newProperty) {
        printf("Erro: Não foi possível alocar memória para a nova propriedade!\n");
        return NULL;
    }

    newProperty->id = list->nextId++;

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
    do {
        printf("Insira a data da propriedade: ");
        if (fgets(newProperty->data, sizeof(newProperty->data), stdin) == NULL) {
            // Handle error or EOF
            clearBuffer();
            continue;
        }
        newProperty->data[strcspn(newProperty->data, "\n")] = '\0'; // Remove newline character
        trimWhitespace(newProperty->data);
        if (strlen(newProperty->data) == 0) {
            printf("A propriedade deve ter uma data definida!\n");
        }
    } while (strlen(newProperty->data) == 0 || newProperty->data[0] == ' ');

    clearBuffer();
    
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
//            if (!checkAgentUsername(newProperty->agente)) {
//                printf("Erro: O agente não existe ou não está disponível\n");
//                newProperty->agente[0] = '\0'; // Clear the string
//            }
        }
    } while (strlen(newProperty->agente) == 0 || newProperty->agente[0] == ' ');

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

    fprintf(file, "%d;%s;%s;%.2f;%s;%s\n", 
            property->id, 
            property->morada,
            property->descricao,
            property->preco,
            property->data,
            property->agente);

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
        printf("Agente: %s", token);
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

// function to remove a property by ID from the file txt and from the list
// - read the file and write all the properties except the one with the ID
// - remove the property from the list
// - use the function printProperties for user see the properties and choose the ID
// - ask the user for the ID of the property to remove
// - ask the user after the remove if he wants to remove another property if not return to the main menu

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

// function to edit a property by ID from the file txt and from the list
// - start using the function printProperties for user see the properties and choose the ID
// - ask the user for the ID of the property to edit
// - ask the user what he want to edit, like this question (What do you want to edit? 1 - Morada, 2 - Descrição, 3 - Preço, 4 - Data, 5 - Agente, 0 - Sair)
// - ask the user for the new value
// - write the new value in the file txt
// - ask the user after the edit if he wants to edit another property if not return to the main menu

void editProperty(PropertiesList* list, const User* user) {
    clearScreen();

    // Chama a função printProperties sem mostrar o menu
    printProperties(user, 0);

    int id;
    // numero de tentativas que usuario falhou ao inserir o ID
    int attempts = 0;
    do {
        // only if attemppts = 0 printf("\n");
        if (attempts > 0) {
            printf("============================================\n");
            printf("Erro: O ID da propriedade escolhida não existe\n");
        }
        else {
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

        FILE* file = fopen(FILENAME, "r");
        if (file == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
            return;
        }

        if (!checkPropertyId(id)) {
            attempts++;
            fclose(file);  // Fecha o arquivo aberto para verificar o ID
        } else {
            // Fecha o arquivo aberto e sai do loop caso o ID seja válido
            fclose(file);
            break;
        }
    } while (1);


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
        if (currentId == id) {
            // Editar a propriedade
            printf("============================================\n");
            printf("1. Editar Morada\n");
            printf("2. Editar Descrição\n");
            printf("3. Editar Preço\n");
            printf("4. Editar Data\n");
            printf("5. Editar Agente\n");
            printf("0. Sair\n");
            printf("============================================\n");
            printf("O que deseja editar? ");
            int choice;
            scanf("%d", &choice);
            clearBuffer();

            char idStr[50], address[256], description[256], price[50], date[50], agent[256];

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

            switch (choice) {
                case 1:
                    printf("Morada atual: %s\n", address);
                    printf("Insira a nova morada: ");
                    if (fgets(address, sizeof(address), stdin) == NULL) {
                        clearBuffer();
                        continue;
                    }
                    address[strcspn(address, "\n")] = '\0'; // Remove newline character
                    break;
                case 2:
                    printf("Descrição atual: %s\n", description);
                    printf("Insira a nova descrição: ");
                    if (fgets(description, sizeof(description), stdin) == NULL) {
                        clearBuffer();
                        continue;
                    }
                    description[strcspn(description, "\n")] = '\0'; // Remove newline character
                    break;
                case 3:
                    printf("Preço atual: %s €\n", price);
                    printf("Insira o novo preço: ");
                    if (fgets(price, sizeof(price), stdin) == NULL) {
                        clearBuffer();
                        continue;
                    }
                    price[strcspn(price, "\n")] = '\0'; // Remove newline character
                    break;
                case 4:
                    printf("Data atual: %s\n", date);
                    printf("Insira a nova data: ");
                    if (fgets(date, sizeof(date), stdin) == NULL) {
                        clearBuffer();
                        continue;
                    }
                    date[strcspn(date, "\n")] = '\0'; // Remove newline character
                    break;
                case 5:
                    printf("Agente atual: %s\n", agent);
                    printf("Insira o novo agente: ");
                    if (fgets(agent, sizeof(agent), stdin) == NULL) {
                        clearBuffer();
                        continue;
                    }
                    agent[strcspn(agent, "\n")] = '\0'; // Remove newline character
                    break;
                case 0:
                    fclose(file);
                    fclose(tempFile);
                    remove("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.txt");
                    display_properties_menu(user);
                    return;
                default:
                    printf("Opção inválida\n");
                    break;
            }

            // Remonta a linha com as atualizações
            fprintf(tempFile, "%s;%s;%s;%s;%s;%s", idStr, address, description, price, date, agent);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/temp.txt", FILENAME);

    printf("Propriedade editada com sucesso!\n");

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




