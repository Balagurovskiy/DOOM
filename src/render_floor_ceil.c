
#include "defines.h"
#include "doom.h"
#include "render_wall.h"

void  relative_map_coordinates_to_absolute(screen *s, float *x, float *z)
{
    float rtx;
    float rtz;

    rtx = (*z) * s->edge.pcos + (*x) * s->edge.psin;
    rtz = (*z) * s->edge.psin - (*x) * s->edge.pcos;
    *x = rtx + s->player->where.x;
    *z = rtz + s->player->where.y;
}

void ceiling_floor_screen_coords_to_map(screen *scrn, int sx, int sy, ceiling_floor_s *cf)
{
    float lim;

    lim = ((H / 2 - (sy)) - scrn->player->yaw * H * V_FOV);
    cf->mapz = (cf->hei) * H * V_FOV / ((lim == 0.0) ? 1.0 : lim);
    cf->mapx = (cf->mapz) * (W / 2 - (sx)) / (W * H_FOV);
    relative_map_coordinates_to_absolute(scrn, &(cf->mapx), &(cf->mapz));
}


void render_floor_ceil(screen *scrn, wall_s wall, heights_s heights, int x)
{
    int y;
    ceiling_floor_s cf;
    int txtx;
    int txtz;
    SDL_Surface *t;

    y = scrn->ytop[x] - 1;
    while(y++ <= scrn->ybottom[x])
    {
        if(y >= wall.cya && y <= wall.cyb)
            y = wall.cyb;//continue;
        cf.hei = y < wall.cya ? heights.yceil : heights.yfloor;
        ceiling_floor_screen_coords_to_map(scrn, x, y, &cf);
        t = y < wall.cya ? scrn->txt->ceiltexture : scrn->txt->floortexture;
        txtx = (int)(cf.mapx * 256) % t->w;//scrn->txt->size;
        txtz = (int)(cf.mapz * 256) % t->h;//scrn->txt->size;
        ((int*)scrn->surface->pixels)[y * W + x] =
                fade_to_black(((int*)t->pixels)[scrn->txt->size * txtz + txtx] , wall.z,160);
//        ((int*)scrn->surface->pixels)[y * W + x] =
//                ((int*)t->pixels)[scrn->txt->size * txtz + txtx];
    }
}