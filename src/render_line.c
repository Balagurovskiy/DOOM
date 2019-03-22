#include "defines.h"
#include "doom.h"
#include "render.h"

void line(SDL_Surface *surface, int x, int y1,int y2, int top,int middle,int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = CLAMP(y1, 0, H-1);
    y2 = CLAMP(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}


void line2(screen *scrn, int x, int y1,int y2, scaler_s ty,unsigned txtx, SDL_Surface *t)
{
    int y;
    int *pix = (int*) scrn->surface->pixels;
    y1 = CLAMP(y1, 0, H-1);
    y2 = CLAMP(y2, 0, H-1);
    pix += y1 * W + x;
    y = y1;
    while(y <= y2)
    {
        unsigned txty = scaler_next(&ty);
        *pix = ((int*)t->pixels)[(scrn->txt->size * (txty % scrn->txt->size) + (txtx % scrn->txt->size))];
        pix += W;
        ++y;
    }
}