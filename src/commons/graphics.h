#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "gamecontext.h"
#include "lang.h"

//FORMATO TILES

#define TILE 8


//ZONA CARTAS

#define PLAYER_INITIAL_X 4
#define PLAYER_INITIAL_Y 13

#define DEALER_INITIAL_X 24
#define DEALER_INITIAL_Y 13

#define CARD_X_STEP 2

#define CARD_W 34
#define CARD_H 34


//HUD

#define HUD_INITIAL_X 1
#define HUD_INITIAL_Y 19
#define HUD_W 38
#define HUD_H 5

///FUNCIONES

void initGraphics();
void destroyGraphics();

void printTest(void);

void printGame(GameContext *gamectx);
void printHUD(GameContext *gamectx);
void printPNJ(GameContext *gamectx);
void printGrannyEnd(GameContext *gamectx);

void printCards(GameContext *gamectx);
void printChat(GameContext *gamectx);
void printCredits(const char *credits[], int x, int offsetY);

void printLogorr(void);
void printdosconLogo(void);
void printTitle(void);

void printTitleHotkey(char key, int x, int y);


//funciones de texto
char speakText(GameContext *gamectx,const char *texto);
void printBasicText(int margin, int y, const char *texto, int color, int fontType, int value);


void fadeToBlack(int speed);
void fadeFromBlack(int speed);

void printDecision(void);

#endif