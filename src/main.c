//#include <gmpxx.h>
#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "render.h"
#include "parser.h"



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
    if (t)
    {
        SDL_FreeSurface(t->ceiltexture);
        SDL_FreeSurface(t->floortexture);
        SDL_FreeSurface(t->uppertextures);
        SDL_FreeSurface(t->lowertextures);

        SDL_FreeSurface(t->active_object);
        SDL_FreeSurface(t->passive_object);
    }
}

void change_level(level_s *lvl, player *p)
{
    int j;
    int next_start;
    float angle;
    char *next_lvl_temp;
    t_map *map_temp;

    j = 3;
    while(j--)
    {
        if(p->sector == lvl->end[j] && lvl->next_level[j])
        {
            next_start = lvl->start[j];
            angle = p->angle;
            next_lvl_temp = ft_strjoin(lvl->next_level[j], NULL);
            map_temp = get_map(next_lvl_temp);
            if (map_temp && next_start >= 0 && next_start < lvl->sectors_size)
            {
                free_level(lvl);
                *lvl = connect_level(map_temp);
                *p = init_player(angle, lvl->sector, next_start, lvl->sectors_size);
            }
            ft_memdel((void**)&next_lvl_temp);

        }
    }
}

void doom_init(SDL_Window *win, SDL_Surface *surface, char *file)
{
    player          player;
    level_s         lvl;

    lvl = connect_level(get_map(file));

    if (catch_exception(0))
        return ;
    player = init_player(0, lvl.sector, 0, lvl.sectors_size);
    while(!player.exit_doom) {

        if(lvl.sector[player.sector].object == 1 && player.action){
            lvl.texture.curr_object = lvl.texture.active_object;
            player.key = 1;
            printf("got KEY\n");
        }
        if(lvl.sector[player.sector].object == 2 && player.action && player.key){
             player.key = 0;
             lvl.sector[player.sector].object = 0;
             lvl.sector[2].floor = 2;
             lvl.sector[1].neighbors[1] = 2;
             // lvl.sector[2].neighbors[3] = 1;
        }

        render_screen(surface, &player, &lvl, 0);

        SDL_UpdateWindowSurface(win);
        events(lvl.sector, &player);
        SDL_Delay(10);
        change_level(&lvl, &player);
    }
    free_level(&lvl);
}

int main(int argc, char **argv)
{
    SDL_Window      *win;
    SDL_Surface     *surface;


    win = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           W, H, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(win);

    SDL_ShowCursor(SDL_DISABLE);
    ///argv checker; if no args play story mode
    doom_init(win, surface, argv[1]);

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return (0);
}


//TODO:
// -set map from file +++
// -make parser; +++
// -story;
// -change speed while ducking
// -ducking=0 if jump while ducking
// PLAYER ANGELS OF END AND START SECTOR BETTER BE THE SAME
// -------->parser seg fault : level tag validation+++; filled sectors validation (neighbor < sector size; neighbor vertex)
