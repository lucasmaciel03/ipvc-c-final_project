#include <stdio.h>
#include <string.h>
#include "../auth/users/user.h"
#include "agents.h"

#define FILENAME "../data/agents.txt"

int countAgents(){
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro!\n");
        return 0;
    }
    
    int count = 0;
    Agent agent;
    while(fscanf(
        file,
        "Username:%19[^;];\nNome:%19[^;];\nNIF:%9[^;];\nMorada:%49[^;];\nContacto:%9[^;];\nData de Nascimento:%9[^;];\nPassword:%19[^;];\nEstado:%d\n",
        agent.username, agent.name, agent.nif, agent.morada, agent.contacto, agent.dataNascimento, agent.password, &agent.status) == 8) {
        count++;
    };
    
    fclose(file);
    return count;
}
//verificar se o agente existe
void agentExists(char *username, int *found){
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro!\n");
        *found = 0;
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char existingUsername[20];
        sscanf(line, "%19[^;]:", existingUsername);

        if (strcmp(existingUsername, username) == 0) {
            fclose(file);
            *found = 1;
            return;
        }
    }

    fclose(file);
    *found = 0;
}

// função para criar agente
void createAgent(){
    Agent newAgent;

    printf("Insira o username do agente: ");
    scanf("%s", newAgent.username);
    printf("Insira a password do agente: ");
    scanf("%s", newAgent.password);
    printf("Insira o nome do agente: ");
    scanf("%s", newAgent.name);
    printf("Insira o NIF do agente: ");
    scanf("%s", newAgent.nif);
    printf("Insira a morada do agente: ");
    scanf("%s", newAgent.morada);
    printf("Insira o contacto do agente: ");
    scanf("%s", newAgent.contacto);
    printf("Insira a data de nascimento do agente (dd-mm-yyyy): ");
    scanf("%s", newAgent.dataNascimento);
    newAgent.status = DISPONIVEL;

    int agentCount = countAgents();

    if(agentCount == -1){
        printf("Erro: Não foi possível contar os agentes!\n");
        return;
    }

    if(agentCount >= MAX_AGENTS) {
        printf("Erro: Número máximo de agentes atingido!\n");
        return;
    }

    if(agentExists(newAgent.username)){
        printf("Erro: O username já existe!\n");
        return;
    }

    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro!\n");
        return;
    }
    fprintf(file,"==============================\n");
    fprintf(file, "Username:%s\nNome:%s\nNIF:%s\nMorada:%s\nContacto:%s\nData de Nascimento:%s\nPassword:%s\nEstado:%d\n",
            newAgent.username, newAgent.name, newAgent.nif, newAgent.morada,
            newAgent.contacto, newAgent.dataNascimento, newAgent.password,
            newAgent.status);
    fprintf(file,"==============================\n");
    fclose(file);

    createUser(newAgent.username, newAgent.password, AGENT);

    printf("Agente %s criado com sucesso!\n", newAgent.name);
}


//função para editar os agentes
void editAgent(){

}



