#ifndef AGENT_H
#define AGENT_H

#define MAX_AGENTS 15

#include "../auth/users/user.h"

typedef enum {
    DISPONIVEL,
    INDISPONIVEL,
} AgentStatus;

typedef struct {
    char username[20];
    char name[20];
    char nif[10];
    char morada[50];
    char contacto[9];
    char dataNascimento[11];
    char idade[4];
    AgentStatus status;
} Agent;

void createAgent(const User *user);
void printAgents(const User *user, int showMenu);
void editAgent(const User *user);
void deleteAgent(const User *user);
int agentExistsv2(const char* username);
void listAgentByUsername(const User *user);
void orderAgentsByName(const User *user);
void orderAgentByAge(const User *user);
void setAgentUnavailable(const User *user);

#endif