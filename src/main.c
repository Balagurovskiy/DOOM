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
void sector_init(sectors* s, int sx[], int sy[], int n[])
{
    int i = 0;

    s->neighbors = (int *)malloc((s->npoints + 1) * sizeof(*s->neighbors));
    s->vertex = (xy *)malloc((s->npoints + 1) * sizeof(*s->vertex));
    while (i < (s->npoints + 1)){
        s->vertex[i].x = sx[i];
        s->vertex[i].y = sy[i];
        s->neighbors[i] = n[i];
        i++;
    }
}
sectors* sprite_test() {
    sectors *sector;
    sectors *sect;

    sector = malloc(5 * sizeof(*sector));

    sect = &sector[0];
    sect->npoints = 2;
    sect->floor = 5;
    sect->ceil = 10;
    int sector0x[] = {1, 1, 1};
    int sector0y[] = {5, 10, 5};
    int neighbors0[] = {-1, -1, -1};
    sector_init(sect, sector0x, sector0y, neighbors0);
    sect = &sector[1];
    sect->npoints = 2;
    sect->floor = 9;
    sect->ceil = 12;
    int sector0x1[] = {11, 14, 5};
    int sector0y1[] = {1, 1, 2};
    int neighbors01[] = {-1, -1, -1};
    sector_init(sect, sector0x1, sector0y1, neighbors01);
    sect = &sector[2];
    sect->npoints = 2;
    sect->floor = 5;
    sect->ceil = 10;
    int sector0x12[] = {11, 12, 11};
    int sector0y12[] = {6, 13, 6};
    sector_init(sect, sector0x12, sector0x12, neighbors0);
    sect = &sector[3];
    sect->npoints = 2;
    sect->floor = 5;
    sect->ceil = 10;
    int sector0x3[] = {6, 6, 6};
    int sector0y3[] = {6, 6, 6};
    sector_init(sect, sector0x3, sector0y3, neighbors0);
    sect = &sector[4];
    sect->npoints = 2;
    sect->floor = 5;
    sect->ceil = 10;
    int sector0x4[] = {5,10, 5};
    int sector0y4[] = {13, 13, 13};
    sector_init(sect, sector0x4, sector0y4, neighbors0);
    return sector;
}
void doom_init(SDL_Window *win, SDL_Surface *surface)
{
    player          player;
    level_s         lvl;

    lvl = connect_level(get_map("map.doom"));
//
//    lvl.sector[5].npoints = 2;
//    lvl.sector[5].floor = 5;
//    lvl.sector[5].ceil = 10;
//    int sector0x1[] = {2, 3, 2};
//    int sector0y1[] = {10, 12, 10};
//    int neighbors01[] = {-1, -1, -1};
//    sector_init(&(lvl.sector[5]), sector0x1, sector0y1, neighbors01);

    if (catch_exception(0))
        return ;
    player = init_player(0, lvl.sector, 0, lvl.sectors_size);
    while(!player.exit_doom) {
    //if (player.sector == 1)
    //    sector[2].floor = 25;
    //else
    //    sector[2].floor = 8;



        render_screen(surface, &player, &lvl, 0);

        sectors *temp = lvl.sector;
        lvl.sector = sprite_test();
        render_screen(surface, &player, &lvl, 1);
        lvl.sector = temp;

        SDL_UpdateWindowSurface(win);
        events(lvl.sector, &player);
        SDL_Delay(10);
        change_level(&lvl, &player);
    }
    free_level(&lvl);
}

int main()
{
    SDL_Window      *win;
    SDL_Surface     *surface;


    win = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           W, H, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(win);

    SDL_ShowCursor(SDL_DISABLE);
    doom_init(win, surface);

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
