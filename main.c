#include <stdio.h>
#include "utils/utils.h"
#include "menus/main_menu/main_menu.h"

int main(){
    clearScreen();
    while(1){
        display_main_menu();
    }
    return 0;
}