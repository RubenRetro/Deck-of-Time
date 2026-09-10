#ifndef DECK_H
#define DECK_H


#define DECK_SIZE 52
#define MAX_HANDSIZE 12
////////////////////////PALOS//////////////////////////////
typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES      
}Suit;

/*RECORDATORIO: 

-typedef, sirve para crear un nuevo tipo de dato, en este caso Suit, 
que es un enumerado que representa los palos de las cartas.
De esta forma, ya no es necesario escribir "enum Suit" cada vez que se quiera usar este tipo,
sino que se puede simplemente escribir "Suit".


-enum, es un listado de constantes enteras, en este caso HEARTS, DIAMONDS, CLUBS y SPADES,
que representan los palos de las cartas. Cada constante se asigna automáticamente 
a un valor entero, comenzando desde 0 para HEARTS, 1 para DIAMONDS, y así sucesivamente.

ejemplos:
Suit mySuit; 
mySuit = HEARTS; // mySuit tendrá el valor 0

Suit anotherSuit = SPADES; // anotherSuit tendrá el valor 3
*/


///////////////////RANGOS(valor de carta)//////////////////
typedef enum {
ACE = 1,
TWO,
THREE,
FOUR,
FIVE,
SIX,
SEVEN,
EIGHT,
NINE,
TEN,
JACK,
QUEEN,
KING
}Rank;

/*NOTA: En este caso, rank, asignamos manualmente 1 a la primera constante (ACE), 
así forzamos a que las siguientes constantes se asignen automáticamente a los valores 
enteros siguientes (TWO = 2, THREE = 3, etc.).*/


/////////CARTA (combinacion de palo y rango)/////////
typedef struct{
    Suit suit;
    Rank rank;
}Card;

/* RECORDATORIO: struct, es una estructura que agrupa diferentes tipos de datos bajo 
un mismo nombre, (sería como crear una carpeta con diferentes archivos dentro, 
pero en este caso, la carpeta es el struct y los archivos son los campos de la estructura).

EJEMPLO VISUAL:
[Card] (Estructura principal)
  |
  L__ [suit] 
  |
  L__ [rank] 

EJEMPLOS DE USO:
// Creamos las dos cartas del jugador
Card carta1;
Card carta2;

// Le asignamos los valores a la primera carta (un As de Picas)
carta1.suit = SPADES;
carta1.rank = ACE;

// Le asignamos los valores a la segunda carta (un Rey de Corazones)
carta2.suit = HEARTS;
carta2.rank = KING;

// Si quisiéramos mostrar en la pantalla de MS-DOS qué cartas tiene:
textprintf_ex(screen, font, 10, 10, 15, -1, "Carta 1: Palo %d, Rango %d", carta1.suit, carta1.rank);
textprintf_ex(screen, font, 10, 25, 15, -1, "Carta 2: Palo %d, Rango %d", carta2.suit, carta2.rank);

  */

/////FUNCIONES PÚBLICAS /////////////////////////////

//crea una baraja ordenada.
void initDeck(Card deck[DECK_SIZE]); //NOTA, los arrays se pasan como punteros siempre, por eso no es necesario usar *deck, pero se entiende que deck es un puntero.

//mezcla las cartas de la baraja
void shuffleDeck(Card deck[DECK_SIZE]);

//devuelve el valor de una carta, pej: AS vale 11, J,Q, K valen 10, etc.
int getCardValue(Card card);

//roba una carta del mazo
Card drawCard(Card deck[DECK_SIZE], int *deckPosition);
/*NOTA: *deckPosition es un puntero a la posicion actual de la baraja.

PUNTERO: es una variable que almacena la direccion de memoria de otra variable.
Se utiliza para modificar el valor de la variable original desde una función,
sin usar punteros, la función solo modificaría una copia local de la variable, 
y el valor original no cambiaría.
*/

//calcucula el valor total de una mano, considerando el valor de los Ases (1 u 11)
int calculateHandValue(Card hand[MAX_HANDSIZE], int handSize); // hand size no se modifica en al función, no requiere puntero.

#endif