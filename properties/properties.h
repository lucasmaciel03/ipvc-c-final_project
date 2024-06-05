#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "../auth/users/user.h"

typedef struct Property {
    int id;
    char morada[50];
    char descricao[20];
    double preco;
    char data[10];
    char agente[20];
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
Property* createProperty(PropertiesList* list, const User* user);
void addProperty(PropertiesList* list, Property* newProperty);
void printProperties(const User* user, int showMenu);
void display_all_users_data(const User *user);
void removeProperty(PropertiesList* list, const User* user);
void editProperty(PropertiesList* list, const User* user);
#endif