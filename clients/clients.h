#ifndef _CLIENTS
#define _CLIENTS

#include "../auth/users/user.h"
#include "../properties/properties.h"

typedef struct {
    char username[20];
    char name[50];
    char nif[10];
    char morada[50];
    char contacto[9];
    char dataNascimento[11];
    char idade[4];
} Client;

void propertiesList(const User *user);
Property* announceProperty(const User *user);
void myProperties(const User *user);
void updateClientProfile(const User* user);
void deleteAccount(const User* user);
void myVisits(const User *user);
#endif