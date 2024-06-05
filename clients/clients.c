#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "../properties/properties.h"
#include "../agents/agents.h"
#include "../auth/users/user.h"
#include "../menus/client_main_menu/client_main_menu.h"

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/properties.txt"

#define FILENAME_VISITAS "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/visitas.txt"

void updatePropertyInFile(int propertyId, const char* newOwner, PropertyStatus newStatus) {
    FILE* file = fopen(FILENAME, "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Property property;
        sscanf(line, "%d;%49[^;];%54[^;];%lf;%10[^;];%19[^;];%49[^;];%d",
               &property.id, property.morada, property.descricao, &property.preco,
               property.data, property.agente, property.proprietario, (int*)&property.status);

        if (property.id == propertyId) {
            // Atualiza a data da propriedade
            getCurrentDate(property.data);
            // Atualiza o proprietário e o status da propriedade
            strcpy(property.proprietario, newOwner);
            property.status = newStatus;
        }

        fprintf(tempFile, "%d;%s;%s;%.2f;%s;%s;%s;%d\n", property.id, property.morada, property.descricao,
                property.preco, property.data, property.agente, property.proprietario, property.status);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void propertiesList(const User *user) {
    while (1) {
        clearScreen();

        printPropertiesToSale(user, 1);

        int propertyId;
        printf("============================================\n");
        printf("Está interessado em alguma propriedade? Se sim, indique o ID (0 para voltar): ");
        scanf("%d", &propertyId);
        clearBuffer();

        if (propertyId == 0) {
            display_client_main_menu(user);
            return;
        }

        // Verifica se o usuário é o proprietário da propriedade
        FILE* file = fopen(FILENAME, "r");
        if (file == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
            return;
        }

        int isOwner = 0;
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            int id;
            char owner[256];

            sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%*[^;];%[^;];%*d", &id, owner);

            if (id == propertyId) {
                if (strcmp(owner, user->username) == 0) {
                    isOwner = 1;
                }
                break;
            }
        }

        fclose(file);

        if (isOwner) {
            printf("Erro: Você não pode comprar ou arrendar uma propriedade que você anunciou.\n");
            continue;  // Volta a perguntar o ID da propriedade
        }

        int choice;
        printf("============================================\n");
        printf("O que deseja fazer com a propriedade?\n");
        printf("1. Comprar esta propriedade\n");
        printf("2. Arrendar esta propriedade\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            updatePropertyInFile(propertyId, user->username, VENDIDA);
            printf("Propriedade comprada com sucesso!\n");
        } else if (choice == 2) {
            updatePropertyInFile(propertyId, user->username, ARRENDADA);
            printf("Propriedade arrendada com sucesso!\n");
        } else {
            printf("Opção inválida.\n");
        }

        break;  // Sai do loop após uma compra ou arrendamento bem-sucedido
    }
}

Property* announceProperty(const User *user) {
    Property* newProperty = createProperty(user, user->username);
    if (newProperty) {
        printf("Propriedade anunciada com sucesso!\n");
    } else {
        printf("Erro ao anunciar a propriedade.\n");
    }
    return newProperty;
}

void myProperties(const User *user) {
    clearScreen();
    printPropertiesByOwner(user);
    
    int choice;
    printf("============================================\n");
    printf("1. Voltar\n");
    printf("2. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if (choice == 1) {
        display_client_main_menu(user);
    } else if (choice == 2) {
        exit_system();
    } else {
        printf("Opção inválida.\n");
    }
}

