#include "login.h"
#include "../utils/utils.h"
#include "users/user.h"
#include <stdio.h>
#include <string.h>

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/users.dat"


int load_user(const char *username, const char *password, User *out_user)
{
    // Load user from .dat file
    FILE *file = fopen(FILENAME, "rb"); // read binary mode
    if (file == NULL)
    {
        clearScreen();
        printf("Error: Could not open file\n");
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0)
        {
            *out_user = user;
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void login(){
    clearScreen();
    
    char username[20];
    char password[20];
    
    User  user;
    
    int login_success = 0;
    
    do {
        printf("Iniciar Sessão (0 para voltar)\n");
        printf("============================================\n");
        printf("Insira o seu username: ");
        scanf("%s", username);
        // Check if the user wants to return to the main menu
        if (strcmp(username, "0") == 0) {
            return;
        }
        printf("Insira a sua password: ");
        scanf("%s", password);
        
        if(load_user(username, password, &user)){
            login_success = 1;
            clearScreen();
            display_menu(&user);
        } else {
            clearScreen();
            printf("Erro: Credenciais inválidas\n");
        }
    } while (!login_success);
}

