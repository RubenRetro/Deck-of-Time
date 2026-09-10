#ifndef MENUS_H
#define MENUS_H

#include<stdbool.h>

//opciones de menu principal
typedef enum {
    MENU_OPTION_PLAY = 1,
    MENU_OPTION_LANGUAJE,
    MENU_OPTION_CREDITS,
    MENU_OPTION_EXIT
} MenuOption;


void splashScreen();
void creditsMenu(void);
MenuOption mainMenu(); //devuelve el tipo menuOption en lugar de int
bool adultTest();

int langMenu(void);

void menuExit(void);


#endif