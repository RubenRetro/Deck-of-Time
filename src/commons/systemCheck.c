#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "systemCheck.h"
#include "input.h"

#define GAME_CREATION_YEAR 2026
#define BOX_WIDTH 56
#define STATUS_WIDTH 6   /* ancho fijo del campo de estado, ej: "[ OK ]" (6 chars) */

#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN    10
#define LIGHTCYAN     11
#define LIGHTRED      12
#define LIGHTMAGENTA  13
#define YELLOW        14
#define WHITE         15

#define BOX_BG   BLUE
#define BOX_FG   WHITE

bool g_isLowEndSystem = false;


/* ============================================================
   UTILIDADES DE LA CAJA
   ============================================================ */

static int boxMargin(void)
{
    int screenCols = 80;
    return (screenCols - BOX_WIDTH) / 2;
}


static void printMargin(void)
{
    int i;
    int m = boxMargin();

    for (i = 0; i < m; i++)
        printf(" ");
}


/* ============================================================
   MARCO SUPERIOR
   ============================================================ */

static void printBoxTop(void)
{
    int i;

    printMargin();

    fflush(stdout);

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xC9");

    for (i = 0; i < BOX_WIDTH - 2; i++)
        cprintf("\xCD");

    cprintf("\xBB\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   MARCO INFERIOR
   ============================================================ */

static void printBoxBottom(void)
{
    int i;

    printMargin();

    fflush(stdout);

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xC8");

    for (i = 0; i < BOX_WIDTH - 2; i++)
        cprintf("\xCD");

    cprintf("\xBC\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   LINEA NORMAL DE LA CAJA
   ============================================================ */

static void printBoxLine(const char *text)
{
    int len = strlen(text);
    int pad = BOX_WIDTH - 4 - len;
    int i;

    if (pad < 0)
        pad = 0;

    printMargin();

    fflush(stdout);

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xBA %s", text);

    for (i = 0; i < pad; i++)
        cprintf(" ");

    cprintf(" \xBA\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   LINEA CENTRADA DE LA CAJA
   ============================================================ */

static void printBoxCentered(const char *text)
{
    int len = strlen(text);
    int totalPad = BOX_WIDTH - 4 - len;
    int left = totalPad / 2;
    int right = totalPad - left;
    int i;

    if (left < 0)
        left = 0;

    if (right < 0)
        right = 0;

    printMargin();

    fflush(stdout);

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xBA ");

    for (i = 0; i < left; i++)
        cprintf(" ");

    cprintf("%s", text);

    for (i = 0; i < right; i++)
        cprintf(" ");

    cprintf(" \xBA\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   HUECOS PARA LOS CHECKS
   ============================================================ */

static int printCheckPlaceholder(const char *label)
{
    int labelLen = strlen(label);
    int pad = BOX_WIDTH - 5 - labelLen - STATUS_WIDTH;
    int i;
    int row;

    if (pad < 1)
        pad = 1;

    printMargin();

    fflush(stdout);

    row = wherey();

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xBA %s", label);

    for (i = 0; i < pad; i++)
        cprintf(".");

    cprintf(" ");

    /*
       Dejamos el espacio del estado en negro.
       Esto se mantiene porque los [ OK ], [NONE], etc.
       aparecen independientemente del fondo azul.
    */

    textbackground(BLACK);

    for (i = 0; i < STATUS_WIDTH; i++)
        cprintf(" ");

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf(" \xBA\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);

    return row;
}


/* ============================================================
   CAMBIA EL ESTADO [ OK ], [FAIL], ETC.
   ============================================================ */

static void setCheckStatus(int row, const char *status, int color)
{
    int col;

    col = boxMargin() + BOX_WIDTH - 1 - STATUS_WIDTH;

    fflush(stdout);

    textbackground(BLACK);
    textcolor(color);

    gotoxy(col, row);

    cprintf("%s", status);

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}



static int printBoxStatusPlaceholder(void)
{
    int i;
    int row;
    int width = BOX_WIDTH - 4;

    printMargin();

    fflush(stdout);

    row = wherey();

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    cprintf("\xBA ");

    for (i = 0; i < width; i++)
        cprintf(" ");

    cprintf(" \xBA\r\n");

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);

    return row;
}


/* ============================================================
   ESCRIBE EL ESTADO FINAL CENTRADO SOBRE AZUL
   ============================================================ */

static void setBoxStatusCentered(int row, const char *text, int color)
{
    int width = BOX_WIDTH - 4;
    int len = strlen(text);
    int leftPad = (width - len) / 2;
    int col;
    int i;

    if (leftPad < 0)
        leftPad = 0;

    col = boxMargin() + 3 + leftPad;

    fflush(stdout);

    /*
       pintamos TODA la zona interior de azul.
       Esto elimina cualquier resto de negro.
    */

    gotoxy(boxMargin() + 2, row);

    textbackground(BOX_BG);
    textcolor(BOX_FG);

    for (i = 0; i < width; i++)
        cprintf(" ");

    /*
       Ahora escribimos el texto sobre azul.
    */

    gotoxy(col, row);

    textbackground(BOX_BG);
    textcolor(color);

    cprintf("%s", text);

    textbackground(BLACK);
    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   DIBUJA UN CARACTER DEL MARCO
   ============================================================ */

static void drawFrameChar(int x,
                          int y,
                          int left,
                          int right,
                          int top,
                          int bottom,
                          int color)
{
    gotoxy(x, y);

    textbackground(BOX_BG);
    textcolor(color);

    /*
       ESQUINAS
    */

    if (x == left && y == top)
    {
        cprintf("\xC9");
    }
    else if (x == right && y == top)
    {
        cprintf("\xBB");
    }
    else if (x == left && y == bottom)
    {
        cprintf("\xC8");
    }
    else if (x == right && y == bottom)
    {
        cprintf("\xBC");
    }

    /*
       PARTE SUPERIOR / INFERIOR
    */

    else if (y == top || y == bottom)
    {
        cprintf("\xCD");
    }

    /*
       LATERALES
    */

    else if (x == left || x == right)
    {
        cprintf("\xBA");
    }

    textbackground(BLACK);
    textcolor(LIGHTGRAY);
}


/* ============================================================
   EFECTO DE BRILLO DEL MARCO
   ============================================================
*/


static void animateFrameGlow(int top, int bottom)
{
    int left;
    int right;

    int x;
    int y;

    int oldX = -1;
    int oldY = -1;

    left = boxMargin() + 1;
    right = left + BOX_WIDTH - 1;


    /* ========================================================
       ARRIBA
       ======================================================== */

    for (x = left; x <= right; x++)
    {
        /*
           Restaura la posición anterior.
        */

        if (oldX != -1)
        {
            drawFrameChar(oldX,
                          oldY,
                          left,
                          right,
                          top,
                          bottom,
                          BOX_FG);
        }

        /*
           Dibuja el brillo.
        */

        drawFrameChar(x,
                      top,
                      left,
                      right,
                      top,
                      bottom,
                      LIGHTCYAN);

        oldX = x;
        oldY = top;

        rest(3);
    }


    /* ========================================================
       DERECHA
       ======================================================== */

    for (y = top + 1; y <= bottom; y++)
    {
        /*
           Restaura posición anterior.
        */

        drawFrameChar(oldX,
                      oldY,
                      left,
                      right,
                      top,
                      bottom,
                      BOX_FG);

        /*
           Dibuja brillo.
        */

        drawFrameChar(right,
                      y,
                      left,
                      right,
                      top,
                      bottom,
                      LIGHTCYAN);

        oldX = right;
        oldY = y;

        rest(3);
    }


    /* ========================================================
       ABAJO
       ======================================================== */

    for (x = right - 1; x >= left; x--)
    {
        /*
           Restaura posición anterior.
        */

        drawFrameChar(oldX,
                      oldY,
                      left,
                      right,
                      top,
                      bottom,
                      BOX_FG);

        /*
           Dibuja brillo.
        */

        drawFrameChar(x,
                      bottom,
                      left,
                      right,
                      top,
                      bottom,
                      LIGHTCYAN);

        oldX = x;
        oldY = bottom;

        rest(3);
    }


    /* ========================================================
       IZQUIERDA
       ======================================================== */

    for (y = bottom - 1; y >= top; y--)
    {
        /*
           Restaura posición anterior.
        */

        drawFrameChar(oldX,
                      oldY,
                      left,
                      right,
                      top,
                      bottom,
                      BOX_FG);

        /*
           Dibuja brillo.
        */

        drawFrameChar(left,
                      y,
                      left,
                      right,
                      top,
                      bottom,
                      LIGHTCYAN);

        oldX = left;
        oldY = y;

        rest(3);
    }


    /*
       Restaura la última posición.
    */

    drawFrameChar(oldX,
                  oldY,
                  left,
                  right,
                  top,
                  bottom,
                  BOX_FG);

    fflush(stdout);
}


/* ============================================================
   TEXTO FUERA DE LA CAJA
   ============================================================ */

static void printOutside(int color, const char *text)
{
    fflush(stdout);

    textcolor(color);

    cprintf("%s", text);

    textcolor(LIGHTGRAY);

    fflush(stdout);
}


/* ============================================================
   SYSTEM CHECK
   ============================================================ */

int systemCheck(void)
{
    int rowAllegro;
    int rowGfx;
    int rowCpu;
    int rowKeyboard;

    int rowTimer;
    int rowSound;
    int rowMouse;
    int rowJoystick;

    int rowStatus;
    int rowAfterBox;
    int rowNext;

    /*
       Coordenadas de la caja para la animación.
    */

    int boxTop;
    int boxBottom;


    system("cls");


    /* ========================================================
       INICIALIZAR ALLEGRO
       ======================================================== */

    if (allegro_init() != 0)
    {
        printf("ERROR: Allegro could not be initialized.\n");
        return 1;
    }


    /* ========================================================
       DETECTAR CPU
       ======================================================== */

    g_isLowEndSystem = (cpu_family < 4);


    /* ========================================================
       COLOR 8 BITS
       ======================================================== */

    set_color_depth(8);


    /* ========================================================
       COMPROBAR GRAFICOS
       ======================================================== */

    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0)
    {
        printf("ERROR: 320x200x8 graphics mode not supported.\n");
        return 1;
    }


    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);


    /* ========================================================
       TITULO
       ======================================================== */

    printf("\n");

    printMargin();

    printOutside(LIGHTCYAN,
                 "D E C K T I M E\r\n");

    printf("\n");


    /* ========================================================
       CAJA
       ======================================================== */

    /*
       Guardamos la fila superior antes de imprimirla.
    */

    boxTop = wherey();


    printBoxTop();

    printBoxCentered("SYSTEM COMPATIBILITY TEST");

    printBoxLine("");


    rowAllegro =
        printCheckPlaceholder("Allegro engine");

    rowGfx =
        printCheckPlaceholder("Graphics mode 320x200");

    rowCpu =
        printCheckPlaceholder("CPU class");

    rowKeyboard =
        printCheckPlaceholder("Keyboard");

    rowTimer =
        printCheckPlaceholder("Timer");

    rowSound =
        printCheckPlaceholder("Sound device");

    rowMouse =
        printCheckPlaceholder("Mouse");

    rowJoystick =
        printCheckPlaceholder("Joystick");


    printBoxLine("");


    rowStatus =
        printBoxStatusPlaceholder();


    printBoxBottom();


    /*
       La última línea de la caja es wherey()-1.
    */

    boxBottom = wherey() - 1;


    /*
       Guardam la posición donde empezará el texto
       exterior de la caja.
    */

    rowAfterBox = wherey();


    /* ========================================================
       ALLEGRO
       ======================================================== */

    setCheckStatus(rowAllegro,
                   "[ OK ]",
                   GREEN);

    rest(20);


    /* ========================================================
       GRAFICOS
       ======================================================== */

    setCheckStatus(rowGfx,
                   "[ OK ]",
                   GREEN);

    rest(20);


    /* ========================================================
       CPU
       ======================================================== */

    {
        int cpuColor;
        const char *cpuLabel;


        if (cpu_family < 4)
        {
            cpuColor = RED;
            cpuLabel = "[ 386]";
        }
        else if (cpu_family == 4)
        {
            cpuColor = GREEN;
            cpuLabel = "[ 486]";
        }
        else
        {
            cpuColor = GREEN;
            cpuLabel = "[FAST]";
        }


        setCheckStatus(rowCpu,
                       cpuLabel,
                       cpuColor);

        rest(20);
    }


    /* ========================================================
       KEYBOARD
       ======================================================== */

    rest(20);


    if (install_keyboard() != 0)
    {
        setCheckStatus(rowKeyboard,
                       "[FAIL]",
                       RED);


        /*
           NOT COMPATIBLE
        */

        setBoxStatusCentered(rowStatus,
                             "SYSTEM STATUS: NOT COMPATIBLE",
                             RED);


        gotoxy(1, rowAfterBox + 1);

        printMargin();

        printOutside(RED,
                     "ERROR: Keyboard driver not available.\r\n");


        return 1;
    }


    setCheckStatus(rowKeyboard,
                   "[ OK ]",
                   GREEN);

    rest(20);


    /* ========================================================
       TIMER
       ======================================================== */

    if (install_timer() != 0)
    {
        setCheckStatus(rowTimer,
                       "[FAIL]",
                       RED);
    }
    else
    {
        setCheckStatus(rowTimer,
                       "[ OK ]",
                       GREEN);
    }


    rest(20);


    /* ========================================================
       SOUND
       ======================================================== */

    rest(20);


    if (install_sound(DIGI_AUTODETECT,
                      MIDI_AUTODETECT,
                      NULL) != 0)
    {
        setCheckStatus(rowSound,
                       "[NONE]",
                       DARKGRAY);
    }
    else
    {
        setCheckStatus(rowSound,
                       "[ OK ]",
                       GREEN);

        remove_sound();
    }


    rest(20);


    /* ========================================================
       MOUSE
       ======================================================== */

    if (install_mouse() < 0)
    {
        setCheckStatus(rowMouse,
                       "[NONE]",
                       DARKGRAY);
    }
    else
    {
        setCheckStatus(rowMouse,
                       "[ OK ]",
                       GREEN);

        remove_mouse();
    }


    rest(20);


    /* ========================================================
       JOYSTICK
       ======================================================== */

    if (install_joystick(JOY_TYPE_AUTODETECT) != 0)
    {
        setCheckStatus(rowJoystick,
                       "[NONE]",
                       DARKGRAY);
    }
    else
    {
        setCheckStatus(rowJoystick,
                       "[ OK ]",
                       GREEN);

        remove_joystick();
    }


    rest(3);


    /* ========================================================
       ESTADO FINAL
       ========================================================

    */

    animateFrameGlow(boxTop,
                     boxBottom);


    /* ========================================================
       SYSTEM STATUS: COMPATIBLE
       ========================================================

    */

    setBoxStatusCentered(rowStatus,
                         "SYSTEM STATUS: COMPATIBLE",
                         GREEN);


    /*
       pausa  antes de que aparezca el mensaje amarillo.
    */

    rest(40);


    /* ========================================================
       TEXTO INFERIOR
       ======================================================== */

    gotoxy(1, rowAfterBox + 1);


    {
        time_t t;
        struct tm *fecha;

        int year;
        int diff;

        char flavorText[128];


        t = time(NULL);

        fecha = localtime(&t);

        year = fecha->tm_year + 1900;

        diff = year - GAME_CREATION_YEAR;


        /* ====================================================
           MENSAJE SEGÚN EL AÑO
           ==================================================== */

        printMargin();


        if (diff < 0)
        {
            sprintf(flavorText,
                    "Parece que has viajado al pasado... este juego\r\n");

            printOutside(YELLOW,
                         flavorText);


            printMargin();


            sprintf(flavorText,
                    "todavia no existe en el ano %d!\r\n",
                    year);

            printOutside(YELLOW,
                         flavorText);
        }


        else if (diff == 0)
        {
            sprintf( flavorText, "A\xA4" "o %d... el mismo a\xA4" "o en que naci\xA2 este juego.\r\n", year );

            printOutside(YELLOW,
                         flavorText);


            printMargin();

            printOutside(YELLOW,
                         "Espero que lo disfrutes!\r\n");
        }


        else if (diff < 10)
        {
sprintf( flavorText, "Estamos en el a\xA4" "o %d. Espero que disfrutes del juego!\r\n", year );

            printOutside(YELLOW,
                         flavorText);
        }


        else
        {
sprintf( flavorText, "Genial, estamos en el a\xA4" "o %d... y todav\xA1" "a\r\n", year );

            printOutside(YELLOW,
                         flavorText);


            printMargin();

            printOutside(YELLOW,
                         "jugando a esto!\r\n");
        }
    }


    /* ========================================================
       MENSAJE DEL CONTEST
       ======================================================== */

    rowNext = wherey();


    gotoxy(1, rowNext + 1);

    printMargin();

    printOutside(YELLOW,
                 "Programado en 2026 para el MS-DOS Contest 2.\r\n");


    /* ========================================================
       ESPERAR BOTON
       ======================================================== */

    if (waitAdvanceButton() == 'X')
        return 1;


    return 0;
}