#include "matchmanager.h"   //incluye las definiciones resethand y resetmatch

/////RESET MATCH (NUEVA PARTIDA GLOBAL///////
void resetMatch(GameContext *gamectx){
    
    
    //MAZO
    initDeck(gamectx->deck);
    shuffleDeck(gamectx->deck);
    gamectx->deckPosition = 0;

    ////PUNTUACIONES
    gamectx->playerScore = 0; //numero de manos ganadas en la ronda
    gamectx->dealerScore = 0;

    gamectx->playerRoundPoints = 0;
    gamectx->dealerRoundPoints = 0;

    //contador de rondas
    gamectx->roundNumber = 0;
    gamectx->handNumber = 0;

        /* UI */

    gamectx->mouthFrame = 0;
    gamectx->mouthTimer = 0;

    gamectx->message[0] = '\0';
}

/////RESET MANO (CADA RONDA /////
void resetHand(GameContext *gamectx){

    //reset manos, num cartas y deck(mano)
    gamectx->playerHandSize = 0;
    gamectx->dealerHandSize = 0;

    for (int i = 0; i < MAX_HANDSIZE; i++) {
            gamectx->playerHand[i].rank = 0;
            gamectx->playerHand[i].suit = 0;

            gamectx->dealerHand[i].rank = 0;
            gamectx->dealerHand[i].suit = 0;

            //Recorremos toda la mano, reseteando palo y rango de cada carta
    }

    //resultados
    gamectx->handResult = -1 ; // -1 = pendiente, 0 = empate, 1 = gana player, 2 = gana dealer
    

    //flags visuales dealer
    gamectx->hideDealerCard = true; ///true es oculta, y 0 no

    gamectx->message[0] = '\0';

}




/*RECORTATORIO PUNTEROS

Se usa "*" en la declaración para indicar que una variable es un puntero.

Al llamar a una función, normalmente se usa "&" para pasar
la dirección de memoria de una variable.

para entrar en una estructura con puntero se usa "->" ,
si tuvieras acceso directo seria "."

*/

