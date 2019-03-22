
#include "defines.h"
#include "doom.h"
#include "render_wall.h"

void  relative_map_coordinates_to_absolute(screen *s, float *x, float *z)
{
    do {
        float rtx = (*z) * s->edge.pcos + (*x) * s->edge.psin;
        float rtz = (*z) * s->edge.psin - (*x) * s->edge.pcos;
        *x = rtx + s->player->where.x;
        *z = rtz + s->player->where.y;
    } while (0);
}

void ceiling_floor_screen_coords_to_map(screen *scrn, float mapY, int screenX, int screenY, float *x,
                                        float *z){
    do {
        *z = (mapY) * H * V_FOV / ((H / 2 - (screenY)) - scrn->player->yaw * H * V_FOV);
        *x = (*z) * (W / 2 - (screenX)) / (W * H_FOV);
        relative_map_coordinates_to_absolute(scrn, x, z);
    } while (0);
}

void render_floor_ceil(screen *scrn, wall_s wall, heights_s heights, int x)
{
    for(int y=scrn->ytop[x]; y<=scrn->ybottom[x]; ++y)
    {
        if(y >= wall.cya && y <= wall.cyb)
        {
            y = wall.cyb;
            continue;
        }
        float hei = y < wall.cya ? heights.yceil : heights.yfloor;
        float mapx, mapz;
        ceiling_floor_screen_coords_to_map(scrn, hei, x, y, &mapx, &mapz);
        int txtx = (mapx * 256);
        int txtz = (mapz * 256);
        SDL_Surface *t = y < wall.cya ? scrn->txt->ceiltexture : scrn->txt->floortexture;
        ((int*)scrn->surface->pixels)[y*W+x] = ((int*)t->pixels)[(scrn->txt->size * (txtz % scrn->txt->size) + (txtx % scrn->txt->size))];
    }
}