#ifndef AGENT_H
#define AGENT_H

#define MAX_AGENTS 15

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
    char dataNascimento[10];
    char password[20];
    char idade[3];
    AgentStatus status;
} Agent;

void createAgent();
void loadAgents();
void editAgent();
void list_agent_by_name();
void list_agent_by_age();
void set_agent_unavailable();
void deleteAgent();
#endif