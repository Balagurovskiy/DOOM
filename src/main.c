
#include "defines.h"
#include "doom.h"
#include "render.h"

void safe_free(void *free_me)
{
    if (free_me != NULL)
        free(free_me);
}
void free_sector(sectors *sct, texture_set_s *t, player *p)
{
    int i;

    i = 0;
    free_texture_set(t);
    if(sct && p) {
        while (i < p->total_sectors) {
            safe_free((void *)(sct[i]).vertex);
            safe_free((void *)(sct[i]).neighbors);
            i++;
        }
        free(sct);
    }
}
void quit(sectors *sct, texture_set_s *t, player *p, level_s *l)
{
    free_sector(sct, t, p);
    safe_free((void *)l);
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


xy find_midd_point(sectors sct)
{
    xy start;
    int i;

    i = 0;
    start = new_xy(0.0, 0.0);
    while (i < sct.npoints)
    {
        start.x += sct.vertex[i].x;
        start.y += sct.vertex[i].y;
        i++;
    }
    start.x /= i;
    start.y /= i;
    return (start);
}

level_s *init_levels()
{
    level_s *levels;
    levels = (level_s *)malloc(sizeof(*levels) * 3);

    levels[0].init_sectors = (sectors *(*)())m1;
    levels[0].init_textures = (texture_set_s (*)())t1;
    levels[0].end[0] = 2;//if player sector == end you need to change level
    levels[0].end[1] = -1;
    levels[0].end[2] = -1;
    levels[0].next_level[0] = 1;//index of next level
    levels[0].next_level[1] = -1;
    levels[0].next_level[2] = -1;
    levels[0].start[0] = 0;// start sector in next level
    levels[0].start[1] = -1;
    levels[0].start[2] = -1;
    levels[0].sectors = 3;//total sectors in level

    levels[1].init_sectors = (sectors *(*)())m2;
    levels[1].init_textures = (texture_set_s (*)())t2;
    levels[1].end[0] = 1;
    levels[1].end[1] = 2;
    levels[1].end[2] = 3;
    levels[1].next_level[0] = 2;
    levels[1].next_level[1] = 2;
    levels[1].next_level[2] = 0;
    levels[1].start[0] = 0;
    levels[1].start[1] = 0;
    levels[1].start[2] = 1;
    levels[1].sectors = 4;

    levels[2].init_sectors = (sectors *(*)())m3;
    levels[2].init_textures = (texture_set_s (*)())t3;
    levels[2].end[0] = 1;
    levels[2].end[1] = -1;
    levels[2].end[2] = -1;
    levels[2].next_level[0] = 1;
    levels[2].next_level[1] = -1;
    levels[2].next_level[2] = -1;
    levels[2].start[0] = 0;
    levels[2].start[1] = -1;
    levels[2].start[2] = -1;
    levels[2].sectors = 2;
    return(levels);
}

void doom_init(SDL_Window *win, SDL_Surface *surface)
{
    player          player;
    sectors         *sector;
    texture_set_s   txt_set;
    level_s         *levels;
    int             i;

    i = 0;
    sector = NULL;

    levels = init_levels();
    sector = levels[i].init_sectors();
    if (sector == NULL)
        return ;
    txt_set = levels[i].init_textures();
    player = init_player(find_midd_point(sector[0]), 0, sector, 0, levels[i].sectors);

    //-------------------------------------------
    while(!player.exit_doom)
    {
        render_screen(surface, &player, sector, &txt_set);
        SDL_UpdateWindowSurface(win);
        events(sector, &player);

        int j = -1;
        while(++j < 3)
        {
            if(player.sector == levels[i].end[j])
            {
                int next_start = levels[i].start[j];
                i = levels[i].next_level[j];
                float angle = player.angle;

                free_sector(sector, &txt_set, &player);

                sector = levels[i].init_sectors();
                if (sector == NULL)
                    return ;
                txt_set = levels[i].init_textures();
                player = init_player(find_midd_point(sector[next_start]), angle, sector, next_start, levels[i].sectors);
            }
        }
        SDL_Delay(10);
    }
    quit(sector, &txt_set, &player, levels);
}

//void doom_init2(SDL_Window *win, SDL_Surface *surface)
//{
//    player          player;
//    sectors         *sector;
//    texture_set_s   txt_set;
//
//    sector = NULL;
//
//    sector = init_map(5);
//    if (sector == NULL)
//        return ;
//    txt_set = t1();
//    player = init_player(find_midd_point(sector[0]), 0, sector, 0, 5);
//    //-------------------------------------------
//    while(1)
//    {
//        render_screen(surface, &player, sector, &txt_set);
//        SDL_UpdateWindowSurface(win);
//        events(sector, &player);
//       ///////////////////////////////////////
////        if (IS_END(sector, player.sector))
////        {
////            int sectors_count = 4;
////            free(sector);
////            sector = init_map(sectors_count);printf("\nsector inited\n");
////            map_selector(&player, sector, &txt_set);
////        }
//        ///////////////////////////////////////
//        SDL_Delay(10);
//
//    }
//
//}
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

        //TODO
        // add collision while crouching under low cieling (+)
        // add collision when stend up after crouching (+)
        // add collision in corners (+)

//-------------------------------------------
//TODO:
// -set map from file
// -make parser;
// -story;
// PLAYER ANGELS OF END AND START SECTOR BETTER BE THE SAME
