#include "tracker.h"
#include "menus.h"
#include "graphics.h"
#include "audio.h"
#include "lang.h"
#include "input.h"
#include <stdio.h>


#define QUESTION_POOL_SIZE 10
#define NUM_QUESTIONS      3

#define CREDIT_SPACING 12

void splashScreen(){



printdosconLogo();
printBasicText(10*TILE, 20*TILE, TXT_SPLASH_ENTRY, 255, 1, -1);

play_song();
rest(600);
fadeToBlack(4);


printLogorr();
fadeFromBlack(4);
rest(1200);
fadeToBlack(2);

}

int langMenu(void)
{
    
    system("cls");
printf("\n\n\n%30s SELECT LANGUAGE\n\n\n", "");
printf("\n%30s   1 - ESPANOL\n", "");
printf("\n%30s   2 - ENGLISH\n", "");
printf("\n%30s   ESC - EXIT\n\n\n\n%33s", "","");

    if (languageInput() == 'X')
        return 1;

    return 0;
}

void creditsMenu(void)
{
    const char *credits[] =
    {
        /*---------------------------------
          DEVELOPMENT
        ---------------------------------*/

        TXT_CREDITS_DEVELOPMENT,
        "RUBENRETRO"

        "",

        /*---------------------------------
          GRAPHICS
        ---------------------------------*/

        TXT_CREDITS_GRAPHICS,
        "RUBENRETRO"

        "",

        /*---------------------------------
          FONT
        ---------------------------------*/

        TXT_CREDITS_FONT,
        "DAMIENG",

        "",

        /*---------------------------------
          MUSIC
        ---------------------------------*/

        TXT_CREDITS_MUSIC,
        "TOURDION",
        "TRADITIONAL / ANONYMOUS",

          "",

        "PASTIME WITH GOOD COMPANY",
        "ENRIQUE VIII",

        "",

        /*---------------------------------
          SOUND EFFECTS
        ---------------------------------*/

        TXT_CREDITS_SOUND,
        "RUBENRETRO",

        "",

        /*---------------------------------
          TECHNOLOGY
        ---------------------------------*/

        TXT_CREDITS_TECHNOLOGY,
        "ALLEGRO 4.2.3",
        "DJGPP",

        "",

        /*---------------------------------
          SPECIAL THANKS
        ---------------------------------*/

        TXT_CREDITS_SPECIAL,
        "WAVE",

        "",

        NULL
    };


    /*---------------------------------
      CONFIGURATION
    ---------------------------------*/

    int startY = 220;
    int endY   = -290;
    int x      = 160;
    int speed  = 1;

    int offsetY = startY;


    while (offsetY > endY)
    {
        printCredits(credits, x, offsetY);

        if (key[KEY_ESC])
            return;

        offsetY -= speed;

        rest(30);
    }
    fadeToBlack(2);
}


MenuOption mainMenu(){



printTitle();

fadeFromBlack(1);
Sound_PlayMusic(MUSIC_TITLE);


MenuOption choice = menuInput();



return choice;
}

bool adultTest(){
   

    //texto informativo
    clear_to_color(screen, 1);   // borra pantalla con índice de color 1 de la paleta (negro)
    fadeFromBlack(4); 
    
    printBasicText(128, 48, TXT_TEST_INTRO1, 190, 0, -1);
    printBasicText(32, 80, TXT_TEST_INTRO2, 190, 0, -1);
    if (waitAdvanceButton() == 'X') return false; // espera espacio o enter
    fadeToBlack(4);
    
    //inicio test
    printTest();
    fadeFromBlack(4); 
    
    
     //si supera el test, devolvera 1 (hay que asignarlo al bool adultContent) si no false
    unsigned char order[QUESTION_POOL_SIZE];
    unsigned char i;
    unsigned char j;
    unsigned char temp;
    unsigned char q;

    char answer;

    const char* questions[QUESTION_POOL_SIZE] =
    {
        TXT_TEST_QUESTION1,
        TXT_TEST_QUESTION2,
        TXT_TEST_QUESTION3,
        TXT_TEST_QUESTION4,
        TXT_TEST_QUESTION5,
        TXT_TEST_QUESTION6,
        TXT_TEST_QUESTION7,
        TXT_TEST_QUESTION8,
        TXT_TEST_QUESTION9,
        TXT_TEST_QUESTION10
    };

    const char answers[QUESTION_POOL_SIZE] =
    {
        '2',
        '1',
        '3',
        '2',
        '1',
        '3',
        '2',
        '1',
        '3',
        '2'
    };

    /* Crear orden inicial */

    for (i = 0; i < QUESTION_POOL_SIZE; i++)
    {
        order[i] = i;
    }

    /* Mezclar preguntas */

    for (i = 0; i < QUESTION_POOL_SIZE; i++)
    {
        j = rand() % QUESTION_POOL_SIZE;

        temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }

    /* Lanzar NUM_QUESTIONS preguntas */

    for (i = 0; i < NUM_QUESTIONS; i++)
    {
        q = order[i];

        
        printTest();
    
        printBasicText(20, 40, questions[q],1, 0, -1);

        answer = getAdultAnswer();

        /* Cheat */
        if (answer == 'T')
        {
            printTest();
            printBasicText(28, 64, TXT_TEST_CHEAT , 1, 0, -1);
                if (waitAdvanceButton() == 'X') return false; // espera espacio o enter
            fadeToBlack(1);
            return true;
        }
        //esc para omitir test(fallo aoutomatico)

        if (answer == 'X')
        {
            
            fadeToBlack(4);
            return false;
        }

        /* Error */
        if (answer != answers[q])
        {
            printTest();
            printBasicText(28, 64, TXT_TEST_FAIL, 1, 0, -1);
                if (waitAdvanceButton() == 'X') return false; // espera espacio o enter
            fadeToBlack(1);
            return false;
        }
    }

    /* Todo correcto */
    
    printTest();
    printBasicText(28, 64, TXT_TEST_PASS , 1, 0, -1);
     if (waitAdvanceButton() == 'X') return false; // espera espacio o enter

    fadeToBlack(1);
    return true;
}

void menuExit(void)
{
    system("cls");
    printf("%s\n", TXT_MENUEXIT);
    
}