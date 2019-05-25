

#ifndef RENDER_HEIGHTS_H
# define RENDER_HEIGHTS_H

#include "render.h"

typedef struct heights
{
    float yceil;
    float yfloor;
    float neighb_yceil;
    float neighb_yfloor;
    float beginx;
    float endx;

    scaler_s ya;
    scaler_s yb;
    scaler_s neighb_ya;
    scaler_s neighb_yb;
    scaler_s z;//shading only
}              heights_s;

heights_s heights_init(screen *scrn, perspective_s perspect, int s);

#endif