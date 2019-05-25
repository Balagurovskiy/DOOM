#include "defines.h"
#include "doom.h"
#include "render.h"

void shaded_line(SDL_Surface *surface, int x, int y1, int y2, int top, int middle, int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = CLAMP(y1, 0, H-1);
    y2 = CLAMP(y2, 0, H-1);
    if(y2 == y1)
        pix[y1 * W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1 * W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2 * W+x] = bottom;
    }
}

txt_line_s set_textured_line(int x, int y1, int y2)
{
    txt_line_s tl;

    tl.x = x;
    tl.y1 = y1;
    tl.y2 = y2;
    return (tl);
}

int		fade_to_black(int color, double current, double max)
{
    double  rgb[3];
    int     i;

    if (current < 0)
        return (current);
    if (current >= max)
        return (0x0);
    rgb[0] = color & 255;
    rgb[1] = (color >> 8) & 255;
    rgb[2] = (color >> 16) & 255;
    i = 3;
    while(i--)
        rgb[i] *= (max - (current - 15)) / max;
    return (rgb[0] + ((int)rgb[1] << 8) + (((int)rgb[2]) << 16));
}

void textured_line(screen *scrn, txt_line_s tl, SDL_Surface *t, int z)
{
    int y;
    int *pixels;
    int txtz;
    int txtx;

    pixels = (int*) scrn->surface->pixels;
    tl.y1 = CLAMP(tl.y1, 0, H - 1);
    tl.y2 = CLAMP(tl.y2, 0, H - 1);
    pixels += tl.y1 * W + tl.x;
    y = tl.y1;
    while(y <= tl.y2)
    {
        txtz = scaler_next(&(tl.scale_ty)) % t->h;
        txtx = scrn->txt_data.txtx % t->w;

         if(TXT_IN && TXT_PIX != 0x0)
            *pixels = fade_to_black(TXT_PIX, z, 120);
        pixels += W;
        ++y;
    }
}

