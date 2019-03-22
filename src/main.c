
#include "defines.h"
#include "doom.h"
#include "render.h"


void    quit(){
    // UnloadData(sectors);
    // SDL_Quit();
    exit(0);
}

void sector_print(int NumSectors, sectors *sectors){
    int    i = 0;
    while (i < NumSectors)
    {
        printf("\n sector [%d] \n",i);
         
        int j = 0;
        while (j < sectors[i].npoints + 1)
        {
            printf(" x:%f y:%f [%d]  neighbors (%d)\n",sectors[i].vertex[j].x,sectors[i].vertex[j].y,j, sectors[i].neighbors[j]);
            j++;
        }
        i++;
    }
}

void doom_init(SDL_Window *win, SDL_Surface *surface)
{
    player          player;
    sectors         *sector;
    texture_set_s   txt_set;

    sector = NULL;
    //-------------------------------------------
    //TODO:
    // -set map from file
    // -make parser;
    sector = init_map(5);
    // sector_print(5, sector);
    txt_set = texture_init();
    player = init_player(new_xy(2.0, 5.0), 5, sector, 0, 5);
    //-------------------------------------------
    if (sector == NULL)
        return ;
    while(1)
    {
        render_screen(surface, &player, sector, &txt_set);
        SDL_UpdateWindowSurface(win);
        event(sector, &player);
        SDL_Delay(10);
    }

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
    quit();

    return 0;
}

        //TODO
        // add collision while crouching under low cieling (+)
        // add collision when stend up after crouching (+)
        // add collision in corners (-)
