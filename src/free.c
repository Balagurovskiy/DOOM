
#include "defines.h"
#include "doom.h"
#include "libft.h"

void free_level(level_s *level)
{
    int i;

    i = 0;
    free_texture_set(&(level->texture));
    if(level->sector)
    {
        while (i < level->sectors_size)
        {
            ft_memdel((void **)&(level->sector[i]).vertex);
            ft_memdel((void **)&(level->sector[i]).neighbors);
            i++;
        }
        ft_memdel((void **)&(level->sector));
    }
    i = 3;
    while(i--)
        ft_memdel((void **) &(level->next_level[i]));
}

void free_texture_set(texture_set_s *t)
{
    int i;

    if (t)
    {

        SDL_FreeSurface(t->ceiltexture);
        SDL_FreeSurface(t->floortexture);
        SDL_FreeSurface(t->uppertextures);
        SDL_FreeSurface(t->lowertextures);
        SDL_FreeSurface(t->sky);
        SDL_FreeSurface(t->door);
        i = 4;
        while(--i)
            SDL_FreeSurface(t->dec[i]);
        i = 6;
        while(--i)
            SDL_FreeSurface(t->key[i]);
        
        SDL_FreeSurface(t->active_object);
        SDL_FreeSurface(t->passive_object);
    }
}