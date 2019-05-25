
#include "defines.h"
#include "doom.h"
#include "parser.h"
#include "libft.h"

static void music_open()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        ft_putstr("EXCEPTION > music > Mix_OpenAudio\n");
        catch_exception(1);
    }
}

static Mix_Music *music_load(char *file)
{
    Mix_Music *song;

    song = Mix_LoadMUS(file);
    if (song == NULL)
    {
        ft_putstr("EXCEPTION > music > invalid file\n");
        catch_exception(1);
    }
    return (song);
}

void music(char *tag)
{
    static Mix_Music *song[3];
    static int mus_idx = 0;

    if (ft_strequ(tag, "#init"))
    {
        music_open();
        song[0] = music_load("music/s1.mp3");
        song[1] = music_load("music/s2.mp3");
        song[2] = music_load("music/s3.mp3");
    }
    if (ft_strequ(tag, "#del"))
    {
//        Mix_FreeMusic(song[0]);
//        Mix_FreeMusic(song[1]);
//        Mix_FreeMusic(song[2]);
//        Mix_CloseAudio();
    }
    if (ft_strequ(tag, "#play"))
    {
        Mix_PlayMusic(song[mus_idx], -1);
        Mix_VolumeMusic(10);
        mus_idx++;
        if (mus_idx >= 3)
            mus_idx = 0;
    }
}