#include "deck.h" // incluye las definiciones (card,suit, etc)
#include <stdlib.h> //para usar la funcion rand

//crea una baraja ordenada.
void initDeck(Card deck[DECK_SIZE]) {
    int index = 0;

    for (int suit = 0; suit < 4; suit++){
            for (int rank = 1; rank <= 13; rank++){
                    deck[index].suit = suit;
                    deck[index].rank = rank;
                    index++;
            }
    }
    
/* EXPLICACIÓN:
   Esta función es llena la caja 'deck' con 52 cartas ordenadas.
   - El bucle 'suit' elige un palo (del 0 al 3).
   - El bucle 'rank' fabrica los números del 1 al 13 para ese palo.
   - 'index' es el contador que avanza del 0 al 51 para colocar cada carta en su carril.
   
   Resultado: Primero fabrica las 13 de Corazones, luego las 13 de Diamantes, etc. */

}


//mezcla las cartas. metodo Fisher-Yates.
void shuffleDeck(Card deck[DECK_SIZE]) {

    for (int i = 51; i > 0; i--) {

        int j = rand() % (i + 1);

        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
/* (Método Fisher-Yates):
   1. Empieza desde el final de la baraja (carta 51) y va retrocediendo hacia la primera.
   2. Elige una carta al azar ('j') pero SOLO entre las que todavía no se han mezclado.
   3. Intercambia esa carta elegida con la carta de la posición actual ('i').
   4. Al avanzar, la carta colocada se "bloquea", asegurando un mezclado 100% perfecto. */

}

//valor de la carta para blackjack
int getCardValue(Card card) {
    if (card.rank >= JACK )
        return 10;  // JQK valen 10
    return card.rank; // si no es JQK, devuelve el valor de la carta

}

//roba una carta (devuelve la carta y avanza posicion del mazo
Card drawCard(Card deck[DECK_SIZE], int *deckPosition) {

    Card c = deck[*deckPosition]; // obtiene la primera carta del mazo

    (*deckPosition)++; //avanza a la siguiente posicion (simula como si se quitara la carta)
    //variable++  , es lo mismo que poner variable = variable +1 o variable += 1
    return c;

}

//calcula el valor total de la mano (valora ases)
int calculateHandValue(Card hand[MAX_HANDSIZE], int handSize) {
    int total = 0;  //acumula valor de la mano
    int aceCount = 0;  //cuenta Ases, para ajustar si vale 11 o 1

    for (int i = 0; i < handSize; i++) {  //recorre todas las cartas de la mano

        total += getCardValue(hand[i]);   //va sumando el valor de cada carta

        if (hand[i].rank == ACE)
            aceCount++;
    }

    if (aceCount > 0 && total +10 <= 21) //si hay ases y se pasa de 21, los asees valen 1, si no, valen 11
        total +=10;  

    return total;

}


//EJEMPLO COMPLETO DE LAS FUNCIONES:

/* Variables para las pruebas
    Card mazo[52];
    int posicionMazo = 0; // Apunta a la parte superior del mazo (carta 0)

    // ==========================================
    // PRUEBA 1: CREAR EL MAZO ORDENADO
    // ==========================================
    initDeck(mazo);

    textprintf_ex(screen, font, 10, 10, 15, -1, "--- PRUEBA 1: MAZO CREADO ---");
    // Mostramos las 3 primeras cartas para comprobar el orden (deberían ser As, 2 y 3 de Corazones)
    textprintf_ex(screen, font, 10, 30, 15, -1, "Carta 0: Palo %d, Rango %d", mazo[0].suit, mazo[0].rank);
    textprintf_ex(screen, font, 10, 45, 15, -1, "Carta 1: Palo %d, Rango %d", mazo[1].suit, mazo[1].rank);
    textprintf_ex(screen, font, 10, 60, 15, -1, "Carta 2: Palo %d, Rango %d", mazo[2].suit, mazo[2].rank);
    
    textprintf_ex(screen, font, 10, 100, 15, -1, "Pulsa una tecla para MEZCLAR...");
    readkey(); // Espera
    clear_to_color(screen, 0); // Limpia pantalla

    // ==========================================
    // PRUEBA 2: MEZCLAR EL MAZO (Fisher-Yates)
    // ==========================================
    shuffleDeck(mazo);

    textprintf_ex(screen, font, 10, 10, 15, -1, "--- PRUEBA 2: MAZO MEZCLADO ---");
    // Volvemos a mirar las 3 primeras posiciones. ¡Ahora deberían ser totalmente aleatorias!
    textprintf_ex(screen, font, 10, 30, 15, -1, "Carta 0: Palo %d, Rango %d", mazo[0].suit, mazo[0].rank);
    textprintf_ex(screen, font, 10, 45, 15, -1, "Carta 1: Palo %d, Rango %d", mazo[1].suit, mazo[1].rank);
    textprintf_ex(screen, font, 10, 60, 15, -1, "Carta 2: Palo %d, Rango %d", mazo[2].suit, mazo[2].rank);
    
    textprintf_ex(screen, font, 10, 100, 15, -1, "Pulsa una tecla para SIMULAR MANO...");
    readkey();
    clear_to_color(screen, 0);

    // ==========================================
    // PRUEBA 3: ROBAR CARTAS Y CALCULAR MANO
    // ==========================================
    Card manoJugador[5]; // Espacio para la mano
    int cartasEnMano = 0;

    // Robamos 2 cartas del mazo usando tu función drawCard
    manoJugador[0] = drawCard(mazo, &posicionMazo);
    cartasEnMano++;
    
    manoJugador[1] = drawCard(mazo, &posicionMazo);
    cartasEnMano++;

    // Calculamos el valor total de la mano con tu función calculateHandValue
    int puntos = calculateHandValue(manoJugador, cartasEnMano);

    textprintf_ex(screen, font, 10, 10, 15, -1, "--- PRUEBA 3: TU MANO DE BLACKJACK ---");
    textprintf_ex(screen, font, 10, 30, 15, -1, "Carta 1 robada: Palo %d, Rango %d", manoJugador[0].suit, manoJugador[0].rank);
    textprintf_ex(screen, font, 10, 45, 15, -1, "Carta 2 robada: Palo %d, Rango %d", manoJugador[1].suit, manoJugador[1].rank);
    
    textprintf_ex(screen, font, 10, 70, 14, -1, "PUNTOS TOTALES: %d", puntos);
    textprintf_ex(screen, font, 10, 90, 15, -1, "Siguiente carta en el mazo es la num: %d", posicionMazo);
    
    textprintf_ex(screen, font, 10, 130, 15, -1, "Prueba terminada. Pulsa ESC para salir.");

    // ==========================================
    // BUCLE DE SALIDA (Para cerrar el juego con ESC)
    // ==========================================
    while (!key[KEY_ESC]) {
        rest(1); // Evita que la CPU se ponga al 100%
    }

    */