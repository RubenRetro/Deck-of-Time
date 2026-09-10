#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "deck.h" // lo necesitamos para usar tipo Card
#include <stdbool.h> //para crear variables tipo bool   

typedef struct {

//baraja de juego
Card deck[DECK_SIZE]; 
int deckPosition;  //en que posicion del mazo estamos   

//manos de jugador y dealer
Card playerHand[MAX_HANDSIZE];
int  playerHandSize;

Card dealerHand[MAX_HANDSIZE];
int dealerHandSize;
//mecanicas específicas de Dealer
bool hideDealerCard; //se usa para saber si el dealer debe ocultar la primera carta o no.


//UI, variables para posición de mensajes etc.
int textRow;

//contador de rondas y manos
int roundNumber;
int handNumber;

//PUNTUACIONES
int playerScore; //numero de manos ganadas en la ronda
int dealerScore;

int playerRoundPoints; // rondas ganadas
int dealerRoundPoints;


int handResult; // indica si ha ganado player , dealer o empate

#define HANDS_PER_ROUND 3
int mouthFrame;
int mouthTimer;
bool activePNJ;

char message[256];
bool dialogueActive;

//contenido adulto
bool adultContent;

}GameContext;


#endif