#include <allegro.h>
#include "input.h"
#include "audio.h"
#include "graphics.h"




char waitAdvanceButton(void)
{
    /* =========================
   WAIT ADVANCE BUTTON
   SOLO ENTER O ESPACIO o esc etc
   ========================= */
    clear_keybuf();

    while (1)
    {
        /* Esc o Ctrl + X = Salir */

        if (key[KEY_ESC] ||
            ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_X]))
        {
            while (key[KEY_ESC] ||
                   key[KEY_LCONTROL] || key[KEY_RCONTROL] ||
                   key[KEY_X])
            {
                rest(10);
            }

            clear_keybuf();
            return 'X';
        }

        /* Enter o Espacio = Avanzar */

        if (key[KEY_ENTER] || key[KEY_SPACE])
        {
            while (key[KEY_ENTER] || key[KEY_SPACE])
            {
                rest(10);
            }

            Sound_PlaySfx(SFX_SELECT);
            clear_keybuf();
            return 'A';
        }

        rest(10);
    }
}

char getPlayerChoice()
{
    int drawKey;
    int standKey;

    clear_keybuf();

    /* Seleccionar teclas según idioma */
    if (currentLanguage == LANG_ES)
    {
        drawKey  = KEY_C;   /* Carta */
        standKey = KEY_Q;   /* Quedarse */
    }
    else
    {
        drawKey  = KEY_H;   /* Hit */
        standKey = KEY_S;   /* Stand */
    }

    while (1)
    {
        /* Esc o Ctrl+X = Salir */

        if (key[KEY_ESC] ||
            ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_X]))
        {
            while (key[KEY_ESC] ||
                   key[KEY_LCONTROL] ||
                   key[KEY_RCONTROL] ||
                   key[KEY_X])
            {
                rest(10);
            }

            clear_keybuf();
            return 'X';
        }

        if (key[drawKey])
        {
            while (key[drawKey])
                rest(10);

            clear_keybuf();
            Sound_PlaySfx(SFX_SELECT);
            return 'D';      /* Internamente sigue siendo Draw */
        }

        if (key[standKey])
        {
            while (key[standKey])
                rest(10);

            clear_keybuf();
            Sound_PlaySfx(SFX_SELECT);
            return 'S';      /* Internamente sigue siendo Stand */
        }

        rest(10);
    }
}

char getAdultAnswer(){
    clear_keybuf();

    while (1)
    {
        /* Ctrl + Shift + X = Cheat Adult Test */

        if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) &&
            (key[KEY_LSHIFT]   || key[KEY_RSHIFT]) &&
             key[KEY_X])
        {
            while (
                key[KEY_LCONTROL] || key[KEY_RCONTROL] ||
                key[KEY_LSHIFT]   || key[KEY_RSHIFT]   ||
                key[KEY_X]
            )
            {
                rest(10);
            }

            clear_keybuf();
            Sound_PlaySfx(SFX_SELECT);
            return 'T';
        }
       
         if (key[KEY_ESC])
        {
            while (key[KEY_ESC]) rest(10);
            clear_keybuf();
            return 'X';
        }

        if (key[KEY_1])
        {
            while (key[KEY_1]) rest(10);

            clear_keybuf();
            return '1';
        }

        if (key[KEY_2])
        {
            while (key[KEY_2]) rest(10);

            clear_keybuf();
            return '2';
        }

        if (key[KEY_3])
        {
            while (key[KEY_3]) rest(10);

            clear_keybuf();
            return '3';
        }

        rest(10);
    }
}

char getPlayerInputBug(void)
{
    clear_keybuf();

    while (1)
    {
        /* =========================
           ESC = salir
           ========================= */

        if (key[KEY_ESC])
        {
            while (key[KEY_ESC])
            {
                rest(10);
            }

            clear_keybuf();
            return 'X';
        }


        /* =========================
           ENTER = aceptar
           ========================= */

        if (key[KEY_ENTER])
        {
            while (key[KEY_ENTER])
            {
                rest(10);
            }

            Sound_PlaySfx(SFX_SELECT);
            clear_keybuf();
            return 'A';
        }


        /* =========================
           A
           ========================= */

        if (key[KEY_A])
        {
            while (key[KEY_A])
                rest(10);

            clear_keybuf();
            return 'A';
        }


        /* =========================
           R
           ========================= */

        if (key[KEY_R])
        {
            while (key[KEY_R])
                rest(10);

            clear_keybuf();
            return 'R';
        }


        /* =========================
           F
           ========================= */

        if (key[KEY_F])
        {
            while (key[KEY_F])
                rest(10);

            clear_keybuf();
            return 'F';
        }


        /* =========================
           G
           ========================= */

        if (key[KEY_G])
        {
            while (key[KEY_G])
                rest(10);

            clear_keybuf();
            return 'G';
        }


        /* =========================
           O
           ========================= */

        if (key[KEY_O])
        {
            while (key[KEY_O])
                rest(10);

            clear_keybuf();
            return 'O';
        }

        rest(10);
    }
}


MenuOption menuInput(void)
{
    clear_keybuf();

    while (1)
    {
        /* Ctrl+X = Salir */
        if ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_X])
        {
            while (key[KEY_LCONTROL] || key[KEY_RCONTROL] || key[KEY_X])
                rest(10);

            clear_keybuf();
            return MENU_OPTION_EXIT;
        }

        /*=========================
          MENÚ EN ESPAÑOL
        =========================*/
        if (currentLanguage == LANG_ES)
        {
            /* Salir */
            if (key[KEY_ESC] || key[KEY_S])
            {
                while (key[KEY_ESC] || key[KEY_S])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('S', 130, 173);
                Sound_PlaySfx(SFX_SELECT);
                rest(100);
                return MENU_OPTION_EXIT;
            }

            /* Jugar */
            if (key[KEY_J])
            {
                while (key[KEY_J])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('J', 126, 89);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_PLAY;
            }

            /* Créditos */
            if (key[KEY_C])
            {
                while (key[KEY_C])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('C', 113, 145);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_CREDITS;
            }

            /* Idioma */
            if (key[KEY_I])
            {
                while (key[KEY_I])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('I', 123, 117);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_LANGUAJE;
            }
        }

        /*=========================
          ENGLISH MENU
        =========================*/
        else
        {
            /* Exit */
            if (key[KEY_ESC] || key[KEY_E])
            {
                while (key[KEY_ESC] || key[KEY_E])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('E', 135, 173);
                Sound_PlaySfx(SFX_SELECT);

                rest(100);
                return MENU_OPTION_EXIT;
            }

            /* Play */
            if (key[KEY_P])
            {
                while (key[KEY_P])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('P', 135, 89);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_PLAY;
            }

            /* Credits */
            if (key[KEY_C])
            {
                while (key[KEY_C])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('C', 119, 145);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_CREDITS;
            }

            /* Language */
            if (key[KEY_L])
            {
                while (key[KEY_L])
                    rest(10);

                clear_keybuf();

                printTitleHotkey('L', 112, 117);
                Sound_PlaySfx(SFX_SELECT);

                return MENU_OPTION_LANGUAJE;
            }
        }

        rest(10);
    }
}

char languageInput(void)
{
    clear_keybuf();

    while (1)
    {
        /* Esc o Ctrl+X = Salir */

        if (key[KEY_ESC] ||
            ((key[KEY_LCONTROL] || key[KEY_RCONTROL]) && key[KEY_X]))
        {
            while (key[KEY_ESC] ||
                   key[KEY_LCONTROL] || key[KEY_RCONTROL] ||
                   key[KEY_X])
            {
                rest(10);
            }

            clear_keybuf();
            return 'X';
        }

        /* Español */

        if (key[KEY_1])
        {
            while (key[KEY_1])
                rest(10);

            clear_keybuf();

            Sound_PlaySfx(SFX_SELECT);
            loadLanguage(LANG_ES);

            return 'A';
        }

        /* English */

        if (key[KEY_2])
        {
            while (key[KEY_2])
                rest(10);

            clear_keybuf();

            Sound_PlaySfx(SFX_SELECT);
            loadLanguage(LANG_EN);

            return 'A';
        }

        rest(10);
    }
}