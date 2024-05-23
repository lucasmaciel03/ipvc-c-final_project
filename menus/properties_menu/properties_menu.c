#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"

void display_properties_menu(const User *user){
    int choice;

    printf("Gestão de Agentes\n");
    printf("============================================\n");
    printf("1. Criar Propriedades \n");
    printf("2. Editar Propriedades \n");
    printf("3. Remover Propriedades \n");
    printf("4. Listar Propriedades e seus preços \n");
    printf("5. Voltar\n");
    printf("6. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            //createProperty();
            break;
        case 2:
            // edit_property();
            break;
        case 3:
            // remove_property();
            break;
        case 4:
            // list_property();
            break;
        case 5:
            display_menu(user);
            break;
        case 6:
            exit_system();
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}