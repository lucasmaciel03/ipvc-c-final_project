#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"
#include "../properties/properties.h"
#include "../agents/agents.h"
#include "../auth/users/user.h"
#include "../menus/client_main_menu/client_main_menu.h"
#include "clients.h"
#include "../role_agents/role_agents.h"

#define FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/properties.txt"

#define FILENAME_VISITAS "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/visits.txt"

#define FILENAME_CLIENTS "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/clients.txt"

#define USERS_FILENAME "/Users/lucas.maciel/Documents/ipvc-git/ipvc-c-final_project/data/users.dat"

void updatePropertyInFile(int propertyId, const char* newOwner, PropertyStatus newStatus) {
    FILE* file = fopen(FILENAME, "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Property property;
        sscanf(line, "%d;%49[^;];%54[^;];%lf;%10[^;];%19[^;];%49[^;];%d",
               &property.id, property.morada, property.descricao, &property.preco,
               property.data, property.agente, property.proprietario, (int*)&property.status);

        if (property.id == propertyId) {
            // Atualiza a data da propriedade
            getCurrentDate(property.data);
            // Atualiza o proprietário e o status da propriedade
            strcpy(property.proprietario, newOwner);
            property.status = newStatus;
        }

        fprintf(tempFile, "%d;%s;%s;%.2f;%s;%s;%s;%d\n", property.id, property.morada, property.descricao,
                property.preco, property.data, property.agente, property.proprietario, property.status);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void propertiesList(const User *user) {
    while (1) {
        clearScreen();

        printPropertiesToSale(user, 1);

        int propertyId;
        printf("============================================\n");
        printf("Está interessado em alguma propriedade? Se sim, indique o ID (0 para voltar): ");
        scanf("%d", &propertyId);
        clearBuffer();

        if (propertyId == 0) {
            display_client_main_menu(user);
            return;
        }

        // Verifica se o usuário é o proprietário da propriedade
        FILE* file = fopen(FILENAME, "r");
        if (file == NULL) {
            printf("Erro: Não foi possível abrir o ficheiro de propriedades\n");
            return;
        }

        int isOwner = 0;
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            int id;
            char owner[256];

            sscanf(line, "%d;%*[^;];%*[^;];%*f;%*[^;];%*[^;];%[^;];%*d", &id, owner);

            if (id == propertyId) {
                if (strcmp(owner, user->username) == 0) {
                    isOwner = 1;
                }
                break;
            }
        }

        fclose(file);

        if (isOwner) {
            printf("Erro: Você não pode comprar ou arrendar uma propriedade que você anunciou.\n");
            continue;  // Volta a perguntar o ID da propriedade
        }

        int choice;
        printf("============================================\n");
        printf("O que deseja fazer com a propriedade?\n");
        printf("1. Comprar esta propriedade\n");
        printf("2. Arrendar esta propriedade\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 1) {
            updatePropertyInFile(propertyId, user->username, VENDIDA);
            printf("Propriedade comprada com sucesso!\n");
        } else if (choice == 2) {
            updatePropertyInFile(propertyId, user->username, ARRENDADA);
            printf("Propriedade arrendada com sucesso!\n");
        } else {
            printf("Opção inválida.\n");
        }

        break;  // Sai do loop após uma compra ou arrendamento bem-sucedido
    }
}

Property* announceProperty(const User *user) {
    Property* newProperty = createProperty(user, user->username);
    if (newProperty) {
        printf("Propriedade anunciada com sucesso!\n");
    } else {
        printf("Erro ao anunciar a propriedade.\n");
    }
    return newProperty;
}

void myProperties(const User *user) {
    clearScreen();
    printPropertiesByOwner(user);
    
    int choice;
    printf("============================================\n");
    printf("1. Voltar\n");
    printf("2. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if (choice == 1) {
        display_client_main_menu(user);
    } else if (choice == 2) {
        exit_system();
    } else {
        printf("Opção inválida.\n");
    }
}

void updateClientProfile(const User* user) {
    FILE* file = fopen(FILENAME_CLIENTS, "r");
    FILE* tempFile = fopen("temp_clients.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }

    char line[256];
    Client client;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%19[^;];%19[^;];%9[^;];%49[^;];%8[^;];%10[^;];%3[^;]",
               client.username, client.name, client.nif, client.morada, client.contacto,
               client.dataNascimento, client.idade);

        if (strcmp(client.username, user->username) == 0) {
            found = 1;
            printf("Informação atual do perfil:\n");
            printf("Nome: %s\n", client.name);
            printf("NIF: %s\n", client.nif);
            printf("Morada: %s\n", client.morada);
            printf("Contacto: %s\n", client.contacto);
            printf("Data de Nascimento: %s\n", client.dataNascimento);
            printf("============================================\n");

            int choice;
            printf("O que deseja alterar?\n");
            printf("1. Nome\n");
            printf("2. NIF\n");
            printf("3. Morada\n");
            printf("4. Contacto\n");
            printf("5. Data de Nascimento\n");
            printf("0. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &choice);
            clearBuffer();

            switch (choice) {
                case 1:
                    do {
                        printf("Insira o novo nome: ");
                        if (fgets(client.name, sizeof(client.name), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        client.name[strcspn(client.name, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(client.name);
                        if (strlen(client.name) == 0 || client.name[0] == ' ') {
                            printf("Erro: O nome deve ser definido\n");
                        }
                    } while (strlen(client.name) == 0 || client.name[0] == ' ');
                    break;
                case 2:
                    do {
                        printf("Insira o novo NIF: ");
                        if (fgets(client.nif, sizeof(client.nif), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        client.nif[strcspn(client.nif, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(client.nif);
                        if (strlen(client.nif) == 0 || client.nif[0] == ' ') {
                            printf("Erro: O NIF deve ser definido\n");
                        }
                    } while (strlen(client.nif) == 0 || client.nif[0] == ' ');
                    break;
                case 3:
                    do {
                        printf("Insira a nova morada: ");
                        if (fgets(client.morada, sizeof(client.morada), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        client.morada[strcspn(client.morada, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(client.morada);
                        if (strlen(client.morada) == 0 || client.morada[0] == ' ') {
                            printf("Erro: A morada deve ser definida\n");
                        }
                    } while (strlen(client.morada) == 0 || client.morada[0] == ' ');
                    break;
                case 4:
                    do {
                        printf("Insira o novo contacto: ");
                        if (fgets(client.contacto, sizeof(client.contacto), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        client.contacto[strcspn(client.contacto, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(client.contacto);
                        if (strlen(client.contacto) == 0 || client.contacto[0] == ' ') {
                            printf("Erro: O contacto deve ser definido\n");
                        }
                    } while (strlen(client.contacto) == 0 || client.contacto[0] == ' ');
                    break;
                case 5:
                    do {
                        printf("Insira a nova data de nascimento: ");
                        if (fgets(client.dataNascimento, sizeof(client.dataNascimento), stdin) == NULL) {
                            clearBuffer();
                            continue;
                        }
                        client.dataNascimento[strcspn(client.dataNascimento, "\n")] = '\0'; // Remove newline character
                        trimWhitespace(client.dataNascimento);
                        if (strlen(client.dataNascimento) == 0 || client.dataNascimento[0] == ' ' || !isValidDate(client.dataNascimento)) {
                            printf("Erro: A data de nascimento deve ser válida no formato dd/mm/aaaa\n");
                        }
                    } while (strlen(client.dataNascimento) == 0 || client.dataNascimento[0] == ' ' || !isValidDate(client.dataNascimento));
                    calculateAge(client.dataNascimento, client.idade);
                    break;
                case 0:
                    fclose(file);
                    fclose(tempFile);
                    remove("temp_clients.txt");
                    display_client_main_menu(user);
                    return;
                default:
                    printf("Opção inválida\n");
                    break;
            }
        }

        fprintf(tempFile, "%s;%s;%s;%s;%s;%s;%s\n", client.username, client.name, client.nif, client.morada,
                client.contacto, client.dataNascimento, client.idade);
    }

    if (!found) {
        printf("Erro: Cliente não encontrado.\n");
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME_CLIENTS);
    rename("temp_clients.txt", FILENAME_CLIENTS);

    printf("Perfil atualizado com sucesso!\n");
    
    int choice;
    printf("============================================\n");
    printf("1. Editar novamente\n");
    printf("2. Voltar\n");
    printf("3. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();
    
    if (choice == 1) {
        updateClientProfile(user);
    } else if (choice == 2) {
        display_client_main_menu(user);
    } else if (choice == 3) {
        exit_system();
    } else {
        printf("Opção inválida.\n");
    }
    
    return;
}

void deleteAccount(const User* user) {
    char choice;
    printf("Tem certeza que deseja mesmo eliminar a sua conta, todas as suas propriedades serão eliminadas (S/N)? ");
    scanf(" %c", &choice);

    if (choice != 'S' && choice != 's') {
        printf("Operação cancelada.\n");
        return;
    }

    // Eliminar a conta do arquivo clients.txt
    FILE* file = fopen(FILENAME_CLIENTS, "r");
    FILE* tempFile = fopen("temp_clients.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        Client client;
        sscanf(line, "%19[^;];%19[^;];%9[^;];%49[^;];%8[^;];%10[^;];%3[^;]",
               client.username, client.name, client.nif, client.morada, client.contacto,
               client.dataNascimento, client.idade);

        if (strcmp(client.username, user->username) == 0) {
            found = 1;
            continue; // Pula a linha correspondente ao cliente a ser deletado
        }

        fprintf(tempFile, "%s;%s;%s;%s;%s;%s;%s\n", client.username, client.name, client.nif, client.morada,
                client.contacto, client.dataNascimento, client.idade);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILENAME_CLIENTS);
        rename("temp_clients.txt", FILENAME_CLIENTS);
        printf("Conta eliminada com sucesso.\n");
    } else {
        remove("temp_clients.txt");
        printf("Erro: Conta não encontrada.\n");
        return;
    }

    // Eliminar a conta do arquivo users.dat
    file = fopen(USERS_FILENAME, "rb");
    tempFile = fopen("temp_users.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de usuários.\n");
        return;
    }

    User tempUser;

    while (fread(&tempUser, sizeof(User), 1, file)) {
        if (strcmp(tempUser.username, user->username) != 0) {
            fwrite(&tempUser, sizeof(User), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(USERS_FILENAME);
    rename("temp_users.dat", USERS_FILENAME);

    // Eliminar as propriedades associadas do arquivo properties.txt
    file = fopen(FILENAME, "r");
    tempFile = fopen("temp_properties.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Erro ao abrir o ficheiro de propriedades.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        Property property;
        sscanf(line, "%d;%49[^;];%54[^;];%lf;%10[^;];%19[^;];%49[^;];%d",
               &property.id, property.morada, property.descricao, &property.preco,
               property.data, property.agente, property.proprietario, (int*)&property.status);

        if (strcmp(property.proprietario, user->username) == 0) {
            continue; // Pula as linhas das propriedades do cliente a ser deletado
        }

        fprintf(tempFile, "%d;%s;%s;%.2f;%s;%s;%s;%d\n", property.id, property.morada, property.descricao,
                property.preco, property.data, property.agente, property.proprietario, property.status);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp_properties.txt", FILENAME);

    printf("Todas as propriedades associadas foram eliminadas.\n");
}

// Função para retornar todas as visitas associadas ao cliente logado
void myVisits(const User *user) {
    FILE* file = fopen(FILENAME_VISITAS, "r");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o ficheiro de visitas\n");
        return;
    }

    Visit visit;
    int found = 0;

    printf("============================================\n");
    printf("Visitas agendadas:\n");
    printf("============================================\n");

    while (fread(&visit, sizeof(Visit), 1, file)) {
        if (strcmp(visit.clientUsername, user->username) == 0) {
            found = 1;
            printf("ID da Propriedade: %d\n", visit.propertyId);
            printf("Data da Visita: %s\n", visit.date);
            printf("Hora da Visita: %s\n", visit.time);
            printf("Agente: %s\n", visit.agentUsername);
            printf("Estado da Visita: %s\n", visit.status == AGENDADA ? "Agendada" : "Realizada");
            printf("============================================\n");
        }
    }

    fclose(file);

    if (!found) {
        printf("Nenhuma visita agendada.\n");
    }

    int choice;
    printf("1. Voltar\n");
    printf("2. Sair\n");
    printf("============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice == 1) {
        display_client_main_menu(user);
    } else if (choice == 2) {
        exit_system();
    } else {
        printf("Opção inválida.\n");
    }
}



