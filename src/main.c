//#include <gmpxx.h>
#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "render.h"
#include "parser.h"

char *save_file(char *file)
{
    static char *save = NULL;

    if (ft_strequ(file, "#del"))
        ft_memdel((void**)&save);
    else if (!ft_strequ(file, "#get"))
    {
        ft_memdel((void**)&save);
        save = ft_strjoin(file, NULL);
    }
    return (save);
}

int ft_timer()
{
    static int oldtime = 0;
    static int newtime = 0;

    newtime = SDL_GetTicks();
    if (newtime > (oldtime + TIME_SPEED))
    {
         oldtime = newtime;
        return (1);
    }
    return (0);
}

void doom_init(SDL_Window *win, SDL_Surface *surface, char *file)
{
    player          player;
    level_s         lvl;



    music("#init");
    message("#init", NULL, NULL);
    lvl = connect_level(get_map(file));
    save_file(file);
    if (!catch_exception(0))
    {
        player = init_player(0, lvl.sector, 0, lvl.sectors_size);
        player.health = 3;


        while(!player.exit_doom && !catch_exception(0))
        {
            // SDL_FillRect(surface, NULL, 0x000000);
    
    /////ACTIONS
            action_controller(&player, &lvl, save_file("#get"));

            render_screen(surface, &player, &lvl, 0);

    /////DEATH HANDLE
            if (player.health == 0)
            {
                render_massage("You died :(((", surface);
                  SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                if (ft_str_contains(save_file("#get"), ".story\0"))
                    goto_level(&lvl, &player, "level/0000.story");
                else
                    goto_level(&lvl, &player, save_file("#get"));

                player.health = 3;
                player.key = 0;
                //player.where.z = -0.08;
            }
/////FONT TEST
            message(save_file("#get"), &player, surface);
            
            events(lvl.sector, &player);
            change_level(&lvl, &player);
            SDL_UpdateWindowSurface(win);
            SDL_Delay(10);
        }
    }
    free_level(&lvl);
    message("#del", NULL, NULL);
    music("#del");
    save_file("#del");

}

int main(int argc, char **argv)
{
    SDL_Window      *win;
    SDL_Surface     *surface;

    win = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           W, H, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(win);
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "0.5",
                             SDL_HINT_OVERRIDE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);
    TTF_Init();

    if (argc == 2 && ft_str_contains(argv[1], ".doom\0"))
        doom_init(win, surface, argv[1]);
    else
        doom_init(win, surface, "level/0000.story");
        

	SDL_FreeSurface(surface);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    return (0);
}


//TODO:
//floor_ceil - busss error
// PLAYER ANGELS OF END AND START SECTOR BETTER BE THE SAME

 
