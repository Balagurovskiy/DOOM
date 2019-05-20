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
    while(!player.exit_doom) {
        // SDL_FillRect(surface, NULL, 0x000000);

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
//     xy q = intersect(new_xy(-0.0,-1.0), new_xy(-3.0,-15.0), new_xy(-5.0,0.0), new_xy(-0.0,-5.0));
//     printf("%f  %f ----- (%d)\n\n", q.x,q.y,point_is_on_line(q, new_xy(-5.0,0.0), new_xy(-0.0,-5.0)));

//     q = intersect(new_xy(-3.0,-1.0), new_xy(-1.0,-3.0), new_xy(-5.0,0.0), new_xy(-0.0,-5.0));
//     printf("%f  %f ----- (%d)\n\n", q.x,q.y,point_is_on_line(q, new_xy(-5.0,0.0), new_xy(-0.0,-5.0)));

//     q = intersect(new_xy(0.0,0.0), new_xy(-1.0,-3.0), new_xy(0.0,0.0), new_xy(-5.0,-5.0));
//     printf("%f  %f ----- (%d)\n\n", q.x,q.y,point_is_on_line(q, new_xy(0.0,0.0), new_xy(-5.0,-5.0)));

// printf("-----  %d  -------\n", point_is_on_line(new_xy(-9.441002, 2.360250), new_xy(-0.000000, 0.000000), new_xy(-20.000000, 5.000000)));
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

//////BLACK SCREEN ON SECTOR EDGE
 
