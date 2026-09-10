#include "lang.h"
Language currentLanguage;


const char *TXT_SPLASH_ENTRY;

const char *TXT_TEST_INTRO1;
const char *TXT_TEST_INTRO2;
const char *TXT_TEST_PASS;
const char *TXT_TEST_FAIL;
const char *TXT_TEST_CHEAT;


const char *TXT_WELCOME;
const char *TXT_WELCOME1;
const char *TXT_WELCOME2;
const char *TXT_WELCOME3;

const char *TXT_NEWHAND;
const char *TXT_SHUFFLE;
const char *TXT_DECISION;

const char *TXT_DARE1;
const char *TXT_DARE2;
const char *TXT_DARE3;

const char *TXT_DEALERBUST;
const char *TXT_BUST;
const char *TXT_DEALERDRAWS;

const char *TXT_HANDWIN;
const char *TXT_HANDWIN2;
const char *TXT_HANDWIN3;
const char *TXT_HANDLOST;
const char *TXT_HANDLOST2;
const char *TXT_HANDLOST3;


const char *TXT_HANDDRAW;

const char *TXT_ROUNDRESULT;
const char *TXT_ROUNDRESULT1;
const char *TXT_ROUNDRESULT2;

const char *TXT_ENDINGLOSE1; 
const char *TXT_ENDINGLOSE2; 
const char *TXT_ENDINGWIN1; 
    
const char *TXT_ENDINGWINA; 
const char *TXT_ENDINGWINB; 
const char *TXT_ENDINGWINC;
    
const char *TXT_ENDINGWIN2;
const char *TXT_ENDINGLOSEERROR;


const char *TXT_CREDITS_DEVELOPMENT;
const char *TXT_CREDITS_GRAPHICS;
const char *TXT_CREDITS_FONT;
const char *TXT_CREDITS_MUSIC;
const char *TXT_CREDITS_SOUND;
const char *TXT_CREDITS_TECHNOLOGY;
const char *TXT_CREDITS_SPECIAL;


const char *TXT_TEST_QUESTION1;
const char *TXT_TEST_QUESTION2;
const char *TXT_TEST_QUESTION3;
const char *TXT_TEST_QUESTION4;
const char *TXT_TEST_QUESTION5;
const char *TXT_TEST_QUESTION6;
const char *TXT_TEST_QUESTION7;
const char *TXT_TEST_QUESTION8;
const char *TXT_TEST_QUESTION9;
const char *TXT_TEST_QUESTION10;

const char *TXT_MENUEXIT;

void loadLanguage(Language lang){

currentLanguage = lang;
if (lang == LANG_ES) {
    
    
    
    TXT_SPLASH_ENTRY = "Participación de ...";
    
    TXT_TEST_INTRO1 = "¡ALTO!\n";
    TXT_TEST_INTRO2 = "Antes de continuar tenemos que comprobar tu edad."
                        "\n"
                        "\n"
                        " La última vez dejamos pasar a un menor y todavía estamos pagando la terapia.";


    TXT_TEST_PASS = "¡Has aprobado! Bienvenido al club."
                    "\n"
                    "\n"
                    "\n"
                    "Y recuerda: después de los cuarenta, una siesta deja de ser un capricho y pasa a ser tratamiento médico.";
    TXT_TEST_FAIL = "Lo sentimos, no has superado el control de edad."
                    "\n"
                    "\n"
                    "\n"
                    "Nuestro detector calcula que aún pides permiso para acostarte tarde. Acceso denegado.";
    TXT_TEST_CHEAT = "¡TRAMPOSO!"
                    "\n"
                    "\n"
                    "\n"
                    "Está claro que has jugado a suficientes aventuras gráficas. Puedes pasar, ya has demostrado tener una edad respetable.";
    
    
    
    TXT_WELCOME = "Bienvenido, jovencito. El azar os reclama. Tomad asiento y demostrad vuestra destreza con los naipes.";
    TXT_WELCOME1 = "Estos naipes pueden hacerme viajar en el tiempo: si vais ganando, regresaré a mis años mozos cuando era bella.";
    TXT_WELCOME2 = "Si no... volveré a mi tiempo actual, donde aún conservo mis encantos. Jeje.";
    TXT_WELCOME3 = "Mas no os preocupéis, jovencito: ganéis o perdáis... ¡al final os enseñaré los pechos!";
    
    TXT_SHUFFLE = "Ronda %d. Barajando.";        
    
    TXT_NEWHAND = "Nueva mano.";
    TXT_DECISION = "Tenéis %d puntos. ¿Qué haréis?";
    
    TXT_DARE1 = "¡Atreveos, mozo! ¡Aún podéis tentar al destino!";
    TXT_DARE2 = "¿Ya os plantáis? ¡Gallina!";
    TXT_DARE3  = "¡Poc, poc, poc! ¿Dónde está vuestro valor?";
   
    TXT_DEALERBUST = "La banca se pasa puntos.";
    TXT_BUST = "El jugador se pasa con %d puntos.";
    TXT_DEALERDRAWS = "La banca roba otra carta.";
    
    TXT_HANDLOST = "¡Os he dado una buena tunda, jovencito!";
    TXT_HANDLOST2 = "¡Esta vez los naipes han estado de mi parte, jovencito!";
    TXT_HANDLOST3 = "¡Qué mala suerte, mozo! Hoy el azar me sonríe.";

    TXT_HANDWIN = "¡Bien jugado, mozo! Esta vez los naipes os han sonreído.";
    TXT_HANDWIN2 = "¡Muy bien jugado, jovencito! Esa mano ha sido vuestra.";
    TXT_HANDWIN3 = "¡Vaya mano, mozo! Parece que el azar os quiere favorecer.";

    TXT_HANDDRAW = "¡Vaya, vaya! Parece que los naipes no se deciden por ninguno de los dos.";

    TXT_ROUNDRESULT = "Fin de la ronda. Resultado:";
    TXT_ROUNDRESULT1 = "Jugador: %d puntos.";
    TXT_ROUNDRESULT2 = "Banca:   %d puntos.";
    
    TXT_ENDINGLOSE1 = "Habéis perdido, jovencito. Venid, venid, que vais a recibir vuestra recompensa... ";
    TXT_ENDINGLOSE2 = "Mis pechos han visto días mejores, pero aún conservan todo su carácter. ¡Espero que tengáis buen estómago!";
    
    TXT_ENDINGWIN1 = "¡Habéis ganado! Ha llegado la hora de vuestra dulce recompensa. ¿Estáis preparado? Una... dos... y...";
    
    TXT_ENDINGWINA = "Me comunica vuestra mujer que sois un guarro y no os permite mirar estas cosas. Lo siento mucho.";
    TXT_ENDINGWINB = "¡Vaya! Parece que el buen desarrollador no tuvo tiempo de terminar algunos sprites. Qué contrariedad...";
    TXT_ENDINGWINC = "Parece que Allegro ha sufrido un error al cargar el bitmap. El desarrollador debió errar el nombre del sprite...";
    
    TXT_ENDINGWIN2 = "Gracias por vuestra visita y... ¡hasta la próxima!";

    TXT_ENDINGLOSEERROR = "Error del sistema: Desbordamiento del búfer óptico.\n"
                          "\n"
                          "EXCEPCIÓN CRÍTICA 06: Error de división por trauma visual.\n"
                          "La CPU se negó a procesar 'tetavieja.PCX'.\n"
                           "\n"
                           "\n"
                           "¿(A)bortar, (R)eintentar u (O)lvidar lo que acabas de ver? _";


    TXT_CREDITS_DEVELOPMENT = "DESARROLLO";
    TXT_CREDITS_GRAPHICS = "GRÁFICOS";
    TXT_CREDITS_FONT = "FUENTE";
    TXT_CREDITS_MUSIC = "MÚSICA";
    TXT_CREDITS_SOUND = "EFECTOS DE SONIDO";
    TXT_CREDITS_TECHNOLOGY = "TECNOLOGÍA";
    TXT_CREDITS_SPECIAL = " AGRADECIMIENTOS";

    //preguntas test
    TXT_TEST_QUESTION1 = 
    "Mucho antes de convertirse en la reina de las canciones del verano, ¿dónde dio el salto a la fama Leticia Sabater?"
    "\n"
    "\n"
    "\n"
    "1- Presentando el Telediario\n"
    "\n"
    "2- Presentando programas infantiles de televisión\n"
    "\n"
    "3- Como azafata de El Precio Justo";

    TXT_TEST_QUESTION2 = 
    "¿Cuál de las siguientes expresiones populares NO pertenecía al repertorio de frases míticas de Chiquito de la Calzada?"
    "\n"
    "\n"
    "\n"
    "1- Hemos triunfao como la Coca-Cola\n"
    "\n"
    "2- ¡Fistro, pecador de la pradera!\n"
    "\n"
    "3- Te das cuen, ¡Al ataquer!";


    TXT_TEST_QUESTION3 = 
    "¿Por qué motivo pasó a la historia de la televisión española la cantante italiana Sabrina Salerno en los años 80?"
    "\n"
    "\n"
    "\n"
    "1- Tuvo un romance con un presentador de TVE.\n"
    "\n"
    "2- Ganó Eurovisión en 1987.\n"
    "\n"
    "3- Se le salió un pecho cantando.";

    TXT_TEST_QUESTION4 = 
    "¿Qué actriz se hizo mundialmente famosa por correr por la playa en bañador rojo?"
    "\n"
    "\n"
    "\n"
    "1- Sharon Stone.\n"
    "\n"
    "2- Pamela Anderson.\n"
    "\n"
    "3- Julia Roberts.";


    TXT_TEST_QUESTION5 = 
    "Ana Torroja puso voz a uno de los grupos españoles más importantes de los años 80 y 90. ¿De qué grupo se trata?"
    "\n"
    "\n"
    "\n"
    "1- Mecano.\n"
    "\n"
    "2- Olé Olé.\n"
    "\n"
    "3- La Unión.";

    TXT_TEST_QUESTION6 = 
    "Michael Knight luchaba contra los malos acompañado de un coche capaz de hablar, pensar y conducir solo. ¿Cómo se llamaba aquel mítico automóvil?"
    "\n"
    "\n"
    "\n"
    "1- Optimus Prime.\n"
    "\n"
    "2- Rayo McQueen.\n"
    "\n"
    "3- KITT.";

    TXT_TEST_QUESTION7 = 
    "Cada noche repartía millones de pesetas desde el Telecupón con una sonrisa inconfundible. ¿Quién era aquella mítica presentadora?"
    "\n"
    "\n"
    "\n"
    "1- Concha Velasco.\n"
    "\n"
    "2- Carmen Sevilla.\n"
    "\n"
    "3- Ana Obregón.";

    TXT_TEST_QUESTION8 = 
    "Si creciste en los 90, esta deberías acertarla sin pestañear... ¿quién era el Príncipe de Bel-Air?"
    "\n"
    "\n"
    "\n"
    "\n"
    "1- Will Smith.\n"
    "\n"
    "2- Eddie Murphy.\n"
    "\n"
    "3- Wesley Snipes.";

    TXT_TEST_QUESTION9 = 
    "En 1992, España estuvo en el punto de mira de todo el mundo gracias a los Juegos Olímpicos de Barcelona. ¿Cómo se llamaba la simpática mascota diseñada por Javier Mariscal?"
    "\n"
    "\n"
    "1- Naranjito.\n"
    "\n"
    "2- Curro.\n"
    "\n"
    "3- Cobi.";


    TXT_TEST_QUESTION10 = 
    "Antes de que existieran los vídeos virales, medio país se partía de risa viendo a japoneses caer por cuestas imposibles. ¿Cómo se llamaba aquel programa?"
    "\n"
    "\n"
    "\n"
    "1- El Gran Juego de la Oca.\n"
    "\n"
    "2- Humor Amarillo.\n"
    "\n"
    "3- Waku Waku";

    TXT_MENUEXIT = "Gracias por jugar a DECKTIME.\n"
               "\n"
               "Esperamos que hayas disfrutado de la partida.\n"
               "\n"
               "Hasta pronto.";

} else {
    
     TXT_SPLASH_ENTRY = "An entry by ...";

    
    TXT_TEST_INTRO1 = "STOP!\n";
    TXT_TEST_INTRO2 = "Before we continue, we need to verify your age.. "
                    "\n"
                    "\n"
                    "Last time we let a minor slip through and we're still paying for the therapy.";


    TXT_TEST_PASS = "You passed! Welcome to the club."
                    "\n"
                    "\n"
                    "\n"
                    "And remember: after forty, a nap stops being a luxury and becomes medical treatment.";
    TXT_TEST_FAIL = "Sorry, you failed the age check."
                    "\n"
                    "\n"
                    "\n"
                    "Our scanner says you still need permission to stay up late. Access denied.";
    TXT_TEST_CHEAT = "CHEATER!"
                    "\n"
                    "\n"
                    "\n"
                    "It's obvious you've played enough point-and-click adventures. You may pass, you've clearly proven you're of a respectable age.";
    
    TXT_WELCOME = "Welcome, young one. Fate calls upon you. Take a seat and show us your skill with the cards.";
    TXT_WELCOME1 = "These cards can send me through time: if you're winning, I'll return to my younger years, when I was beautiful.";
    TXT_WELCOME2 = "If not... I'll return to my present time, where I still keep my charms. Heh heh.";
    TXT_WELCOME3 = "But worry not, young one: win or lose... in the end I'll flash you!";

    TXT_SHUFFLE = "Round %d. Shuffling.";        
    
    TXT_NEWHAND = "New hand.";
    TXT_DECISION = "You have %d points. What will you do?";
    
    TXT_DARE1 = "Go on then, lad! You can still tempt fate!";
    TXT_DARE2 = "Standing already? Chicken!";
    TXT_DARE3  = "Cluck, cluck, cluck! Where's your courage gone?";
   
    TXT_DEALERBUST = "The dealer busts.";
    TXT_BUST = "The player busts with %d points.";
    TXT_DEALERDRAWS = "The dealer draws another card.";
    
    TXT_HANDLOST = "I've given you a proper thrashing, young one!";
    TXT_HANDLOST2 = "The cards were on my side this time, young one!";
    TXT_HANDLOST3 = "Such bad luck, lad! Fortune smiles on me today.";

    TXT_HANDWIN = "Well played, lad! The cards have smiled upon you this time.";
    TXT_HANDWIN2 = "Very well played, young one! That hand was yours.";
    TXT_HANDWIN3 = "Quite a hand, lad! Seems fortune favours you.";

    TXT_HANDDRAW = "Well, well! Looks like the cards can't decide between the two of you.";

    TXT_ROUNDRESULT = "End of the round. Result:";
    TXT_ROUNDRESULT1 = "Player: %d points.";
    TXT_ROUNDRESULT2 = "Dealer: %d points.";

    TXT_ENDINGLOSE1 = "You have lost, young one. Come, come, it's time for your reward... ";
    TXT_ENDINGLOSE2 = "My chest has seen better days, but it still has plenty of character. Hope you've got a strong stomach!";

    TXT_ENDINGWIN1 = "You have won! The time has come for your sweet reward. Are you ready? One... two... and...";

    TXT_ENDINGWINA = "Your wife informs me you're a pervert and won't let you look at this. Terribly sorry.";
    TXT_ENDINGWINB = "Oh dear! Looks like the developer didn't have time to finish some of the sprites. What a shame...";
    TXT_ENDINGWINC = "Looks like Allegro hit an error loading the bitmap. The developer must have typed the sprite name wrong...";

    TXT_ENDINGWIN2 = "Thanks for visiting and... see you next time!";

        TXT_ENDINGLOSEERROR = "System Error: Optical Buffer Overflow.\n"
                          "\n"
                          "CRITICAL EXCEPTION 06: Visual Trauma Division Error.\n"
                          "Memory dump failed (CPU refused to process 'oldtit.PCX').\n"
                           "\n"
                           "\n"
                           "(A)bort, (R)etry, (F)ail, or (F)orget what you just saw?_";

    TXT_CREDITS_DEVELOPMENT = "DEVELOPMENT";
    TXT_CREDITS_GRAPHICS = "GRAPHICS";
    TXT_CREDITS_FONT = "FONT";
    TXT_CREDITS_MUSIC = "MUSIC";
    TXT_CREDITS_SOUND = "SOUND EFFECTS";
    TXT_CREDITS_TECHNOLOGY = "TECHNOLOGY";
    TXT_CREDITS_SPECIAL = "SPECIAL THANKS";

    //quiz questions
    TXT_TEST_QUESTION1 = 
    "Long before becoming the queen of summer hit songs, where did Leticia Sabater first rise to fame?"
    "\n"
    "\n"
    "\n"
    "1- Hosting the evening news\n"
    "\n"
    "2- Hosting children's TV shows\n"
    "\n"
    "3- As a hostess on The Price Is Right";

    TXT_TEST_QUESTION2 = 
    "Which of these popular catchphrases did NOT belong to Chiquito de la Calzada's legendary repertoire?"
    "\n"
    "\n"
    "\n"
    "1- We've triumphed like Coca-Cola\n"
    "\n"
    "2- Fistro, sinner of the prairie!\n"
    "\n"
    "3- You get it, let's attack!";


    TXT_TEST_QUESTION3 = 
    "Why did Italian singer Sabrina Salerno go down in Spanish TV history in the 80s?"
    "\n"
    "\n"
    "\n"
    "1- She had a fling with a TVE host.\n"
    "\n"
    "2- She won Eurovision in 1987.\n"
    "\n"
    "3- Her breast popped out while singing.";

    TXT_TEST_QUESTION4 = 
    "Which actress became world-famous for running down a beach in a red swimsuit?"
    "\n"
    "\n"
    "\n"
    "1- Sharon Stone.\n"
    "\n"
    "2- Pamela Anderson.\n"
    "\n"
    "3- Julia Roberts.";


    TXT_TEST_QUESTION5 = 
    "Ana Torroja lent her voice to one of Spain's biggest bands of the 80s and 90s. Which band was it?"
    "\n"
    "\n"
    "\n"
    "1- Mecano.\n"
    "\n"
    "2- Olé Olé.\n"
    "\n"
    "3- La Unión.";

    TXT_TEST_QUESTION6 = 
    "Michael Knight fought crime alongside a car that could talk, think, and drive itself. What was that legendary car called?"
    "\n"
    "\n"
    "\n"
    "1- Optimus Prime.\n"
    "\n"
    "2- Lightning McQueen.\n"
    "\n"
    "3- KITT.";

    TXT_TEST_QUESTION7 = 
    "Every night she handed out millions of pesetas on Telecupón with an unmistakable smile. Who was that legendary host?"
    "\n"
    "\n"
    "\n"
    "1- Concha Velasco.\n"
    "\n"
    "2- Carmen Sevilla.\n"
    "\n"
    "3- Ana Obregón.";

    TXT_TEST_QUESTION8 = 
    "If you grew up in the 90s, this one should be a no-brainer... who was the Prince of Bel-Air?"
    "\n"
    "\n"
    "\n"
    "\n"
    "1- Will Smith.\n"
    "\n"
    "2- Eddie Murphy.\n"
    "\n"
    "3- Wesley Snipes.";

    TXT_TEST_QUESTION9 = 
    "In 1992, Spain became the center of the world's attention thanks to the Barcelona Olympic Games. What was the friendly mascot designed by Javier Mariscal called?"
    "\n"
    "\n"
    "1- Naranjito.\n"
    "\n"
    "2- Curro.\n"
    "\n"
    "3- Cobi.";


    TXT_TEST_QUESTION10 = 
    "Before viral videos existed, half the country cracked up watching Japanese contestants fall down impossible slopes. What was that show called?"
    "\n"
    "\n"
    "\n"
    "1- The Great Game of the Goose.\n"
    "\n"
    "2- Endurance.\n"
    "\n"
    "3- Waku Waku";

    TXT_MENUEXIT = "Thank you for playing DECKTIME.\n"
               "\n"
               "We hope you enjoyed the game.\n"
               "\n"
               "See you next time!";

}
}