

#include "defines.h"
#include "doom.h"
#include "render.h"

static void init_texture_edges(screen *scrn)
{
    scrn->txt_data.org1.x = scrn->edge.t1.x;
    scrn->txt_data.org1.y = scrn->edge.t1.z;
    scrn->txt_data.org2.x = scrn->edge.t2.x;
    scrn->txt_data.org2.y = scrn->edge.t2.z;
}

static void switch_edges_to_intersections(screen *scrn, xy i1, xy i2)
{
    if (scrn->edge.t1.z < NEARZ )
    {
        if (i1.y > 0.0)
        {                
            scrn->edge.t1.x = i1.x;
            scrn->edge.t1.z = i1.y;
        }
        else
        {
            scrn->edge.t1.x = i2.x;
            scrn->edge.t1.z = i2.y;
        }
    }
}

static void switch_edges_to_intersections2(screen *scrn, xy i1, xy i2)
{
    if (scrn->edge.t2.z < NEARZ)
    {
        if (i1.y > 0.0)
        {
            scrn->edge.t2.x = i1.x;
            scrn->edge.t2.z = i1.y;
        }
        else
        {
            scrn->edge.t2.x = i2.x;
            scrn->edge.t2.z = i2.y;
        }
    }
}

static void texture_intersection(screen *scrn)
{
    if(ABS(T2X - T1X) > ABS(T2Z - T1Z))
    {
        scrn->txt_data.u0 = (T1X - ORG1X) * (TXTW - 1) / (ORG2X - ORG1X);
        scrn->txt_data.u1 = (T2X - ORG1X) * (TXTW - 1) / (ORG2X - ORG1X);
    }
    else
    {
        scrn->txt_data.u0 = (T1Z - ORG1Y) * (TXTW - 1) / (ORG2Y - ORG1Y);
        scrn->txt_data.u1 = (T2Z - ORG1Y) * (TXTW - 1) / (ORG2Y - ORG1Y);
    }
}

void view_intersection_with_wall(screen *scrn)
{
    xy i1;
    xy i2;
    // Find an intersetion between the wall and the approximate edges of player's view
    i1 = intersect(EDGE_T(scrn ->edge.t1), EDGE_T(scrn->edge.t2),
                   new_xy(-(NEAR_SIDE), NEARZ), new_xy(-FAR_SIDE, FARZ));
    i2 = intersect(EDGE_T(scrn->edge.t1), EDGE_T(scrn->edge.t2),
                   new_xy(NEAR_SIDE, NEARZ), new_xy(FAR_SIDE, FARZ));
    init_texture_edges(scrn);
    switch_edges_to_intersections(scrn, i1, i2);
    switch_edges_to_intersections2(scrn, i1, i2);
    texture_intersection(scrn);
}