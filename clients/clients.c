#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "../properties/properties.h"
#include "../agents/agents.h"
#include "../auth/users/user.h"
#include "../menus/client_main_menu/client_main_menu.h"

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/properties.txt"

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
    clearScreen();
    
    printPropertiesToSale(user, 1);

    int propertyId;
    printf("============================================\n");
    printf("Está interessado em alguma propriedade? Se sim, indique o ID (0 para voltar): ");
    scanf("%d", &propertyId);
    clearBuffer();

    if (propertyId == 0) {
        return;
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
}