#include <stdio.h>
#include <string.h>
#include "agents.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include "../auth/users/user.h"
#include "../menus/agent_menu/agent_menu.h"

#define FILENAME "../data/agents.txt"

Agent agents[MAX_AGENTS];
int numAgents = 0;

//função para verificar se o username já existe
int agentExists(char* username){
    for(int i = 0; i < numAgents; i++){
        if(strcmp(agents[i].username, username) == 0){
            return 1;
        }
    }
    return 0;
}

//função para adicionar um agente
void addAgent(const Agent newAgent){
    if(numAgents < MAX_AGENTS){
        agents[numAgents++] = newAgent;
    }else{
        printf("Número máximo de agentes atingido\n");
    }
}

//função para criar novo agente
void createAgent(){
    Agent newAgent;
    User user;
    
    while (getchar() != '\n');
    printf("Username:");
    fgets(newAgent.username, sizeof(newAgent.username), stdin);
    newAgent.username[strcspn(newAgent.username, "\n")] = 0;
    if(agentExists(newAgent.username)){
        printf("Username já existe\n");
        return;
    }
    do{
        printf("Nome do Agente:");
        if(fgets(newAgent.name, sizeof(newAgent.name), stdin) == NULL){
            clearBuffer();
            continue;
        }
        newAgent.name[strcspn(newAgent.name, "\n")] = 0;
        trimWhitespace(newAgent.name);
        if(strlen(newAgent.name) == 0 || newAgent.name[0] == ' '){
            printf("Erro: O agente deve ter um nome definido\n");
        }
    }while
    (strlen(newAgent.name) == 0 || newAgent.name[0] == ' ');

    do{
        printf("NIF do Agente:");
        if(fgets(newAgent.nif, sizeof(newAgent.nif), stdin) == NULL){
            clearBuffer();
            continue;
        }
        newAgent.nif[strcspn(newAgent.nif, "\n")] = 0;
        trimWhitespace(newAgent.nif);
        if(strlen(newAgent.nif) == 0 || newAgent.nif[0] == ' '){
            printf("Erro: O agente deve ter um NIF definido\n");
        }
    }while
    (strlen(newAgent.nif) == 0 || newAgent.nif[0] == ' ');
    while (getchar() != '\n');
    do{
        printf("Morada do Agente:");
        if(fgets(newAgent.morada, sizeof(newAgent.morada), stdin) == NULL){
            clearBuffer();
            continue;
        }
        newAgent.morada[strcspn(newAgent.morada, "\n")] = 0;
        trimWhitespace(newAgent.morada);
        if(strlen(newAgent.morada) == 0 || newAgent.morada[0] == ' '){
            printf("Erro: O agente deve ter uma morada definida\n");
        }
    }while
    (strlen(newAgent.morada) == 0 || newAgent.morada[0] == ' ');

    do{
        printf("Contacto do Agente:");
        if(fgets(newAgent.contacto, sizeof(newAgent.contacto), stdin) == NULL){
            clearBuffer();
            continue;
        }
        newAgent.contacto[strcspn(newAgent.contacto, "\n")] = 0;
        trimWhitespace(newAgent.contacto);
        if(strlen(newAgent.contacto) == 0 || newAgent.contacto[0] == ' '){
            printf("Erro: O agente deve ter um contacto definido\n");
        }
    }while
    (strlen(newAgent.contacto) == 0 || newAgent.contacto[0] == ' ');
    while (getchar() != '\n');
    do{
        printf("Data de Nascimento do Agente:");
        if(fgets(newAgent.dataNascimento, sizeof(newAgent.dataNascimento), stdin) == NULL){
            clearBuffer();
            continue;
        }
        newAgent.dataNascimento[strcspn(newAgent.dataNascimento, "\n")] = 0;
        trimWhitespace(newAgent.dataNascimento);
        if(strlen(newAgent.dataNascimento) == 0 || newAgent.dataNascimento[0] == ' ') {
            printf("Erro: O agente deve ter uma data de nascimento definida\n");
        }
    }while
    (strlen(newAgent.dataNascimento) == 0 || newAgent.dataNascimento[0] == ' ');
    while (getchar() != '\n');
    do {
        printf("Password do Agente:");
        if (fgets(newAgent.password, sizeof(newAgent.password), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.password[strcspn(newAgent.password, "\n")] = 0;
        trimWhitespace(newAgent.password);
        if (strlen(newAgent.password) == 0 || newAgent.password[0] == ' ') {
            printf("Erro: O agente deve ter uma password definida\n");
        }
    } while
    (strlen(newAgent.password) == 0 || newAgent.password[0] == ' ');

    do {
        printf("Idade do Agente:");
        if (fgets(newAgent.idade, sizeof(newAgent.idade), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newAgent.idade[strcspn(newAgent.idade, "\n")] = 0;
        trimWhitespace(newAgent.idade);
        if (strlen(newAgent.idade) == 0 || newAgent.idade[0] == ' ') {
            printf("Erro: O agente deve ter uma idade definida\n");
        }
    } while
    (strlen(newAgent.idade) == 0 || newAgent.idade[0] == ' ');

    newAgent.status = DISPONIVEL;

    addAgent(newAgent);

    FILE *file = fopen(FILENAME, "w");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    for(int i = 0; i < numAgents; i++){
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                agents[i].username, agents[i].name, agents[i].nif,
                agents[i].morada, agents[i].contacto, agents[i].dataNascimento,
                agents[i].password, agents[i].idade, agents[i].status);
    }
    fclose(file);
    printf("Agente %s criado com sucesso\n", newAgent.username);
    display_agent_menu(&user);
}

//função para carregar os agentes e os dados dos agentes do ficheiro
void loadAgents(){
    FILE *file = fopen(FILENAME, "r");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    numAgents = 0;
    while(fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
                 agents[numAgents].username, agents[numAgents].name, agents[numAgents].nif,
                 agents[numAgents].morada, agents[numAgents].contacto, agents[numAgents].dataNascimento,
                 agents[numAgents].password, agents[numAgents].idade, &agents[numAgents].status) == 9){
        printf("Username: %s\n", agents[numAgents].username);
        printf("Nome: %s\n", agents[numAgents].name);
        printf("NIF: %s\n", agents[numAgents].nif);
        printf("Morada: %s\n", agents[numAgents].morada);
        printf("Contacto: %s\n", agents[numAgents].contacto);
        printf("Data de Nascimento: %s\n", agents[numAgents].dataNascimento);
        printf("Password: %s\n", agents[numAgents].password);
        printf("Idade: %s\n", agents[numAgents].idade);
        printf("Status: %d\n", agents[numAgents].status);
        numAgents++;
    }
    fclose(file);
}

void editField(char *field, const char *message, size_t size) {
    while (getchar() != '\n');
    do {
        printf("%s (atual: %s): ", message, field);
        if (fgets(field, size, stdin) == NULL) {
            clearBuffer();
            continue;
        }
        field[strcspn(field, "\n")] = 0;
        trimWhitespace(field);
        if (strlen(field) == 0 || field[0] == ' ') {
            printf("Erro: Campo inválido\n");
        }
    } while (strlen(field) == 0 || field[0] == ' ');
}

//ver o que se passa porque não edita na totalidade
void editAgent() {
    while (getchar() != '\n');
    char username[20];
    do {
        printf("Username do agente a editar:");
        if (fgets(username, sizeof(username), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        username[strcspn(username, "\n")] = 0;
        trimWhitespace(username);
        if (strlen(username) == 0 || username[0] == ' ') {
            printf("Erro: O username do agente deve ser definido\n");
        }
    } while (strlen(username) == 0 || username[0] == ' ');

    loadAgents();

    int i;
    for (i = 0; i < numAgents; i++) {
        if (strcmp(agents[i].username, username) == 0) {
            break;
        }
    }

    if (i == numAgents) {
        printf("Agente não encontrado\n");
        return;
    }
    printf("Editar informações do agente %s:\n", username);
    while (getchar() != '\n');
    do {
        editField(agents[i].name, "Novo nome do Agente", sizeof(agents[i].name));
    } while (strlen(agents[i].name) == 0 || agents[i].name[0] == ' ');
    while (getchar() != '\n');
    do {
        editField(agents[i].nif, "Novo NIF do Agente", sizeof(agents[i].nif));
    } while (strlen(agents[i].nif) == 0 || agents[i].nif[0] == ' ');
    while (getchar() != '\n');
    do {
        editField(agents[i].morada, "Nova morada do Agente", sizeof(agents[i].morada));
    } while (strlen(agents[i].morada) == 0 || agents[i].morada[0] == ' ');
    do {
        editField(agents[i].contacto, "Novo contacto do Agente", sizeof(agents[i].contacto));
    } while (strlen(agents[i].contacto) == 0 || agents[i].contacto[0] == ' ');
    while (getchar() != '\n');
    do {
        editField(agents[i].dataNascimento, "Nova data de nascimento do Agente", sizeof(agents[i].dataNascimento));
    } while (strlen(agents[i].dataNascimento) == 0 || agents[i].dataNascimento[0] == ' ');
    while (getchar() != '\n');
    do {
        editField(agents[i].password, "Nova password do Agente", sizeof(agents[i].password));
    } while (strlen(agents[i].password) == 0 || agents[i].password[0] == ' ');
    do {
        editField(agents[i].idade, "Nova idade do Agente", sizeof(agents[i].idade));
    } while (strlen(agents[i].idade) == 0 || agents[i].idade[0] == ' ');

    editField(agents[i].status == DISPONIVEL ? "Disponível" : "Indisponível", "Status do Agente", sizeof(agents[i].status));

    // Atualizar o arquivo com as informações editadas
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    for (int i = 0; i < numAgents; i++) {
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                agents[i].username, agents[i].name, agents[i].nif,
                agents[i].morada, agents[i].contacto, agents[i].dataNascimento,
                agents[i].password, agents[i].idade, agents[i].status);
    }
    fclose(file);
    printf("Agente %s editado com sucesso\n", username);
}

//função para listar o agente pelo nome pedido pelo utilizador - funciona
void list_agent_by_name(){
    char name[20];
    do{
        printf("Nome do agente a procurar:");
        if(fgets(name, sizeof(name), stdin) == NULL){
            clearBuffer();
            continue;
        }
        name[strcspn(name, "\n")] = 0;
        trimWhitespace(name);
        if(strlen(name) == 0 || name[0] == ' '){
            printf("Erro: O nome do agente deve ser definido\n");
        }
    }while
    (strlen(name) == 0 || name[0] == ' ');

    loadAgents();
    for(int i = 0; i < numAgents; i++){
        if(strcmp(agents[i].name, name) == 0){
            printf("Username: %s\n", agents[i].username);
            printf("Nome: %s\n", agents[i].name);
            printf("NIF: %s\n", agents[i].nif);
            printf("Morada: %s\n", agents[i].morada);
            printf("Contacto: %s\n", agents[i].contacto);
            printf("Data de Nascimento: %s\n", agents[i].dataNascimento);
            printf("Password: %s\n", agents[i].password);
            printf("Idade: %s\n", agents[i].idade);
            printf("Status: %s\n", agents[i].status == DISPONIVEL ? "Disponível" : "Indisponível");
        }
    }
}

void list_agent_by_age(){
    loadAgents();
    for(int i = 0; i < numAgents; i++){
        for(int j = i + 1; j < numAgents; j++){
            if(atoi(agents[i].idade) > atoi(agents[j].idade)){
                Agent temp = agents[i];
                agents[i] = agents[j];
                agents[j] = temp;
            }
        }
    }
    for(int i = 0; i < numAgents; i++){
        printf("Username: %s\n", agents[i].username);
        printf("Nome: %s\n", agents[i].name);
        printf("NIF: %s\n", agents[i].nif);
        printf("Morada: %s\n", agents[i].morada);
        printf("Contacto: %s\n", agents[i].contacto);
        printf("Data de Nascimento: %s\n", agents[i].dataNascimento);
        printf("Password: %s\n", agents[i].password);
        printf("Idade: %s\n", agents[i].idade);
        printf("Status: %s\n", agents[i].status == DISPONIVEL ? "Disponível" : "Indisponível");
    }
}

void set_agent_unavailable(){
    char username[20];
    do{
        printf("Username do agente a colocar como indisponível:");
        if(fgets(username, sizeof(username), stdin) == NULL){
            clearBuffer();
            continue;
        }
        username[strcspn(username, "\n")] = 0;
        trimWhitespace(username);
        if(strlen(username) == 0 || username[0] == ' '){
            printf("Erro: O username do agente deve ser definido\n");
        }
    }while
    (strlen(username) == 0 || username[0] == ' ');

    loadAgents();

    int i;
    for(i = 0; i < numAgents; i++){
        if(strcmp(agents[i].username, username) == 0){
            break;
        }
    }

    if(i == numAgents){
        printf("Agente não encontrado\n");
        return;
    }

    agents[i].status = INDISPONIVEL;

    FILE *file = fopen(FILENAME, "w");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    for(int i = 0; i < numAgents; i++){
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                agents[i].username, agents[i].name, agents[i].nif,
                agents[i].morada, agents[i].contacto, agents[i].dataNascimento,
                agents[i].password, agents[i].idade, agents[i].status);
    }
    fclose(file);
    printf("Agente %s colocado como indisponível\n", username);
}

void deleteAgent(){
    while(getchar() != '\n');
    char username[20];
    do{
        printf("Username do agente a remover:");
        if(fgets(username, sizeof(username), stdin) == NULL){
            clearBuffer();
            continue;
        }
        username[strcspn(username, "\n")] = 0;
        trimWhitespace(username);
        if(strlen(username) == 0 || username[0] == ' '){
            printf("Erro: O username do agente deve ser definido\n");
        }
    }while
    (strlen(username) == 0 || username[0] == ' ');

    loadAgents();

    int i;
    for(i = 0; i < numAgents; i++){
        if(strcmp(agents[i].username, username) == 0){
            break;
        }
    }

    if(i == numAgents){
        printf("Agente não encontrado\n");
        return;
    }

    for(int j = i; j < numAgents - 1; j++){
        agents[j] = agents[j + 1];
    }
    numAgents--;

    FILE *file = fopen(FILENAME, "w");
    if(file == NULL){
        printf("Erro ao abrir ficheiro\n");
        return;
    }
    for(int i = 0; i < numAgents; i++){
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                agents[i].username, agents[i].name, agents[i].nif,
                agents[i].morada, agents[i].contacto, agents[i].dataNascimento,
                agents[i].password, agents[i].idade, agents[i].status);
    }
    fclose(file);
    printf("Agente %s removido com sucesso\n", username);
}


