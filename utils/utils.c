#include <stdlib.h>
#include <stdio.h>

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
