//#include <gmpxx.h>
#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "render.h"
#include "parser.h"

void doom_init(SDL_Window *win, SDL_Surface *surface, char *file)
{
    player          player;
    level_s         lvl;

    lvl = connect_level(get_map(file));

    if (catch_exception(0))
        return ;
    player = init_player(0, lvl.sector, 0, lvl.sectors_size);
// lvl.sector[0].vertex[2].x = 0.5;
// lvl.sector[1].vertex[1].x = 0.5;
    while(!player.exit_doom) {


        action_controller(&player, &lvl, file);
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
