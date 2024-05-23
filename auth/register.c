#include "register.h"
#include "../utils/utils.h"
#include "users/user.h"
#include <stdio.h>
#include <string.h>

#define FILENAME "../data/users.dat"

void create_account(){
    clearScreen();
    
    char username[20];
    char password[20];
    
    User user;
    
    printf("Criar Conta (0 para voltar)\n");
    printf("============================================\n");
    printf("Insira o seu username: ");
    scanf("%s", username);
    // Check if the user wants to return to the main menu
    if (strcmp(username, "0") == 0) {
        return;
    }
    printf("Insira a sua password: ");
    scanf("%s", password);

    createUser(username, password, CLIENT);
    printf("Conta criada com sucesso\n");
    printf("============================================\n");
    printf("Pressione qualquer tecla para continuar...");
    getchar();
    getchar();
    clearScreen();
}