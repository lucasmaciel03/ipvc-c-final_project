#ifndef _UTILS
#define _UTILS

void clearScreen();
void clearBuffer();
void pause();
void exit_system();
void trimWhitespace(char* str);
int isValidDate(const char *date);
void getCurrentDate(char* date);
int compareDates(const char *date1, const char *date2);
int isValidTime(const char *time);

#endif