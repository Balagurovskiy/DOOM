

#include "defines.h"
//#include "doom.h"
//#include "render.h"
#include "render_wall.h"


wall_s wall_init(screen *scrn, heights_s *heights, int x, perspective_s persp)
{
    wall_s wall;

    /////////////////  TextureMapping
    float p1 = scrn->txt_data.u0 * (persp.x2 - x) * scrn->edge.t2.z;
    float p2 = scrn->txt_data.u1 * ((x - persp.x1) * scrn->edge.t1.z);
    float p = ((persp.x2 - x) * scrn->edge.t2.z + (x - persp.x1) * scrn->edge.t1.z);
    scrn->txt_data.txtx = (p1 + p2) / ((COMPARE(ABS(p), 0.0)) ? 1.0 : p);
    /////////////////
    ///////////////// ! NOT ! TextureMapping
    /* Calculate the Z coordinate for this point. (Only used for lighting.) */
    wall.z = scaler_next(&(heights->z));
    /////////////////
    /* Acquire the Y coordinates for our floor & ceiling for this X coordinate */
    wall.ya = scaler_next(&(heights->ya));
    wall.yb = scaler_next(&(heights->yb));
    /* CLAMP the ya & yb */
    wall.cya = CLAMP(wall.ya, scrn->ytop[x], scrn->ybottom[x]);
    wall.cyb = CLAMP(wall.yb, scrn->ytop[x], scrn->ybottom[x]);
    return (wall);
}

void set_neighbor_wall(wall_s *wall, screen *scrn, heights_s *heights, int x)
{
    wall->nya = scaler_next(&(heights->neighb_ya));
    wall->nyb = scaler_next(&(heights->neighb_yb));
    /* CLAMP ya2 & yb2 */
    wall->cnya = CLAMP(wall->nya, scrn->ytop[x], scrn->ybottom[x]);
    wall->cnyb = CLAMP(wall->nyb, scrn->ytop[x], scrn->ybottom[x]);
}

static void render_wall_line(screen *scrn, txt_line_s tl, scaler_set_s ss, SDL_Surface *t, int z)
{
    tl.scale_ty = scaler_init(ss, 0, (t->w - 1));
    textured_line(scrn, tl, t, z);
}

SDL_Surface *play_animation(SDL_Surface *anims[], int size)
{
    // printf("%d\n",ft_timer("#get"));
    static int entry = 0;
    static int back = 0;

    static int test = 0;
    if (ft_timer())
    {
        if (back)
            entry--;
        else
            entry++;
    }
    if (entry > size - 1)
    {
        entry = size - 2;
        back = 1;
    }
    if (entry < 0)
    {
        entry = 1;
        back = 0;
    }
    if (size <= 2)
        entry = 0;
    return (anims[entry]);
}

SDL_Surface *texture_switch(screen *scrn, int s)
{
    if (SECT_NOW->npoints < s)
    {
        if (SECT_NOW->object == 1)
            return (scrn->txt->door);
        if (SECT_NOW->object == 2)
            return (scrn->txt->dec[0]);
        if (SECT_NOW->object == 3)
            return (scrn->txt->dec[1]);
        if (SECT_NOW->object == 4)
            return (scrn->txt->dec[2]);
        if (SECT_NOW->object == 5)
            return (scrn->txt->dec[3]);
        if (SECT_NOW->object == 6)
            return (scrn->txt->dec[4]);
        if (SECT_NOW->object == 7)
            return (play_animation(scrn->txt->key, 6));
        if (SECT_NOW->object == 8)
            return (scrn->txt->key[6]);
    }
    return (scrn->txt->uppertextures);
}

void render_the_wall(screen *scrn, perspective_s perspect, heights_s heights, int s)
{
    wall_s wall;
    int x;

    x = heights.beginx;
    // printf("%f -> %f | ", heights.beginx,heights.endx);
    while (++x <= heights.endx)
    {
        wall = wall_init(scrn, &heights, x, perspect);
        /////////////////  TextureMapping
        // Texture-mapping for floors and ceilings is not very optimal in my program.
        // I'm converting each screen-pixel into map-coordinates by doing the perspect
        // transformation in reverse, and using these map-coordinates as indexes into texture.
        // This involves a few division calculations _per_ pixel, and would have been way
        // too slow for the platforms targeted by Doom and Duke3D.
        // In any case, there's no neat way to do it.
        // It is why the SNES port of Doom didn't do floor & ceiling textures at all.
        /////////////////
        if(SECT_NOW->npoints > s)
            render_floor_ceil(scrn, wall, heights, x);
        ///////////////// ELSE
        /* Render ceiling: everything above this sector's ceiling height. */
//        shaded_line(scrn->surface, x, scrn->ytop[x], wall.cya - 1, 0x111111, 0x222222, 0x111111);
        /* Render floor: everything below this sector's floor height. */
//        shaded_line(scrn->surface, x, wall.cyb + 1, scrn->ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);
        /////////////////

        /* Is there another sector behind this edge? */
        if (HAS_NGHBR_NOW(s))
        {
            /* Same for _their_ floor and ceiling */
            set_neighbor_wall(&wall, scrn, &heights, x);
            /* If our ceiling is higher than their ceiling, render_towards upper wall */
            ///////////////// TextureMapping
            render_wall_line(scrn,
                             set_textured_line(x, wall.cya, (wall.cnya - 1)),
                             set_scaler(wall.ya, wall.cya, wall.yb),
                             scrn->txt->uppertextures, wall.z);
            ///////////////// ELSE
//            shaded_line(scrn->surface, x, wall.cya, wall.cnya - 1, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R1(wall.z), 0);
            /////////////////
            scrn->ytop[x] = CLAMP(MAX(wall.cya, wall.cnya), scrn->ytop[x], H - 1);

            // If our floor is lower than their floor, render_towards bottom wall
            ///////////////// TextureMapping
            //((SECT_NOW->object)?  curr_object
            render_wall_line(scrn,
                             set_textured_line(x, (wall.cnyb + 1), wall.cyb),
                             set_scaler(wall.ya, (wall.cnyb + 1), wall.yb),
                             scrn->txt->lowertextures, wall.z);
                             // scrn->txt->lowertextures, wall.z);
            // ((scrn->sector[NGHBR_NOW(s)].object)? scrn->txt->curr_object : scrn->txt->lowertextures), wall.z);

            ///////////////// ELSE
//            shaded_line(scrn->surface, x, wall.cnyb + 1, wall.cyb, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R2(wall.z), 0);
            /////////////////
            scrn->ybottom[x] = CLAMP(MIN(wall.cyb, wall.cnyb), 0, scrn->ybottom[x]);
        } else {
            /* There's no neighbor. Render wall. */
            ///////////////// TextureMapping
            render_wall_line(scrn,
                             set_textured_line(x, wall.cya, wall.cyb),
                             set_scaler(wall.ya, wall.cya, wall.yb),
                             texture_switch(scrn, s), wall.z);
            ///////////////// ELSE
//            shaded_line(scrn->surface, x, wall.cya, wall.cyb, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R(wall.z), 0);
            /////////////////
        }
    }
}


