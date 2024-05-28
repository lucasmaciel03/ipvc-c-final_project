#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "properties.h"
#include "../agents/agents.h"
#include "../auth/users/user.h"
#include "../menus/properties_menu/properties_menu.h"

// Function to initialize the property list
void initPropertiesList(PropertiesList* list){
    list->head = NULL;
    list->tail = NULL;
    list->nextId = 1; // Start IDs from 1
}

// Function to create a new property
Property* createProperty(PropertiesList* list) {
    clearScreen();
    Property* newProperty = (Property*)malloc(sizeof(Property));
    User user;

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
            display_properties_menu(&user);
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
        }
    } while (strlen(newProperty->agente) == 0 || newProperty->agente[0] == ' ');

    newProperty->next = NULL;
    newProperty->prev = NULL;

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

// Function to list all properties
void printProperties(const PropertiesList* list){   
    Property* current = list->head;
    
    if (current == NULL) {
        printf("Não existem propriedades para mostrar.\n");
        return;
    }
    
    printf("Lista de Propriedades\n");
    printf("============================================\n");
    
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Morada: %s\n", current->morada);
        printf("Descrição: %s\n", current->descricao);
        printf("Preço: %.2f\n", current->preco);
        printf("Data: %s\n", current->data);
        printf("Agente: %s\n", current->agente);
        printf("============================================\n");
        
        current = current->next;
    }
}

