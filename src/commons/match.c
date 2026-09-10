#include "gamecontext.h"
#include "graphics.h"
#include "input.h"
#include "tracker.h"
#include "matchmanager.h"
#include "lang.h"
#include "audio.h"
#include "match.h"
#include <stdio.h> // para sprintf
#include <allegro.h>


int dealerPlay(GameContext *gamectx, int playerTotal)
{
    int dealerTotal =
        calculateHandValue(gamectx->dealerHand, gamectx->dealerHandSize);
        /*recorrre la mano mirando cada carta (dealerhand[]) tantas veces como
        cartas hay en mano (deakerHandSize)*/
    gamectx->hideDealerCard = false;
    //cuando juega, deja de esconder la primera carta

    while (dealerTotal < 17) {
        //va robando cartas hasta tener menos de 17

        Card c = drawCard(gamectx->deck, &gamectx->deckPosition);
        /*drawcard(obtiene la siguiente carta de la baraja, avanza la posicion)

          - gamectx->deck es un array. Los arrays se pasan automáticamente
            como un puntero al primer elemento, por eso no hace falta '&'.

            - &gamectx->deckPosition pasa la dirección de la variable
              deckPosition para que drawCard pueda modificar su valor.eccion
          */
    
        gamectx->dealerHand[gamectx->dealerHandSize++] = c;
        /*
        equivale a:
        gamectx->dealerHand[gamectx->dealerHandSize] = c;
        gamectx->dealerHandSize++;


        & solo se usa para pasar pasar la dirección de una variable a otra funcion
        pej draCrard(). pero en este caso se modifica directamente (sin función)
        */

        dealerTotal =
            calculateHandValue(gamectx->dealerHand, gamectx->dealerHandSize);

        
        printGame(gamectx);
        printBasicText(10*TILE, 20*TILE, TXT_DEALERDRAWS, -1, 1, -1);
        if (waitAdvanceButton() == 'X') return -2;
    }

    /* RESULTADO FINAL */

    gamectx->hideDealerCard = false;

    if (dealerTotal > 21) {
       
        printGame(gamectx);
        printBasicText(12*TILE, 20*TILE, TXT_DEALERBUST, -1, 1, -1);
        if (waitAdvanceButton() == 'X') return -2;
        return 1;
    }

    if (dealerTotal > playerTotal) {
       
        return 0;
    }

    if (playerTotal > dealerTotal) {

        return 1;
    }

    // Empate: para esta partida, el jugador pierde la mano y la ronda.
    return 0;


    /*resultados devueltos:

empate = 0  // se trata como derrota del jugador
player gana = 1
dealer gana = 0
salir = -2

*/


}

char npcTalk(GameContext *gamectx, DialogId dialog)
{
    switch(dialog)
    {
       
   

        case DIALOG_INTRO:

            speakText(gamectx, TXT_WELCOME);
            speakText(gamectx, TXT_WELCOME1);
            speakText(gamectx, TXT_WELCOME2);
            speakText(gamectx, TXT_WELCOME3);
         
            return 0;

   

        case DIALOG_HANDRESULT:

           if (gamectx->handResult == 1)
            {
                switch(rand() % 3)
                {
                    case 0:
                        return speakText(gamectx, TXT_HANDWIN);
                    case 1:
                        return speakText(gamectx, TXT_HANDWIN2);
                    case 2:
                        return speakText(gamectx, TXT_HANDWIN3);
                }
               
            }
            else if (gamectx->handResult == 0)
            {
                switch(rand() % 3)
                {
                    case 0:
                        return speakText(gamectx, TXT_HANDLOST);
                    case 1:
                        return speakText(gamectx, TXT_HANDLOST2);
                    case 2:
                        return speakText(gamectx, TXT_HANDLOST3);
                }
            }
            else
            {
                return speakText(gamectx, TXT_HANDDRAW);
            }


   

        case DIALOG_DECISION:

            switch(rand() % 3)
            {
                case 0:
                    return speakText(gamectx, TXT_DARE1);

                case 1:
                    return speakText(gamectx, TXT_DARE2);

                default:
                    return speakText(gamectx, TXT_DARE3);
            }



        case DIALOG_ENDING:

            if (gamectx->playerRoundPoints <=
                gamectx->dealerRoundPoints)
            {
                    speakText(gamectx, TXT_ENDINGLOSE1);
                    speakText(gamectx, TXT_ENDINGLOSE2); 
                    printGrannyEnd(gamectx);
                    Sound_StopMusic();

                    clear_to_color(screen, 1);
                    vsync();
                    
                    spk_on(1000);
                    rest(100);
                    spk_off();


                    printBasicText(0*TILE, 1*TILE, TXT_ENDINGLOSEERROR, 255, 0, -1);
                    getPlayerInputBug();
                    return 0;
            }
            else
            {
                    speakText(gamectx, TXT_ENDINGWIN1);
                    switch (rand() % 3)
                    {
                         case 0:
                            return speakText(gamectx, TXT_ENDINGWINA);
                         case 1:
                            return speakText(gamectx, TXT_ENDINGWINB);
                        case 2:
                            return speakText(gamectx, TXT_ENDINGWINC);
                    }
                    speakText(gamectx, TXT_ENDINGWIN2);
            }

    }

    return '\0';
}

void match(GameContext *gamectx){
    
    Sound_PlayMusic(MUSIC_GAME);
    // resset puntos de rondas
   
    resetMatch(gamectx);//reiniciar partida completa
    resetHand(gamectx);
    
    //PRIMERA ESCENA
    printGame(gamectx); // dibuja frame de juego actual
    fadeFromBlack(1);
    
    if (npcTalk(gamectx, DIALOG_INTRO) == 'X')  { fadeToBlack(4); return; }
    
    //juega 3 rondas ( cada ronda tiene dentro 3 manos)
    for(gamectx->roundNumber = 0; gamectx->roundNumber < 3; gamectx->roundNumber++){
            gamectx->playerScore = 0;
            gamectx->dealerScore = 0;
            gamectx->handNumber = 0;
            
            initDeck(gamectx->deck);
            shuffleDeck(gamectx->deck);
            gamectx->deckPosition = 0; //reiniciamos posicion inical de mazo

          
           
            //construye una cadena de texto "round 1 - new..." y la mete en gamctx->message
            printGame(gamectx); // dibuja frame de juego actual
            Sound_PlaySfx(SFX_SHUFFLE);
            printBasicText(10*TILE, 21*TILE, TXT_SHUFFLE, -1, 1, gamectx->roundNumber+ 1);
         
            
            if (waitAdvanceButton() == 'X') { fadeToBlack(4); return; } // espera espacio o enter
          
            
            //juega 3 manos
            for (gamectx->handNumber = 0; gamectx->handNumber < 3; gamectx->handNumber++) {

                    resetHand(gamectx);
                    int standWarningCount = 0; //variable flag de si te ha incitado a robar más
                    
                        /* NUEVA MANO: solo al comenzar la segunda mano */
                        if (gamectx->handNumber >= 1 && gamectx->handNumber <= 2)
                        {                         
                               printGame(gamectx);
                               printBasicText(14*TILE, 21*TILE, TXT_NEWHAND, -1, 1, -1);
                               if (waitAdvanceButton() == 'X') { fadeToBlack(4); return; }
                         }


                    /* CARTAS INICIALES se roban 2 cada uno*/
                    gamectx->playerHand[gamectx->playerHandSize++] =
                    drawCard(gamectx->deck, &gamectx->deckPosition);
                    gamectx->playerHand[gamectx->playerHandSize++] =
                    drawCard(gamectx->deck, &gamectx->deckPosition);
                    
                    gamectx->dealerHand[gamectx->dealerHandSize++] =
                    drawCard(gamectx->deck, &gamectx->deckPosition);
                    gamectx->dealerHand[gamectx->dealerHandSize++] =
                    drawCard(gamectx->deck, &gamectx->deckPosition);
                    
                    int playing = 1;
                    while (playing){

                                
                                int playerTotal =
                                calculateHandValue(gamectx->playerHand,gamectx->playerHandSize);
                                
                                printGame(gamectx);
                                printBasicText(11*TILE, 20*TILE, TXT_DECISION, -1, 1, playerTotal);
                                
                                printDecision();
                                char choice = getPlayerChoice();
                                if (choice == 'D') {
                                            
                                            //NPCCHAT?

                                            Card c = drawCard(gamectx->deck, &gamectx->deckPosition);
                                            gamectx->playerHand[gamectx->playerHandSize++] = c;
                                            playerTotal = calculateHandValue(gamectx->playerHand, gamectx->playerHandSize);
                                            if (playerTotal > 21) {
                                                        gamectx->handResult = 0;
                                                        printGame(gamectx);
                                                        printBasicText(11*TILE, 20*TILE, TXT_BUST, -1, 1, playerTotal);
                                                        if (waitAdvanceButton() == 'X') { fadeToBlack(4); return; }
                                                        playing = 0;
                                            }

                                }else if (choice == 'S') {
                                                
                                                // si puede apurar algo, incita al player a arriesgarse
                                                if (playerTotal <= 17 && standWarningCount < 2)
                                                {
                                                    standWarningCount++;
                                                    if (npcTalk(gamectx, DIALOG_DECISION) == 'X')
                                                           { fadeToBlack(4); return; }

                                                    continue;   // vuelve a preguntar Draw/Stand
                                                }

                                            
                                            /* 18, 19, 20, 21: se planta directamente */

                                            gamectx->handResult =
                                            dealerPlay(gamectx, playerTotal);
                                            if (gamectx->handResult == -2)
                                                    return;
                                            playing = 0;
                                }
                                //exit
                                else if (choice == 'X') {
                                
                                            { fadeToBlack(4); return; }
                                }
                                         
                                
                    }

                    

                   // resultado de mano
if (gamectx->handResult == 1) {
    gamectx->playerScore++;
}
else {
    // empate o derrota: el jugador no suma la mano y la mano cuenta para el dealer
    gamectx->dealerScore++;
}


                    
                    if (npcTalk(gamectx, DIALOG_HANDRESULT) == 'X')
                                                           { fadeToBlack(4); return; }
               
            }

            //resultado de la ronda
           
            if (gamectx->playerScore > gamectx->dealerScore) {
                        gamectx->playerRoundPoints++;
                  
            } else {
                        // empate o derrota: el jugador no gana la ronda,
                        // y el dealer debe llevar la cuenta de la ronda.
                        gamectx->dealerRoundPoints++;
            }
           
            
            
            //resultado primera ronda

            printGame(gamectx);
            printBasicText(6*TILE, 20*TILE, TXT_ROUNDRESULT, -1, 1, -1);
            printBasicText(10*TILE, 21*TILE, TXT_ROUNDRESULT1, -1, 1, gamectx->playerRoundPoints);
            printBasicText(10*TILE, 22*TILE, TXT_ROUNDRESULT2, -1, 1, gamectx->dealerRoundPoints);

            if (waitAdvanceButton() == 'X') { fadeToBlack(4); return; }
            
    }

    // resltado final de la partida

if (npcTalk(gamectx, DIALOG_ENDING) == 'X')  { fadeToBlack(4); return; }

    



fadeToBlack(1); 
   
}
