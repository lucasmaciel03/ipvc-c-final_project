#include <stdio.h>
#include "../../utils/utils.h"
#include "../../auth/users/user.h"
#include "../../properties/properties.h"

void display_properties_menu(const User *user){
    int choice;

    PropertiesList list;
    initPropertiesList(&list);
    
    clearScreen();
    
    printf("Gestão de Propriedades\n");
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
    clearBuffer();
    
    switch(choice){
        case 1:
            
            do{
                Property* newProperty = createProperty(user, "Imobiliária");
                if(newProperty){
                    addProperty(&list, newProperty);
                }
                printf("Deseja criar outra propriedade? (1 - Sim, 0 - Não): ");
                scanf("%d", &choice);
                display_properties_menu(user);
                clearBuffer();
            } while(choice == 1);
            break;
        case 2:
            editProperty(&list, user);
            break;
        case 3:
            removeProperty(&list, user);
            break;
        case 4:
            printProperties(user, 1);
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