
#include "defines.h"
#include "doom.h"
#include "parser.h"
#include "render_wall.h"

// void  relative_map_coordinates_to_absolute(screen *s, float *x, float *z)
// {
//     float rtx;
//     float rtz;

//     rtx = (*z) * s->edge.pcos + (*x) * s->edge.psin;
//     rtz = (*z) * s->edge.psin - (*x) * s->edge.pcos;
//     *x = rtx + s->player->where.x;
//     *z = rtz + s->player->where.y;
// }

// void ceiling_floor_screen_coords_to_map(screen *scrn, int sx, int sy, ceiling_floor_s *cf)
// {
//     float lim;

//     lim = ((H / 2 - (sy)) - scrn->player->yaw * H * V_FOV);
//     cf->mapz = (cf->hei) * H * V_FOV / ((lim == 0.0) ? 1.0 : lim);
//     cf->mapx = (cf->mapz) * (W / 2 - (sx)) / (W * H_FOV);
//     relative_map_coordinates_to_absolute(scrn, &(cf->mapx), &(cf->mapz));
// }

// void render_floor_ceil(screen *scrn, wall_s wall, heights_s heights, int x)
// {
//     int y;
//     ceiling_floor_s cf;
//     int txtx;
//     int txtz;
//     SDL_Surface *t;

//     y = scrn->ytop[x] - 1;
//     while(++y <= scrn->ybottom[x])
//     {
//         if(y >= wall.cya && y <= wall.cyb)
//             y = wall.cyb;//continue;
//         else
//         {
//         cf.hei = y < wall.cya ? heights.yceil : heights.yfloor;
//         ceiling_floor_screen_coords_to_map(scrn, x, y, &cf);
//         t = y < wall.cya ? scrn->txt->ceiltexture : scrn->txt->floortexture;
//         txtx = (int)(cf.mapx * 256) % t->w;//256
//         txtz = (int)(cf.mapz * 256) % t->h;
//         if (MAIN_IN && TXT_IN)
//             SCRN_PIX = fade_to_black(TXT_PIX , wall.z, 120);
//     }
// //        ((int*)scrn->surface->pixels)[y * W + x] =
// //                ((int*)t->pixels)[scrn->txt->size * txtz + txtx];
//     }
// }


int null_check(screen *scrn)
{
	if (scrn)
		if (scrn->txt)
			if(scrn->txt->sky ||
				scrn->txt->floortexture ||
				scrn->txt->ceiltexture)
				return (0);
	catch_exception(1);
	return (1);
}

#include "unistd.h"
void render_floor_ceil(screen *scrn, wall_s wall, heights_s heights, int x)
{
    int y;
    ceiling_floor_s cf;
    int txtx;
    int txtz;
    SDL_Surface *t;

	if (null_check(scrn))
		return ;

    y = scrn->ytop[x] - 1;
    while(++y <= scrn->ybottom[x])
    {

        if(y >= wall.cya && y <= wall.cyb)
            y = wall.cyb;//continue;
        else
        {

            cf.hei = y < wall.cya ? heights.yceil : heights.yfloor;
            t = y < wall.cya ? scrn->txt->sky : scrn->txt->floortexture;

            int with_shade;

            with_shade = 0;

            float lim;
            lim = ((H / 2 - (y)) - scrn->player->yaw * H * V_FOV);
            cf.mapz = (cf.hei) * H * V_FOV / ((lim == 0.0) ? 1.0 : lim);
            cf.mapx = (cf.mapz) * (W / 2 - (x)) / (W * H_FOV);

            if (y >= wall.cya || (heights.yceil + scrn->player->where.z <= 16))
            {
                float rtx;
                float rtz;

                rtx = cf.mapz * scrn->edge.pcos + cf.mapx * scrn->edge.psin;
                rtz = cf.mapz * scrn->edge.psin - cf.mapx * scrn->edge.pcos;
                cf.mapx = rtx + scrn->player->where.x;
                cf.mapz = rtz + scrn->player->where.y;
                if (heights.yceil + scrn->player->where.z <= 16 && y < wall.cya)
                    t = scrn->txt->ceiltexture;
                with_shade = 1;
            }
            txtx = (int)(cf.mapx * 256) % t->w;
            txtz = (int)(cf.mapz * 256) % t->h;
            if (MAIN_IN && TXT_IN) {
                if (with_shade)
                    SCRN_PIX = fade_to_black(TXT_PIX, wall.z, 140);
                else
                    SCRN_PIX = TXT_PIX;
            }
        }
//
    }
}