#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"
#include "../../clients/clients.h"
#include "../../properties/properties.h"



void display_client_main_menu(const User *user){
    int choice;

    printf("Bem Vindo, %s\n", user->username);
    printf("============================================\n");
    printf("1. Procurar Propriedadea\n");
    printf("2. Anunciar Propriedade\n");
    printf("3. Minhas Propriedades\n");
    printf("4. Ver minhas Visitas\n");
    printf("5. Editar Perfil\n");
    printf("6. Eliminar Perfil\n");
    printf("7. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    switch(choice){
        case 1:
            propertiesList(user);
            break;
        case 2:
            announceProperty(user);
            break;
        case 3:
            myProperties(user);
            break;
        case 4:
            myVisits(user);
            break;
        case 5:
            updateClientProfile(user);
            break;
        case 6:
            deleteAccount(user);
            break;
        case 7:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}