#ifndef INPUT_H
#define INPUT_H

#include "menus.h"
#include "lang.h"

char waitAdvanceButton(void);
char getPlayerChoice(void);
char getAdultAnswer(void);
char getPlayerInputBug(void);

MenuOption menuInput(void);

char languageInput(void);

#endif