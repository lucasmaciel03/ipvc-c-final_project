#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "../auth/users/user.h"

typedef enum{
    VENDIDA, // 0
    ANUNCIADA, // 1
    ARRENDADA, // 2
    CASA_ABERTA // 3
} PropertyStatus;

typedef struct Property {
    int id;
    char morada[50];
    char descricao[55];
    double preco;
    char data[11];
    char agente[20];
    char proprietario[50];
    PropertyStatus status;
    struct Property *next;
    struct Property *prev;
} Property;

// Define the structure for the doubly linked list
typedef struct {
    Property *head;
    Property *tail;
    int nextId;
} PropertiesList;

void initPropertiesList(PropertiesList* list);
Property* createProperty(const User* user, const char* owner);
void addProperty(PropertiesList* list, Property* newProperty);
void printProperties(const User* user, int showMenu);
void display_all_users_data(const User *user);
void removeProperty(PropertiesList* list, const User* user);
void editProperty(PropertiesList* list, const User* user);
void printPropertiesToSale(const User* user, int showMenu);
void printPropertiesByOwner(const User* user);
#endif