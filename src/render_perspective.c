
#include "defines.h"
#include "doom.h"
#include "render.h"

static float get_scale(float z, char side)
{
    float fside;

    if (side == 'y')
        fside = H * V_FOV;
    if (side == 'x')
        fside = W * H_FOV;
    return (fside / z);
}

perspective_s perspective_init(edge_s edge)
{
    perspective_s perspect;

    perspect.scale1.x = get_scale(edge.t1.z, 'x');
    perspect.scale1.y = get_scale(edge.t1.z, 'y');
    perspect.x1 = W / 2 + (int)(-edge.t1.x * perspect.scale1.x);
    perspect.scale2.x = get_scale(edge.t2.z, 'x');
    perspect.scale2.y  = get_scale(edge.t2.z, 'y');
    perspect.x2 = W / 2 + (int)(-edge.t2.x * perspect.scale2.x);
    return (perspect);
}