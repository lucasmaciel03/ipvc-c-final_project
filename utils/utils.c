#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void clearScreen()
{
    system(CLEAR);
}

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause()
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void exit_system()
{
    printf("A sair do sistema...\n");
    exit(0);
}

void trimWhitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) {
        // All spaces
        *str = '\0';
        return;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';
}