#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

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

int isValidDate(const char *date) {
    int day, month, year;
    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0;
    }

    // Verificar ano razoável
    if (year < 1900 || year > 2100) {
        return 0;
    }

    // Verificar mês válido
    if (month < 1 || month > 12) {
        return 0;
    }

    // Verificar dia válido para cada mês
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verificar ano bissexto
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return 0;
    }

    return 1;
}

// create a function to get the current date in the format dd/mm/yyyy
void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Verifica se a hora está no formato hh:mm
int isValidTime(const char *time) {
    int hour, minute;
    if (sscanf(time, "%d:%d", &hour, &minute) != 2) {
        return 0;
    }
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return 0;
    }
    return 1;
}

// Compara duas datas no formato dd/mm/aaaa
int compareDates(const char *date1, const char *date2) {
    int day1, month1, year1;
    int day2, month2, year2;
    sscanf(date1, "%d/%d/%d", &day1, &month1, &year1);
    sscanf(date2, "%d/%d/%d", &day2, &month2, &year2);

    if (year1 != year2) {
        return year1 - year2;
    }
    if (month1 != month2) {
        return month1 - month2;
    }
    return day1 - day2;
}