        #include "graphics.h"
        #include "lang.h"
        #include "gamecontext.h"
        #include "audio.h"
        #include "input.h"
        #include <allegro.h>
        #include <string.h>
        #include <stdio.h>
        #include "systemCheck.h" //para la global de lowEndSystem
        #include <math.h>// para usar funcion sinus

      
        
        //SPRITES


        /* 
        background es un puntero a una imagen (BITMAP).
        Más adelante load_bitmap() devolverá la dirección de memoria de una
        imagen cargada, y esa dirección se guardará en background.

        Se inicializa a NULL para indicar que todavía no apunta a ninguna
        imagen válida y evitar que contenga una dirección indeterminada.

        El modificador static hace que esta variable sea privada de
        graphics.c. Ningún otro módulo puede acceder a ella directamente.

        BITMAP es un tipo definido por la librería Allegro para representar
        imágenes en memoria.
        */
        static BITMAP *buffer = NULL;

        static BITMAP *background = NULL;
        // HUD spritesheets and cut pieces
        static BITMAP *hudSheet = NULL;
        static BITMAP *hudManos = NULL;
        static BITMAP *hudHandsEnglish = NULL;
        static BITMAP *hudRondas = NULL;
        static BITMAP *hudRoundsEnglish = NULL;
        static BITMAP *hudDe = NULL;
        static BITMAP *hudSlash = NULL;
        static BITMAP *hudNumbers[4] = {NULL, NULL, NULL, NULL};
        static BITMAP *hudBubble = NULL;
        static BITMAP *hudDecision[4] = {NULL, NULL, NULL, NULL};

        //PNJ
        static BITMAP *pnjSprites[2] = {NULL, NULL};
        static BITMAP *pnjGrannyMouth[2] = {NULL, NULL};
        static BITMAP *pnjGirlMouth[2] = {NULL, NULL};
        static BITMAP *pnjGrannyEnd = NULL;

        static BITMAP *logorr = NULL;
        static BITMAP *dosconLogo = NULL;

        static BITMAP *testScreen = NULL;
        static BITMAP *titleScreen = NULL;

        static BITMAP *titleUISheet = NULL;
        static BITMAP *titleLabels[2] = {NULL, NULL};
        static BITMAP *titleHotkeys[7] = {NULL, NULL, NULL, NULL, NULL, NULL};

        static BITMAP *cardBack = NULL;
        static BITMAP *cardSpriteSheet = NULL;
        static BITMAP *cardSprites[DECK_SIZE];
        static FONT *hudFont = NULL;
        static FONT *hudFont2 = NULL;
        static PALETTE gamePalette;
        /*PALETTE es un tipo definido por allegro, es un array
        de 256 colores. mete en cada posición el color
        que pasamos: gamepalette[o]=negro, gamepalette[1]= azul.. etc*/

        //capacidad máxima de texto
        #define MAX_VISIBLE_TEXT 128
        //maximo de texto por línea
        #define MAX_LINE_CHARS 38

        //medidas de carta para recortar spritesheet
        #define CARD_SHEET_W 34
        #define CARD_SHEET_H 33


        //CARD a SPRITE INDEX

        static int getCardId(Card card){
            
            return (card.suit*13)+(card.rank -1 );

            /*
            convierte Carta card en un numero del 0 al 51.
            Se usa para organizar el array *cardSprites[DECK_SIZE]

            EJEMPLO:
            "AS de corazones", card.suit= 0, card.rank=1
            (0x13) + (1-1)=0
            cardsprites[0]

            "rey de diamantes", card.suit=1, card.rank=13
            (1x13) + (13 -1 ) = 25
            carsprites[25]

            */
        }

        //INICIAR GRAFICOS
        void initGraphics(){

            int i;
            int col, row;
            BITMAP *paletteBitmap = NULL;    

            /* Inicializar modo gráfico */

            set_color_depth(8);

            if (set_gfx_mode(
                    GFX_AUTODETECT,
                    320,
                    200,
                    0,
                    0) != 0)
            {
                allegro_message("Error gfx mode");
                exit(EXIT_FAILURE);
            }

            /*----------------------------------
            CARGA DE RECURSOS
            ----------------------------------*/


            //carga la paleta de palette.pcx
            paletteBitmap = load_bitmap ("assets/backg/palette.pcx", gamePalette);
            /*el segundo parametro de load_bitmap sirve para recubir paleta,
            en el resto de casos ponemos NULL*/

            /*load_bitmap esta pensando para cargar siempre una imagen, 
            por eso hay que meterla en paletteBitmap y luego destruirla 
            porque ya no tiene más utilidad.*/

            if (paletteBitmap){
                destroy_bitmap(paletteBitmap);
                paletteBitmap = NULL;
                /* la destruye, solo quería obtener la paleta*/
            }
            
            /* Cambiar el color 0 a negro, para que no se vea en cian el "marco" del juego*/
            gamePalette[0].r = 0;
            gamePalette[0].g = 0;
            gamePalette[0].b = 0;

            /*
            ALTERNATIVA O IDEA PARA USAR EN JUEGO COMO EFECTOS

            #include <pc.h>   // DJGPP: para inportb / outportb

            //pone el color del borde/overscan de la VGA (registro aparte de la paleta de 256)
            
            static void setBorderColor(int color)
            {
                inportb(0x3DA);         // resetea el flip-flop del Attribute Controller
                outportb(0x3C0, 0x11);  // seleccionamos el registro de overscan (indice 0x11)
                outportb(0x3C0, color); // escribimos el color que queremos
                outportb(0x3C0, 0x20);  // reactivamos la salida normal de vídeo
            }
            
            ejemplo de uso(solo para graphics.c):

            set_palette(gamePalette);
            clear_to_color(screen, 1);
            setBorderColor(1); // 1 = negro en tu paleta

            */
            
            //aplicamos la paleta goblalmente
            set_palette(gamePalette);
            clear_to_color(screen, 1);
        
        
            select_palette(gamePalette);
            /*Ambas, funciones de allegro.
            set_palette: carga la paleta en la tarjeta grafica. IMPORTANTE
            select_palette: indica a allegro que use esa paleta para sus operaciones internas.*/

            
            

            buffer = create_bitmap(320, 200);
            clear_to_color(buffer, 1);
        
            //carga el fondo
            background = load_bitmap("assets/backg/backg.pcx",NULL);

            logorr = load_bitmap("assets/menus/logorr.pcx",NULL);
            dosconLogo = load_bitmap("assets/menus/doscon.pcx",NULL);

            testScreen = load_bitmap("assets/backg/test.pcx",NULL);

            titleScreen = load_bitmap("assets/backg/title.pcx",NULL);

            titleUISheet = load_bitmap("assets/hud/mlabels.pcx",NULL);  
            if (titleUISheet){
                    titleLabels[0] = create_bitmap(96, 120); //labels grandes del menu principal
                    titleLabels[1] = create_bitmap(96, 120); // en ingles
                    
                     if (titleLabels[0])  
                        blit(titleUISheet,   //blit(fuente, destino, fuente_x, fuente_y, destino_x,destino_y, ancho del rectangulo a copiar, alto)
                             titleLabels[0],
                             0, 0,
                             0, 0,
                             96, 120);

                     if (titleLabels[1])
                         blit(titleUISheet,
                              titleLabels[1],
                              96, 0,
                              0, 0,
                              96, 120);
                    
                    for (i = 0; i < 7; i++) {
                            titleHotkeys[i] = create_bitmap(16, 16);
                            if (titleHotkeys[i]) {
                                blit(titleUISheet, titleHotkeys[i], i * 16, 120, 0, 0, 16, 16);
                            
                            
                            }                 
                     }
            destroy_bitmap(titleUISheet);
            titleUISheet = NULL;
            }

            hudSheet = load_bitmap("assets/hud/hud.pcx", NULL);
            if (hudSheet) {
                hudManos = create_bitmap(32, 8);
                hudHandsEnglish = create_bitmap(32, 8);
                hudRondas = create_bitmap(40, 8);
                hudRoundsEnglish = create_bitmap(40, 8);
                hudDe = create_bitmap(16, 8);
                hudSlash = create_bitmap(8, 8);
                hudBubble = create_bitmap(16, 8);

                if (hudManos) blit(hudSheet, hudManos, 0, 0, 0, 0, 32, 8);
                if (hudHandsEnglish) blit(hudSheet, hudHandsEnglish, 0, 8, 0, 0, 32, 8);
                if (hudRondas) blit(hudSheet, hudRondas, 0, 16, 0, 0, 40, 8);
                if (hudRoundsEnglish) blit(hudSheet, hudRoundsEnglish, 0, 24, 0, 0, 40, 8);
                if (hudDe) blit(hudSheet, hudDe, 0, 32, 0, 0, 16, 8);
                if (hudSlash) blit(hudSheet, hudSlash, 16, 32, 0, 0, 8, 8);
                if (hudBubble) blit(hudSheet, hudBubble, 32, 40, 0, 0, 16, 8);

                for (i = 0; i < 4; i++) {
                    hudNumbers[i] = create_bitmap(8, 8);
                    if (hudNumbers[i]) {
                        blit(hudSheet, hudNumbers[i], i * 8, 40, 0, 0, 8, 8);
                    }
                    hudDecision[i] = create_bitmap(80, 8);
                    if (hudDecision[i]) {
                        blit(hudSheet, hudDecision[i], 48, i * 8, 0, 0, 80, 8);
                    }
                }

                destroy_bitmap(hudSheet);
                hudSheet = NULL;
            }

            //carga PNJ
            pnjSprites[0] = load_bitmap("assets/pnj/granny.pcx", NULL);
            if (pnjSprites[0])
                {
                    pnjGrannyMouth[0] = create_bitmap(32,32);
                    pnjGrannyMouth[1] = create_bitmap(32,32);

                     if (pnjGrannyMouth[0])
                            blit(pnjSprites[0], pnjGrannyMouth[0],
                                   160,0,
                                   0,0,
                                   32,32);

                     if (pnjGrannyMouth[1])
                             blit(pnjSprites[0], pnjGrannyMouth[1],
                                    160,32,
                                    0,0,
                                    32,32);
                }

            pnjGrannyEnd = load_bitmap("assets/pnj/granny2.pcx", NULL);
            
            pnjSprites[1] = load_bitmap("assets/pnj/girl.pcx", NULL);
            if (pnjSprites[1])
                {
                     pnjGirlMouth[0] = create_bitmap(16,16);
                     pnjGirlMouth[1] = create_bitmap(16,16);

                     if (pnjGirlMouth[0])
                         blit(pnjSprites[1], pnjGirlMouth[0],
                                  160,0,
                                  0,0,
                                  16,16);

                    if (pnjGirlMouth[1])
                         blit(pnjSprites[1], pnjGirlMouth[1],
                                 160,16,
                                 0,0,
                                  16,16);
                }
        



            //CARTA SPRITESHEET DE CARTAS
            cardSpriteSheet = load_bitmap("assets/cards/cardshee.pcx", NULL);
            if (!cardSpriteSheet){
                    destroy_bitmap(cardBack);
                    cardBack = NULL;
                    return;
                    /*ERROR CRITICO, si no hay spritesheet, destruye la cadBack(estaba creada)
                    no destruimos el fondo, porque no era critico, y podria no haberse cargado*/
            }

            //inicializar la matriz de cartasrecortadas a NULL
            for (i = 0; i < DECK_SIZE; i++){
                    cardSprites[i] = NULL;
            }
            
            //EXTRACCION DE CARTAS A APRTIR DE SPRITESHEET(13X4)
            for (i = 0; i<DECK_SIZE; i++){

                col = i % 13; //columnas en el spritesheet
                row = i/ 13; // filas en el spritesheet

                int x = col * CARD_SHEET_W;
                int y = row * CARD_SHEET_H;

                //CREAMOS LOS BITMAPS DE LAS DIFERENTES CARTAS
                cardSprites[i] = create_bitmap(CARD_SHEET_W,CARD_SHEET_H);
                if (cardSprites[i]){

                        //copiamos la region del sprite sheet a carta bitmap
                        blit(
                            cardSpriteSheet, //fuente
                            cardSprites[i],  //destino
                            x,y,             //donde empieza el recorte
                            0,0,            //donde se pega
                            CARD_SHEET_W,CARD_SHEET_H // medidas del trazo
                        );
                        /*con BLIT, copiamos una parte de una imagen y la pegamos en otra.
                        coge el rectangulo de spritesheet y lo guarda como imagenes independientes*/
                }
            }
            //CARTA TRASERA
            cardBack = create_bitmap(CARD_SHEET_W, CARD_SHEET_H);

            if (cardBack){
                        blit(
                             cardSpriteSheet,
                             cardBack,
                             13 * CARD_SHEET_W,   // columna nueva a la derecha
                             0,
                             0,
                             0,
                             CARD_SHEET_W,
                             CARD_SHEET_H
                         );
            }   
            

            //destruimos el spritesheet, ya no es necesario
            if (cardSpriteSheet){

                    destroy_bitmap(cardSpriteSheet);
                    cardSpriteSheet = NULL;

            }

            //cargamos la fuente personalizada para el juego
            hudFont = load_font("assets/font/hudfont.pcx",NULL, NULL); 
            hudFont2 = load_font("assets/font/hudfont2.pcx",NULL, NULL); 
            //los dos NULL, son parametro especial, parametro extra

        }


        ///destruir graficos
void destroyGraphics()
{

            int i;

            for (i=0; i < DECK_SIZE; i++){

                    if (cardSprites[i] != NULL){
                        destroy_bitmap(cardSprites[i]);
                        cardSprites[i] = NULL;
                    }

                            /* 
                igualar a = NULL tras destruir. 
                La razón principal es evitar los llamados punteros colgantes (dangling pointers).
                Allegro libera la memoria donde estaba almacenada la imagen. 
                Pero la variable paletteBitmap sigue conteniendo la dirección antigua.*/

            }

            if (background != NULL){
                    destroy_bitmap(background);
                    background = NULL;
            }

            if (logorr != NULL){
                    destroy_bitmap(logorr);
                    logorr = NULL;
            }

            if (dosconLogo != NULL){
                    destroy_bitmap(dosconLogo);
                    dosconLogo = NULL;
            }

            if (titleScreen != NULL){
                    destroy_bitmap(titleScreen );
                    titleScreen  = NULL;
            }


            if (testScreen != NULL){
                    destroy_bitmap(testScreen);
                    testScreen = NULL;
            } 


            if (cardBack != NULL){
                    destroy_bitmap(cardBack);
                    cardBack = NULL;
            }

            if (cardSpriteSheet != NULL){
                    destroy_bitmap(cardSpriteSheet);
                    cardSpriteSheet = NULL;
            }

            if (hudFont != NULL ){
                    destroy_font(hudFont);
                    hudFont = NULL;
            }

            if (hudFont2 != NULL ){
                    destroy_font(hudFont2);
                    hudFont2 = NULL;
            }

            if (hudManos != NULL) {
                destroy_bitmap(hudManos);
                hudManos = NULL;
            }
            if (hudHandsEnglish != NULL) {
                destroy_bitmap(hudHandsEnglish);
                hudHandsEnglish = NULL;
            }
            if (hudRondas != NULL) {
                destroy_bitmap(hudRondas);
                hudRondas = NULL;
            }
            if (hudRoundsEnglish != NULL) {
                destroy_bitmap(hudRoundsEnglish);
                hudRoundsEnglish = NULL;
            }
            if (hudDe != NULL) {
                destroy_bitmap(hudDe);
                hudDe = NULL;
            }
            if (hudSlash != NULL) {
                destroy_bitmap(hudSlash);
                hudSlash = NULL;
            }
            if (hudBubble != NULL) {
                destroy_bitmap(hudBubble);
                hudBubble = NULL;
            }
            
            if (titleUISheet != NULL) {
                destroy_bitmap(titleUISheet);
                titleUISheet = NULL;
            }

            for (i = 0; i < 2; i++) {
                if (titleLabels[i] != NULL) {
                      destroy_bitmap(titleLabels[i]);
                      titleLabels[i] = NULL;
                 }
            }

            for (i = 0; i < 7; i++) {
                if (titleHotkeys[i] != NULL) {
                     destroy_bitmap(titleHotkeys[i]);
                     titleHotkeys[i] = NULL;
                    }
            }
            
            for (i = 0; i < 4; i++) {
                if (hudNumbers[i] != NULL) {
                    destroy_bitmap(hudNumbers[i]);
                    hudNumbers[i] = NULL;
                }
                if (hudDecision[i] != NULL) {
                    destroy_bitmap(hudDecision[i]);
                    hudDecision[i] = NULL;
                }
            }

        for (i = 0; i < 2; i++){

            if (pnjSprites[i]){
                destroy_bitmap(pnjSprites[i]);
                pnjSprites[i] = NULL;
            }

            if (pnjGrannyMouth[i]) {
                    destroy_bitmap(pnjGrannyMouth[i]);
                    pnjGrannyMouth[i] = NULL;
            }

            if (pnjGirlMouth[i]) {
                    destroy_bitmap(pnjGirlMouth[i]);
                    pnjGirlMouth[i] = NULL;
            }
            
        }
        if (pnjGrannyEnd != NULL) {
                destroy_bitmap(pnjGrannyEnd);
                pnjGrannyEnd = NULL;
        }
        

}



        //dibujar HUD
void printHUD(GameContext *gamectx)
{
    int x = 248;
    int y = 16;

    BITMAP *handsBmp;
    BITMAP *roundsBmp;
    BITMAP *separatorBmp;

    int separatorWidth;
    int separatorX;

   
      //Seleccionar sprites según idioma
  

    if (currentLanguage == LANG_ES)
    {
        handsBmp      = hudManos;
        roundsBmp     = hudRondas;
        separatorBmp  = hudDe;
        separatorWidth = 16;
        separatorX     = x + 8;
    }
    else
    {
        handsBmp      = hudHandsEnglish;
        roundsBmp     = hudRoundsEnglish;
        separatorBmp  = hudSlash;
        separatorWidth = 8;
        separatorX     = x + 10;   /* 8  +2 para centrar el slash */
    }

   
      //Valores
   

    int handsWon = gamectx->playerScore;
    if (handsWon < 0) handsWon = 0;
    if (handsWon > HANDS_PER_ROUND) handsWon = HANDS_PER_ROUND;

    int handsPlayed = gamectx->playerScore + gamectx->dealerScore;
    if (handsPlayed < 0) handsPlayed = 0;
    if (handsPlayed > HANDS_PER_ROUND) handsPlayed = HANDS_PER_ROUND;

    int currentHand = handsPlayed;
    if (currentHand < 0) currentHand = 0;
    if (currentHand > HANDS_PER_ROUND) currentHand = HANDS_PER_ROUND;

    int roundPoints = gamectx->playerRoundPoints;
    if (roundPoints < 0) roundPoints = 0;
    if (roundPoints > 3) roundPoints = 3;

    int roundsPlayed = gamectx->playerRoundPoints + gamectx->dealerRoundPoints;
    if (roundsPlayed < 0) roundsPlayed = 0;
    if (roundsPlayed > 3) roundsPlayed = 3;

    int currentRound = roundsPlayed;
    if (currentRound < 0) currentRound = 0;
    if (currentRound > 3) currentRound = 3;

  
      //Etiquetas
  

    if (handsBmp)
    {
        masked_blit(
            handsBmp,
            buffer,
            0, 0,
            x, y,
            32, 8);
    }

    if (roundsBmp)
    {
        masked_blit(
            roundsBmp,
            buffer,
            0, 0,
            x - 8, y + 16,
            40, 8);
    }

    if (separatorBmp)
    {
        masked_blit(
            separatorBmp,
            buffer,
            0, 0,
            separatorX, y + 8,
            separatorWidth, 8);

        masked_blit(
            separatorBmp,
            buffer,
            0, 0,
            separatorX, y + 24,
            separatorWidth, 8);
    }


      //Números
  

    if (hudNumbers[handsWon])
    {
        masked_blit(
            hudNumbers[handsWon],
            buffer,
            0, 0,
            x, y + 8,
            8, 8);
    }

    if (hudNumbers[currentHand])
    {
        masked_blit(
            hudNumbers[currentHand],
            buffer,
            0, 0,
            x + 24, y + 8,
            8, 8);
    }

    if (hudNumbers[roundPoints])
    {
        masked_blit(
            hudNumbers[roundPoints],
            buffer,
            0, 0,
            x, y + 24,
            8, 8);
    }

    if (hudNumbers[currentRound])
    {
        masked_blit(
            hudNumbers[currentRound],
            buffer,
            0, 0,
            x + 24, y + 24,
            8, 8);
    }
}

        //DIBUJAR Pnj

void printPNJ(GameContext *gamectx)
{
    int x = 11 * TILE;
    int y = 0 * TILE;
    int currentPnj;

    if (gamectx->playerRoundPoints > gamectx->dealerRoundPoints)
        currentPnj = 1;      // chica
    else
        currentPnj = 0;      // VIEJA

    /* Cuerpo */
    masked_blit(
        pnjSprites[currentPnj],
        buffer,
        0, 0,
        x, y,
        160, 96
    );

    /* Boca */
    if (gamectx->mouthFrame == 1)
    {
        if (currentPnj == 0)
        {
            masked_blit(
                pnjGrannyMouth[0],
                buffer,
                0, 0,
                19 * TILE,
                4 * TILE,
                32, 32
            );
        }
        else
        {
            masked_blit(
                pnjGirlMouth[0],
                buffer,
                0, 0,
                19 * TILE,
                4 * TILE,
                16, 16
            );
        }
    }
    else if (gamectx->mouthFrame == 2)
    {
        if (currentPnj == 0)
        {
            masked_blit(
                pnjGrannyMouth[1],
                buffer,
                0, 0,
                19 * TILE,
                4 * TILE,
                32, 32
            );
        }
        else
        {
            masked_blit(
                pnjGirlMouth[1],
                buffer,
                0, 0,
                19 * TILE,
                4 * TILE,
                16, 16
            );
        }
    }
}

        //DIBUJAR CARTAS

void printCards(GameContext *gamectx)
{

            int i;

            if(!cardBack)
                return;
            
            //player cards

            for (i = 0; i < gamectx->playerHandSize; i++){
                    int cardId = getCardId(gamectx->playerHand[i]);

                    if (cardId < 0 || cardId >= DECK_SIZE)
                        continue;

                    if (!cardSprites[cardId])
                        continue;

                    int x = (PLAYER_INITIAL_X + i*CARD_X_STEP) *TILE;
                    int y = (PLAYER_INITIAL_Y * TILE)+4;// el 4 es un ajuste de últma hora para que encaje

                    masked_blit(
                        cardSprites[cardId],
                        buffer ,
                        0,0,
                        x,y,
                        CARD_W,CARD_W
                    );
            }
            //DEALER CARDS
            for (i = 0; i < gamectx->dealerHandSize; i++){
                    int dealerX = (DEALER_INITIAL_X + i*CARD_X_STEP) * TILE;
                    int dealerY = (DEALER_INITIAL_Y * TILE)+4;

                    if (gamectx->hideDealerCard && i == 1) {
                            masked_blit(
                                cardBack,
                                buffer,
                                0,0,
                                dealerX, dealerY,
                                CARD_W, CARD_H
                            );
                    
                    }else {

                            int cardId = getCardId(gamectx->dealerHand[i]);

                            if (cardId < 0 || cardId >= DECK_SIZE)
                                continue;
                            if (!cardSprites[cardId])
                                continue;
                            
                            masked_blit(
                                cardSprites[cardId],
                                buffer,
                                0,0,
                                dealerX, dealerY,
                                CARD_W,CARD_H
                            );
                    }
            }
}


       

void printChat(GameContext *gamectx)
{

            int x = HUD_INITIAL_X * TILE;
            int y = HUD_INITIAL_Y * TILE;

            FONT *fontToUse = hudFont ? hudFont : font;

            rectfill(
                buffer,
                x,
                y,
                x + HUD_W * TILE,
                y + HUD_H * TILE,
                1 //indice 1 que es negro en mi paleta
            );


            char texto[sizeof(gamectx->message)];
        char *linea;
        int yy;

        strncpy(
            texto,
            gamectx->message,
            sizeof(texto) - 1
        );

        texto[sizeof(texto) - 1] = '\0';

        linea = strtok(texto, "\n");

        yy = y + 12;

        while(linea)
        {
            textout_ex(
                buffer,
                fontToUse,
                linea,
                x,
                yy,
                -1,
                -1
            );

            yy += 8;

            linea = strtok(NULL, "\n");
        }


}

void printBubble()
{
            if (hudBubble ) {
                masked_blit(hudBubble , screen, 0, 0, 36*TILE, 181, 16, 8);
            }
            
}

void printDecision(void)
{
        int first;

        if (currentLanguage == LANG_ES)
            first = 0;
        else
            first = 2;

        masked_blit(hudDecision[first], screen,
                    0, 0,
                    10, 180,
                    80, 8);

        masked_blit(hudDecision[first + 1], screen,
                    0, 0,
                    230, 180,
                    80, 8);
}
void timeTravelTransition(BITMAP *oldScreen, BITMAP *newScreen)
{
            int i;

            for (i = 0; i < 80; i++)
            {
                int y;
                int amplitude;
                BITMAP *source;

                clear_to_color(buffer, 1);

                if (i < 40)
                {
                    source = oldScreen;
                    amplitude = i;
                }
                else
                {
                    source = newScreen;
                    amplitude = 80 - i;
                }

                for (y = 0; y < 200; y++)
                {
                    int offset = (int)(
                        sin((y + i) * 0.12) * amplitude
                    );

                    blit(
                        source,
                        buffer,
                        0, y,
                        offset, y,
                        320, 1
                    );
                }

                vsync();
                blit(buffer, screen, 0, 0, 0, 0, 320, 200);

                rest(5);
            }
}





void timeTravelIfNeeded(GameContext *gamectx)
{
            static int previousPnjState = -1;

            int currentState;

            currentState =
                (gamectx->playerRoundPoints >
                gamectx->dealerRoundPoints);

            if (previousPnjState == -1)
            {
                previousPnjState = currentState;
                return;
            }

            if (currentState != previousPnjState)
            {
                BITMAP *oldScreen;
                BITMAP *newScreen;

                oldScreen = create_bitmap(320,200);
                newScreen = create_bitmap(320,200);

                blit(screen, oldScreen,
                    0,0,0,0,
                    320,200);

                blit(buffer, newScreen,
                    0,0,0,0,
                    320,200);

                timeTravelTransition(
                    oldScreen,
                    newScreen
                );

                destroy_bitmap(oldScreen);
                destroy_bitmap(newScreen);

                previousPnjState = currentState;
            }
}


void printLogorr()
{
    clear_to_color(buffer, 1);
                masked_blit(
                        logorr,
                        buffer,
                        0,0,
                        96,32,
                        128,128);

                vsync();
                blit(buffer, screen, 0, 0, 0, 0, 320, 200);
}

void printdosconLogo()
{
    clear_to_color(buffer, 1);
                masked_blit(
                        dosconLogo,
                        buffer,
                        0,0,
                        0,0,
                        320,200);

                vsync();
                blit(buffer, screen, 0, 0, 0, 0, 320, 200);
}

void printTitle(void){
                masked_blit(
                        titleScreen, buffer,0,0,0,0,320,200);

                /* Label según idioma */
                if (currentLanguage == LANG_ES) {
                        masked_blit(    titleLabels[0],buffer,0, 0, 14*TILE, 10*TILE,/* posición en pantalla */ 96, 120);
                }
                else
                {
                        masked_blit(titleLabels[1], buffer,0, 0,14*TILE, 10*TILE,96, 120);
                }
                
                vsync();
                blit(buffer, screen, 0, 0, 0, 0, 320, 200);
}
            
void printTitleHotkey(char key, int x, int y)
{
    int sprite = -1;

    switch (key)
    {
        case 'J': sprite = 0; break;
        case 'I': sprite = 1; break;
        case 'C': sprite = 2; break;
        case 'S': sprite = 3; break;
        case 'P': sprite = 4; break;
        case 'E': sprite = 5; break;
        case 'L': sprite = 6; break;
        default: return;
    }

    masked_blit(
        titleHotkeys[sprite],
        buffer,
        0, 0,
        x, y,
        16, 16
    );

    vsync();
    blit(buffer, screen, 0, 0, 0, 0, 320, 200);
}    
void printTest(void)
  {
                masked_blit(
                        testScreen, buffer,0,0,0,0,320,200);

                vsync();
                blit(buffer, screen, 0, 0, 0, 0, 320, 200);

}

        

void printGame(GameContext *gamectx){


            if (background){
                    masked_blit(background,buffer,0,0,0,0,320,200);
            }else{

                    clear_to_color(buffer, 1);

            }
            printPNJ(gamectx);
            printHUD(gamectx);
            printCards(gamectx);
            printChat(gamectx);

        timeTravelIfNeeded(gamectx);


            vsync();
            blit(buffer, screen, 0,0,0,0,320,200);
}




void fadeToBlack(int speed)
{
            //speed son los pasos por frame, cuanto más alto más rápido
            fade_out(speed);
}

void fadeFromBlack(int speed)
{
            fade_in(gamePalette, speed);
}


        #define CREDIT_SPACING 12

void printCredits(const char *credits[], int x, int offsetY)
{
            int i;
            int y = offsetY;

            /* Dibujar fondo */
            if (titleScreen )
            {
                masked_blit(
                    titleScreen ,
                    buffer,
                    0,0,
                    0,0,
                    320,200);
            }
            else
            {
                clear_to_color(buffer,1);
            }

            /* Dibujar todas las líneas */
            for (i = 0; credits[i] != NULL; i++)
            {
                if (y > -8 && y < 200)
                {
                    textout_centre_ex(
                        buffer,
                        hudFont ? hudFont : font,
                        credits[i],
                        x,
                        y,
                        -1,
                        -1);
                }

                y += CREDIT_SPACING;
            }

            vsync();

            blit(
                buffer,
                screen,
                0,0,
                0,0,
                320,200);
}

static void playRandomTalk(GameContext *gamectx)
{
    int currentPnj;

    if (gamectx->playerRoundPoints > gamectx->dealerRoundPoints)
        currentPnj = 1;      /* chica */
    else
        currentPnj = 0;      /* vieja */


    if (currentPnj == 1)
    {
        /* CHICA */

        switch(rand() % 3)
        {
            case 0:
                Sound_PlaySfx(SFX_GIRL1);
                break;

            case 1:
                Sound_PlaySfx(SFX_GIRL2);
                break;

            default:
                Sound_PlaySfx(SFX_GIRL3);
                break;
        }
    }
    else
    {
        /* vieja*/

        switch(rand() % 3)
        {
            case 0:
                Sound_PlaySfx(SFX_OLDI1);
                break;

            case 1:
                Sound_PlaySfx(SFX_OLDI2);
                break;

            default:
                Sound_PlaySfx(SFX_OLDI3);
                break;
        }
    }
}

#define MOUTH_SPEED 2

static int utf8_seqlen(unsigned char c)
{
    if ((c & 0x80) == 0x00) return 1; /* ASCII normal */
    if ((c & 0xE0) == 0xC0) return 2; /* 2 bytes: la mayoría de acentos/ñ */
    if ((c & 0xF0) == 0xE0) return 3; /* 3 bytes */
    if ((c & 0xF8) == 0xF0) return 4; /* 4 bytes */
    return 1; /* byte inválido/suelto: tratar como 1 para no colgarse */
}

/* 
   Construye el texto completo con word wrap aplicado,
   respetando caracteres UTF-8, sin animar nada.
   */
static void buildWrappedText(const char *texto, char *out, int outSize)
{
    int len = strlen(texto);
    int lineChars = 0;
    int i = 0;
    int outPos = 0;

    while (i < len && outPos < outSize - 1)
    {
        unsigned char c = (unsigned char)texto[i];
        int seqlen = utf8_seqlen(c);
        if (i + seqlen > len) seqlen = 1;

        if (c == ' ')
        {
            int j = i + 1;
            int nextWordLen = 0;

            while (texto[j] &&
                   texto[j] != ' ' &&
                   texto[j] != '\n')
            {
                nextWordLen++;
                j++;
            }

            if (lineChars + nextWordLen >= MAX_LINE_CHARS)
            {
                out[outPos++] = '\n';
                lineChars = 0;
            }
            else
            {
                out[outPos++] = ' ';
                lineChars++;
            }

            i++;
        }
        else if (c == '\n')
        {
            out[outPos++] = '\n';
            lineChars = 0;
            i++;
        }
        else
        {
            int k;
            for (k = 0; k < seqlen && outPos < outSize - 1; k++)
            {
                out[outPos++] = texto[i + k];
            }
            lineChars++;
            i += seqlen;
        }
    }

    out[outPos] = '\0';
}

char speakText(GameContext *gamectx, const char *texto)
{
    /* 
       VERSIÓN REDUCIDA: sistemas inferiores a 486
       Muestra el texto final directamente, sin animación
    */
    if (g_isLowEndSystem)
    {
        char visible[MAX_VISIBLE_TEXT];

        buildWrappedText(texto, visible, sizeof(visible));

        strncpy(
            gamectx->message,
            visible,
            sizeof(gamectx->message) - 1
        );
        gamectx->message[sizeof(gamectx->message) - 1] = '\0';

        gamectx->mouthFrame = 0;
        gamectx->mouthTimer = 0;

        printGame(gamectx);
        printBubble();

        if (texto == TXT_WELCOME3 || texto == TXT_ENDINGLOSE2)
        {
            Sound_PlaySfx(SFX_OLDLAUGHT);
        }

        if (waitAdvanceButton() == 'X') return 'X';

        gamectx->message[0] = '\0';
        printGame(gamectx);

        return '\0';
    }

    /* 
       VERSIÓN COMPLETA: 486 en adelante
       Texto letra a letra, con boca animada y sonido
    */
    char visible[MAX_VISIBLE_TEXT];

    int len;
    int lineChars;
    int i;
    int visPos;

    visible[0] = '\0';

    len = strlen(texto);
    lineChars = 0;
    i = 0;
    visPos = 0;

    while (i < len)
    {
        unsigned char c = (unsigned char)texto[i];
        int seqlen = utf8_seqlen(c);

        if (i + seqlen > len) seqlen = 1;

        /* 
        WORD WRAP AUTOMÁTICO
        */

        if (c == ' ')
        {
            int j = i + 1;
            int nextWordLen = 0;

            while (texto[j] &&
                   texto[j] != ' ' &&
                   texto[j] != '\n')
            {
                nextWordLen++;
                j++;
            }

            if (lineChars + nextWordLen >= MAX_LINE_CHARS)
            {
                visible[visPos++] = '\n';
                lineChars = 0;
            }
            else
            {
                visible[visPos++] = ' ';
                lineChars++;
            }

            i++;
        }
        else if (c == '\n')
        {
            visible[visPos++] = '\n';
            lineChars = 0;
            i++;
        }
        else
        {
            int k;
            for (k = 0; k < seqlen; k++)
            {
                visible[visPos++] = texto[i + k];
            }
            lineChars++;
            i += seqlen;
        }

        visible[visPos] = '\0';

        strncpy(
            gamectx->message,
            visible,
            sizeof(gamectx->message) - 1
        );

        gamectx->message[
            sizeof(gamectx->message) - 1
        ] = '\0';

        /* ANIMACION BOCA */
        gamectx->mouthTimer++;

        if (gamectx->mouthTimer >= MOUTH_SPEED)
        {
            gamectx->mouthFrame++;
            gamectx->mouthTimer = 0;

            if (gamectx->mouthFrame > 2)
                gamectx->mouthFrame = 0;
        }

        printGame(gamectx);

        /* 
        SONIDO
        */

        if (c != ' ' && c != '\n')
        {
            playRandomTalk(gamectx);
        }

        /* 
        VELOCIDAD TEXTO
         */

        if (key[KEY_SPACE])
        {
            //rest(1);
        }
        else
        {
            switch (c)
            {
                case '.':
                case '!':
                case '?':
                    rest(150);
                    break;

                case ',':
                case ';':
                    rest(80);
                    break;

                default:
                    rest(30);
                    break;
            }
        }
    }

    /* 
    TODO
    Boca cerrada final
    */
    printGame(gamectx);
    printBubble();

    if (texto == TXT_WELCOME3 || texto == TXT_ENDINGLOSE2)
    {
        Sound_PlaySfx(SFX_OLDLAUGHT);
    }

    if (waitAdvanceButton() == 'X') return 'X';

    gamectx->message[0] = '\0';

    gamectx->mouthFrame = 0;
    gamectx->mouthTimer = 0;
    printGame(gamectx);

    return '\0';
}

void printBasicText(int margin, int y, const char *texto, int color, int fontType, int value)
{
    
    /*
    printBasicText()

    fontType:
        0 = usa la fuente genérica de Allegro y aplica "color".
        1 = usa hudFont2 e ignora "color" (usa su propio color).

    value:
        NULL = el texto no lleva ningún número.
        &variable = permite usar un único %d en "texto".

    Ejemplos:

    Sin número:
        printBasicText(10, 20, "NUEVA MANO", -1, 1, NULL);

    Con número:
        int numero = 3;
        printBasicText(10, 20, "RONDA %d", -1, 1, &numero);

    IMPORTANTE:
        Esta versión solo admite un %d.
    */
    
    char formatted[256];
    char word[64];
    char line[256];

    int wordLen = 0;
    int lineLen = 0;

    int drawY = y;
    int x = margin;
    int maxWidth = SCREEN_W - (margin * 2);

    FONT *fontToUse;


    /* 
       SELECCIONAR FUENTE
       */

    if (fontType == 1)
        fontToUse = hudFont2;
    else
        fontToUse = font;


    /* 
       PREPARAR TEXTO
        */

    if (value != -1)
    {
        sprintf(formatted, texto, value);
    }
    else
    {
        strcpy(formatted, texto);
    }


    line[0] = '\0';


    /* 
       WORD WRAP
     */

    texto = formatted;

    while (*texto)
    {
        char c = *texto;

        /* formar palabra */
        if (c != ' ' && c != '\n' && *(texto + 1) != '\0')
        {
            word[wordLen++] = c;
        }
        else
        {
            if (*(texto + 1) == '\0' && c != ' ' && c != '\n')
            {
                word[wordLen++] = c;
            }

            word[wordLen] = '\0';


            /* probar si cabe */
            char test[300];

            if (lineLen == 0)
                sprintf(test, "%s", word);
            else
                sprintf(test, "%s %s", line, word);


            if (text_length(fontToUse, test) > maxWidth)
            {
                if (fontType == 0)
                {
                    textout_ex(
                        screen,
                        fontToUse,
                        line,
                        x,
                        drawY,
                        color,
                        -1);
                }
                else
                {
                    textout_ex(
                        screen,
                        fontToUse,
                        line,
                        x,
                        drawY,
                        -1,
                        -1);
                }

                drawY += text_height(fontToUse) + 2;

                strcpy(line, word);
                lineLen = strlen(word);
            }
            else
            {
                if (lineLen > 0)
                {
                    strcat(line, " ");
                    lineLen++;
                }

                strcat(line, word);
                lineLen += strlen(word);
            }

            wordLen = 0;


            /* salto de línea manual */
            if (c == '\n')
            {
                if (fontType == 0)
                {
                    textout_ex(
                        screen,
                        fontToUse,
                        line,
                        x,
                        drawY,
                        color,
                        -1);
                }
                else
                {
                    textout_ex(
                        screen,
                        fontToUse,
                        line,
                        x,
                        drawY,
                        -1,
                        -1);
                }

                drawY += text_height(fontToUse) + 2;

                line[0] = '\0';
                lineLen = 0;
            }
        }

        texto++;
    }


    /* 
       ÚLTIMA LÍNEA
       */

    if (lineLen > 0)
    {
        if (fontType == 0)
        {
            textout_ex(
                screen,
                fontToUse,
                line,
                x,
                drawY,
                color,
                -1);
        }
        else
        {
            textout_ex(
                screen,
                fontToUse,
                line,
                x,
                drawY,
                -1,
                -1);
        }
    }
}

void printGrannyEnd(GameContext *gamectx)
{
  
    int j;



        for (j = 0; j < 12; j++)
        {
            /* Negro */
            clear_to_color(screen, 1);
            vsync();
            rest(2);

            /* Juego + Granny 2 */
            printGame(gamectx);

            if (pnjGrannyEnd)
            {
                masked_blit(
                    pnjGrannyEnd,
                    screen,
                    0, 0,
                    11 * TILE,
                    0,
                    160, 96
                );
            }

            vsync();
            rest(20);
        }


}