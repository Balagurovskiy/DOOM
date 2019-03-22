#include "defines.h"
#include "doom.h"
#include "utils.h"

// INTERSECT_BOX: DeterMINe whether two 2D-boxes INTERSECT.
int intersect_box(xy xy0, xy xy1, xy xy2, xy xy3){
    int overlap_x;
    int overlap_y;

    overlap_x = OVERLAP(xy0.x, xy1.x, xy2.x, xy3.x);
    overlap_y = OVERLAP(xy0.y, xy1.y, xy2.y, xy3.y);
    return (overlap_x  && overlap_y);
}

int intersect_box_handle(xy p, xy d, xy* vert, int s){
    xy p_d;
    xy vert0;
    xy vert1;

    p_d.x = p.x + d.x;
    p_d.y = p.y + d.y;
    vert0.x = vert[s + 0].x;
    vert0.y = vert[s + 0].y;
    vert1.x = vert[s + 1].x;
    vert1.y = vert[s + 1].y;
    return (intersect_box(p, p_d, vert0, vert1));
}

// INTERSECT: Calculate the point of INTERSECTion between two lines.
xy intersect(xy xy1, xy xy2, xy xy3, xy xy4){
    float vxs_12;
    float vxs_34;
    float y0;
    float x0;
    float xy;

    vxs_12 = VXS(xy1.x, xy1.y, xy2.x, xy2.y);
    vxs_34= VXS(xy3.x, xy3.y, xy4.x, xy4.y);
    x0 = VXS(vxs_12, (xy1.x - xy2.x), vxs_34, (xy3.x - xy4.x));
    y0 = VXS(vxs_12, (xy1.y - xy2.y), vxs_34, (xy3.y - xy4.y));
    xy = VXS((xy1.x - xy2.x), (xy1.y - xy2.y),
            (xy3.x - xy4.x), (xy3.y - xy4.y));
    return (new_xy((x0 / xy), (y0 / xy)));
}

int intersert_circle_bound(xy line_p0, xy line_pn, xy center, float radius)
{
    line_p0.x -= center.x;
    line_p0.y -= center.y;
    line_pn.x -= center.x;
    line_pn.y -= center.y;

    float dx = line_pn.x - line_p0.x;
    float dy = line_pn.y - line_p0.y;

    float a_ = dx * dx + dy * dy;
    float b_ = 2.0 * (line_p0.x * dx + line_p0.y * dy);
    float c_ = line_p0.x * line_p0.x + line_p0.y * line_p0.y - radius * radius;

    if (-b_ < 0.0)
        return (c_ < 0.0);
    if (-b_ < (2.0 * a_))
        return ((4.0 * a_ * c_ - b_ * b_) < 0.0);
    return ((a_ + b_ + c_) < 0.0);
}