

#include "defines.h"
#include "doom.h"
#include "render.h"

void view_intersection_with_wall(screen *scrn)
{
    xy i1;
    xy i2;
    /////////////////TextureMapping
//             int u0;
//             int u1;
//             xy org1;
//             xy org2;
/////////////////
    if (scrn->edge.t1.z <= 0 || scrn->edge.t2.z <= 0) {
        // Find an intersetion between the wall and the approximate edges of player's view
        i1 = intersect(EDGE_T(scrn->edge.t1), EDGE_T(scrn->edge.t2),
                       new_xy(-NEAR_SIDE, NEARZ), new_xy(-FAR_SIDE, FARZ));
        i2 = intersect(EDGE_T(scrn->edge.t1), EDGE_T(scrn->edge.t2),
                       new_xy(NEAR_SIDE, NEARZ), new_xy(FAR_SIDE, FARZ));
/////////////////TextureMapping
//        scrn->txt_data.u0 = 0;
//        scrn->txt_data.u1 = 1023;
        scrn->txt_data.org1.x = scrn->edge.t1.x;
        scrn->txt_data.org1.y = scrn->edge.t1.z;
        scrn->txt_data.org2.x = scrn->edge.t2.x;
        scrn->txt_data.org2.y = scrn->edge.t2.z;
/////////////////
        if (scrn->edge.t1.z < NEARZ) {
            if (i1.y > 0) {
                scrn->edge.t1.x = i1.x;
                scrn->edge.t1.z = i1.y;
            } else {
                scrn->edge.t1.x = i2.x;
                scrn->edge.t1.z = i2.y;
            }
        }
        if (scrn->edge.t2.z < NEARZ) {
            if (i1.y > 0) {
                scrn->edge.t2.x = i1.x;
                scrn->edge.t2.z = i1.y;
            } else {
                scrn->edge.t2.x = i2.x;
                scrn->edge.t2.z = i2.y;
            }
        }
/////////////////TextureMapping
        if(ABS(scrn->edge.t2.x - scrn->edge.t1.x) > ABS(scrn->edge.t2.z - scrn->edge.t1.z)) {
            scrn->txt_data.u0 = (scrn->edge.t1.x - scrn->txt_data.org1.x) * (scrn->txt->size - 1) / (scrn->txt_data.org2.x - scrn->txt_data.org1.x);
            scrn->txt_data.u1 = (scrn->edge.t2.x - scrn->txt_data.org1.x) * (scrn->txt->size - 1) / (scrn->txt_data.org2.x - scrn->txt_data.org1.x);
        }else {
            scrn->txt_data.u0 = (scrn->edge.t1.z - scrn->txt_data.org1.y) * (scrn->txt->size - 1) / (scrn->txt_data.org2.y - scrn->txt_data.org1.y);
            scrn->txt_data.u1 = (scrn->edge.t2.z - scrn->txt_data.org1.y) * (scrn->txt->size - 1) / (scrn->txt_data.org2.y - scrn->txt_data.org1.y);
        }
/////////////////
    }
}