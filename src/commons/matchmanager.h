#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H

#include "gamecontext.h"

//reiniciar partida completa (mejor de 3, mazo, estado global
void resetMatch(GameContext *gamectx);

//reinicia solo una mano(ronda player y dealer)
void resetHand(GameContext *gamectx);


#endif