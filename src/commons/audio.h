#ifndef AUDIO_H
#define AUDIO_H

#include <allegro.h>
#include <stdbool.h>

/* Música */
typedef enum
{
    MUSIC_NONE,
    MUSIC_TITLE,
    MUSIC_GAME
    
} MusicID;

/* Efectos */
typedef enum
{
    SFX_SELECT,
    SFX_SHUFFLE,
    SFX_OLDLAUGHT,
    SFX_OLDI1,
    SFX_OLDI2,
    SFX_OLDI3,
    SFX_GIRLLAUGHT,
    SFX_GIRL1,
    SFX_GIRL2,
    SFX_GIRL3,
    SFX_COUNT
} SfxID;

void Sound_Init(void);
void Sound_Shutdown(void);

void Sound_PlayMusic(MusicID music);
void Sound_StopMusic(void);

void Sound_PlaySfx(SfxID sfx);

#endif


/*"Tourdion" (Danza tradicional francesa, Anónima, S. XVI).
Arreglo e instrumentación MIDI de Dominio Público.

Pastime with good company
 ENRIQUE VIII


"Ay Linda Amiga" (Anónimo, Siglo XVI)

"Saltarello" (Anónimo, Siglo XIV)

"Greensleeves" / "What Child Is This" (Tradicional Inglesa, Siglo XVI)

*/