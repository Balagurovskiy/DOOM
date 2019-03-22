
#include "defines.h"
#include "doom.h"
#include "render.h"
#include "utils.h"

static screen screen_init(SDL_Surface *surface,
                            player *player,
                            sectors *sector,
                            texture_set_s *t)
{
     screen scrn;
     unsigned int i;

     scrn.player = player;
     scrn.surface = surface;
     scrn.sector = sector;
     scrn.txt = t;
     scrn.head = scrn.queue;
     scrn.tail = scrn.queue;
     i = 0;
     while (i < W){
         scrn.ytop[i] = 0;
         scrn.ybottom[i] = H - 1;
         i++;
     }
     /* Begin whole-screen rendering from where the player is. */
     scrn.head->sectorno = player->sector;
     scrn.head->sx1 = 0;
     scrn.head->sx2 = W - 1;
     if(++scrn.head == (scrn.queue + MAX_QUE))
         scrn.head = scrn.queue;
     return (scrn);
}

void render_screen(SDL_Surface *srf, player *pl, sectors *sct, texture_set_s *t)
{
    screen scrn;
    unsigned int s;
    int renderedsectors[pl->num_sectors];

    scrn = screen_init(srf, pl, sct, t);
    s = 0;
    while (s < pl->num_sectors)
         renderedsectors[s++] = 0;
    while(scrn.head != scrn.tail)
    {
        /* Pick a sector & slice from scrn.queue to draw */
        scrn.now = *scrn.tail;
        if(++scrn.tail == scrn.queue +MAX_QUE)
            scrn.tail = scrn.queue;
        if(!(renderedsectors[scrn.now.sectorno] & 0x21)) // Odd = still rendering, 0x20 = give up
        {
            ++renderedsectors[scrn.now.sectorno];
            render_towards(&scrn);
            ++renderedsectors[scrn.now.sectorno];
        }
    }
}