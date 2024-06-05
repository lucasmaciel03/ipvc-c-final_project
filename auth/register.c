#include "register.h"
#include "../utils/utils.h"
#include "users/user.h"
#include <stdio.h>
#include <string.h>
#include "../clients/clients.h"
#include "../agents/agents.h"

#define FILENAME_DAT "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/users.dat"

#define FILENAME_TXT "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/clients.txt"

int userExists(const char* username) {
    FILE* file = fopen(FILENAME_DAT, "rb");
    if (file == NULL) {
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file) == 1) { // 1 = 1 element read
        if (strcmp(user.username, username) == 0 && user.role == CLIENT) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}


void create_account() {
    clearScreen();

    User newUser;
    Client newClient;

    printf("Criar Conta (0 para voltar)\n");
    printf("============================================\n");

    // Solicitar username e password
    do {
        printf("Insira o seu username: ");
        if (fgets(newUser.username, sizeof(newUser.username), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newUser.username[strcspn(newUser.username, "\n")] = 0;
        trimWhitespace(newUser.username);
        if (strcmp(newUser.username, "0") == 0) {
            return;
        }
        if (strlen(newUser.username) == 0 || newUser.username[0] == ' ') {
            printf("Erro: O username deve ser definido\n");
        }
        if (userExists(newUser.username)) {
            printf("Erro: O username já existe\n");
        }
    } while (strlen(newUser.username) == 0 || newUser.username[0] == ' ' || userExists(newUser.username));

    do {
        printf("Insira a sua password: ");
        if (fgets(newUser.password, sizeof(newUser.password), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newUser.password[strcspn(newUser.password, "\n")] = 0;
        trimWhitespace(newUser.password);
        if (strlen(newUser.password) == 0 || newUser.password[0] == ' ') {
            printf("Erro: A password deve ser definida\n");
        }
    } while (strlen(newUser.password) == 0 || newUser.password[0] == ' ');

    newUser.role = CLIENT;

    // Solicitar os restantes dados
    do {
        printf("Insira o seu Nome: ");
        if (fgets(newClient.name, sizeof(newClient.name), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newClient.name[strcspn(newClient.name, "\n")] = 0;
        trimWhitespace(newClient.name);
        if (strlen(newClient.name) == 0 || newClient.name[0] == ' ') {
            printf("Erro: O nome deve ser definido\n");
        }
    } while (strlen(newClient.name) == 0 || newClient.name[0] == ' ');

    do {
        printf("Insira o seu NIF: ");
        if (fgets(newClient.nif, sizeof(newClient.nif), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newClient.nif[strcspn(newClient.nif, "\n")] = 0;
        trimWhitespace(newClient.nif);
        if (strlen(newClient.nif) == 0 || newClient.nif[0] == ' ') {
            printf("Erro: O NIF deve ser definido\n");
        }
    } while (strlen(newClient.nif) == 0 || newClient.nif[0] == ' ');

    do {
        printf("Insira a sua Morada: ");
        if (fgets(newClient.morada, sizeof(newClient.morada), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newClient.morada[strcspn(newClient.morada, "\n")] = 0;
        trimWhitespace(newClient.morada);
        if (strlen(newClient.morada) == 0 || newClient.morada[0] == ' ') {
            printf("Erro: A morada deve ser definida\n");
        }
    } while (strlen(newClient.morada) == 0 || newClient.morada[0] == ' ');

    do {
        printf("Insira o seu Contacto: ");
        if (fgets(newClient.contacto, sizeof(newClient.contacto), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newClient.contacto[strcspn(newClient.contacto, "\n")] = 0;
        trimWhitespace(newClient.contacto);
        if (strlen(newClient.contacto) == 0 || newClient.contacto[0] == ' ') {
            printf("Erro: O contacto deve ser definido\n");
        }
    } while (strlen(newClient.contacto) == 0 || newClient.contacto[0] == ' ');

    do {
        printf("Insira a sua Data de Nascimento: ");
        if (fgets(newClient.dataNascimento, sizeof(newClient.dataNascimento), stdin) == NULL) {
            clearBuffer();
            continue;
        }
        newClient.dataNascimento[strcspn(newClient.dataNascimento, "\n")] = 0;
        trimWhitespace(newClient.dataNascimento);
        if (strlen(newClient.dataNascimento) == 0 || newClient.dataNascimento[0] == ' ' || !isValidDate(newClient.dataNascimento)) {
            printf("Erro: A data de nascimento deve ser válida no formato dd/mm/aaaa\n");
        }
    } while (strlen(newClient.dataNascimento) == 0 || newClient.dataNascimento[0] == ' ' || !isValidDate(newClient.dataNascimento));

    calculateAge(newClient.dataNascimento, newClient.idade);

    // Guardar os dados no ficheiro .dat
    FILE* file = fopen(FILENAME_DAT, "ab");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        return;
    } else {
        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);
    }

    // Guardar os dados no ficheiro .txt
    file = fopen(FILENAME_TXT, "a");
    if (file == NULL) {
        printf("Erro ao abrir ficheiro\n");
        return;
    } else {
        fprintf(file, "%s;%s;%s;%s;%s;%s;%s\n",
                newUser.username, newClient.name, newClient.nif,
                newClient.morada, newClient.contacto, newClient.dataNascimento,
                newClient.idade);
        fclose(file);
    }

    printf("Conta criada com sucesso\n");
    printf("============================================\n");
    printf("Pressione qualquer tecla para continuar...");
    getchar();
    clearScreen();
}