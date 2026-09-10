#include "audio.h"


static bool soundEnabled = false;

/* Música actual */
static MIDI *current_music = NULL;

/* Efectos cargados */
static SAMPLE *sfx[SFX_COUNT];

/* -------------------------------------------------- */

void Sound_Init(void)
{
    
    int i;


    if (install_sound(DIGI_AUTODETECT,
                      MIDI_AUTODETECT,
                      NULL) != 0)
    {
        soundEnabled = false;
        return;
    }

    soundEnabled = true;
    for (i = 0; i < SFX_COUNT; i++)
        sfx[i] = NULL;

    /* Cargar efectos */

    sfx[SFX_SELECT] = load_sample("assets/sfx/input1.wav");
    sfx[SFX_SHUFFLE]   = load_sample("assets/sfx/shuffle.wav");
    sfx[SFX_OLDLAUGHT]   = load_sample("assets/sfx/laughtgr.wav");
    sfx[SFX_OLDI1]   = load_sample("assets/sfx/daold1.wav");
    sfx[SFX_OLDI2]   = load_sample("assets/sfx/daold2.wav");
    sfx[SFX_OLDI3]   = load_sample("assets/sfx/daold3.wav");
    sfx[SFX_GIRL1]   = load_sample("assets/sfx/dagirl1.wav");
    sfx[SFX_GIRL2]   = load_sample("assets/sfx/dagirl2.wav");
    sfx[SFX_GIRL2]   = load_sample("assets/sfx/dagirl3.wav");
}

/* -------------------------------------------------- */

void Sound_StopMusic(void)
{
    if (!soundEnabled) return;

    if (current_music)
    {
        stop_midi();
        destroy_midi(current_music);
        current_music = NULL;
    }
}

/* -------------------------------------------------- */

void Sound_PlayMusic(MusicID music)
{
    if (!soundEnabled) return;
    
    Sound_StopMusic();

    switch (music)
    {
        case MUSIC_TITLE:
            current_music = load_midi("assets/music/pastime.MID");
            break;

        case MUSIC_GAME:
            current_music = load_midi("assets/music/tourdion.mid");
            break;

        default:
            return;
    }

    if (current_music)
        play_midi(current_music, TRUE);
}

/* -------------------------------------------------- */

void Sound_PlaySfx(SfxID id)
{
    
    if (!soundEnabled) return;

    if (id < 0 || id >= SFX_COUNT)
        return;

    if (!sfx[id])
        return;

    play_sample(
        sfx[id],   /* sample */
        255,       /* volumen */
        128,       /* pan */
        1000,      /* frecuencia */
        FALSE      /* loop */
    );
}

/* -------------------------------------------------- */

void Sound_Shutdown(void)
{
    int i;

    if (!soundEnabled) return;
    
    Sound_StopMusic();

    for (i = 0; i < SFX_COUNT; i++)
    {
        if (sfx[i])
        {
            destroy_sample(sfx[i]);
            sfx[i] = NULL;
        }
    }

    remove_sound();
    soundEnabled = false;


}