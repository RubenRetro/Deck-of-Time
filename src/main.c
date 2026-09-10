#include <allegro.h>
#include <time.h>
#include <string.h>

#include "commons/deck.h"
#include "commons/gamecontext.h"
#include "commons/graphics.h"
#include "commons/input.h"
#include "commons/match.h"
#include "commons/menus.h"
#include "commons/audio.h"
#include "commons/lang.h"
#include "commons/systemCheck.h"


int main(void) {
    
    GameContext game = {0};

    
    if(systemCheck() != 0) return 1;

    if (langMenu()) return 1;

    srand(time(NULL));//inicia semmilla de random


    initGraphics();

    Sound_Init();



//intro aqui
splashScreen();
game.adultContent = adultTest();
//game.adultContent= true; //TEST


if (game.adultContent == true){
    while (1) {
        MenuOption option = mainMenu();

        if (option == MENU_OPTION_PLAY) {
                fadeToBlack(1);  
                match(&game);
        } else if (option == MENU_OPTION_CREDITS) {
                creditsMenu();
        } else if (option == MENU_OPTION_LANGUAJE) {
                loadLanguage(currentLanguage == LANG_ES ? LANG_EN : LANG_ES );
                fadeToBlack(8); 
        } else if (option == MENU_OPTION_EXIT) {
                break;
        }
    }
}

Sound_Shutdown();
destroyGraphics();
set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

menuExit();

return 0;
}
END_OF_MAIN();