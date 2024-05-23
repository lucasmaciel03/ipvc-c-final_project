#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "properties.h"
#include "../agents/agents.h"

// Function to initialize the property list
void initPropertiesList(PropertiesList* list){
    list->head = NULL;
    list->tail = NULL;
    list->nextId = 1; // Start IDs from 1
}

// Function to create a new property
Property* createProperty(PropertiesList* list){
    Property* newProperty = (Property*)malloc(sizeof(Property));
    if (!newProperty) {
        printf("Erro: Não foi possível alocar memória para a nova propriedade!\n");
        return NULL;
    }

    newProperty->id = list->nextId++;

    
    printf("Insira a morada da propriedade: ");
    fgets(newProperty->morada, sizeof(newProperty->morada), stdin);
    newProperty->morada[strcspn(newProperty->morada, "\n")] = '\0'; // Remove newline character
    
    printf("Insira a descrição da propriedade: ");
    fgets(newProperty->descricao, sizeof(newProperty->descricao), stdin);
    newProperty->descricao[strcspn(newProperty->descricao, "\n")] = '\0'; // Remove newline character

    printf("Insira o preço da propriedade: ");
    scanf("%lf", &newProperty->preco);
    clearBuffer();
    
    printf("Insira a data da propriedade: ");
    fgets(newProperty->data, sizeof(newProperty->data), stdin);
    newProperty->data[strcspn(newProperty->data, "\n")] = '\0'; // Remove newline character
    
    printf("Insira o agente da propriedade: ");
    fgets(newProperty->agente, sizeof(newProperty->agente), stdin);
    newProperty->agente[strcspn(newProperty->agente, "\n")] = '\0'; // Remove newline character

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

