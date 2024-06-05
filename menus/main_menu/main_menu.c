#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/login.h"
#include "../../auth/register.h"

void display_main_menu(){
    int choice;

    clearScreen();
    printf("Bem Vindo ao Sistema de Gestão Imobiliária\n");
    printf("============================================\n");
    printf("1. Iniciar Sessão\n");
    printf("2. Criar Conta\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            login();
            break;
        case 2:
            create_account();
            break;
        case 3:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}