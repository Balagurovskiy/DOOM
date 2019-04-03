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

void set_textured_line(txt_line_s *tl, int x, int y1, int y2)
{
    tl->x = x;
    tl->y1 = y1;
    tl->y2 = y2;
}

txt_line_s set_textured_line2(int x, int y1, int y2)
{
    txt_line_s tl;

    tl.x = x;
    tl.y1 = y1;
    tl.y2 = y2;
    return (tl);
}

void textured_line(screen *scrn, txt_line_s tl, SDL_Surface *t)
{
    int y;
    int *pixels;
    int txt_y;
    int txt_x;

    pixels = (int*) scrn->surface->pixels;
    tl.y1 = CLAMP(tl.y1, 0, H - 1);
    tl.y2 = CLAMP(tl.y2, 0, H - 1);
    pixels += tl.y1 * W + tl.x;
    y = tl.y1;
    while(y <= tl.y2)
    {
        txt_y = scaler_next(&(tl.scale_ty)) % scrn->txt->size;
        txt_x = scrn->txt_data.txtx % scrn->txt->size;
        *pixels = ((int*)t->pixels)[scrn->txt->size * txt_y + txt_x];
        pixels += W;
        ++y;
    }
}

