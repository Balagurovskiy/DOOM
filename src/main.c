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

int ft_timer(char *tag)
{
    static int oldtime = 0;
    static int newtime = 0;
    static int time = 0;

    if (!ft_strequ(tag, "#get"))
    {   
        oldtime = newtime;
        newtime = clock();
        time += (newtime - oldtime) / 1000;
        if (time > 1000)
            time = 0;
    }
    // if (time == 0)
    //     lvl.sector[0].floor--;
    return (time);
}

void doom_init(SDL_Window *win, SDL_Surface *surface, char *file)
{
    player          player;
    level_s         lvl;



    music("#init");
    massage("#init", NULL, NULL);
    lvl = connect_level(get_map(file));
    save_file(file);
    if (!catch_exception(0))
    {
        player = init_player(0, lvl.sector, 0, lvl.sectors_size);
        player.health = 3;

       
        while(!player.exit_doom && !catch_exception(0)) 
        {
            // SDL_FillRect(surface, NULL, 0x000000);
    ////CLOCK TEST
        ft_timer("B====D");
        // printf("%d\n",ft_timer("#get"));
            
    /////ACTIONS
            action_controller(&player, &lvl, save_file("#get"));


            render_screen(surface, &player, &lvl, 0);

   
    /////DEATH HANDLE
            if (player.health == 1){
                render_massage("You died :(((", surface);
                  SDL_UpdateWindowSurface(win);               
                SDL_Delay(2000);
                if (ft_str_contains(save_file("#get"), "level/sprite\0"))
                    goto_level(&lvl, &player, "level/map.doom");
                else
                    goto_level(&lvl, &player, save_file("#get"));
                
                player.health = 3;
                player.where.z = -0.08;
            }
/////FONT TEST  
            massage(save_file("#get"), &player, surface);

            SDL_UpdateWindowSurface(win);
            events(lvl.sector, &player);
            change_level(&lvl, &player);
            SDL_Delay(10);
        }
    }  
    free_level(&lvl);
    massage("#del", NULL, NULL);
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
    if (argc != 2)
        doom_init(win, surface, "story_0.map");
    else
        doom_init(win, surface, argv[1]);
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

 
