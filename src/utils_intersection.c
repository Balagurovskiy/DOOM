#include "defines.h"
#include "doom.h"
#include "utils.h"

// INTERSECT_BOX: DeterMINe whether two 2D-boxes INTERSECT.
int intersect_box(xy xy0, xy xy1, xy xy2, xy xy3){
    int overlap_x;
    int overlap_y;

    overlap_x = OVERLAP(xy0.x, xy1.x, xy2.x, xy3.x);
    overlap_y = OVERLAP(xy0.y, xy1.y, xy2.y, xy3.y);
    return (overlap_x && overlap_y);
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

int point_is_on_line(xy point, xy l0, xy ln)
{
    xy vector_l;
    xy vector_p;
    float cross_prod;

    // printf("l: %f - %f ; %f - %f\n", l0.x , ln.x, l0.y , ln.y);
    // printf("l: %f ; %f \n", (ln.x - l0.x), (ln.y - l0.y));
    // vector_l = new_xy((l0.x - ln.x), (l0.y - ln.y));
    vector_l = new_xy((ln.x - l0.x), (ln.y - l0.y));

    // printf("l: %f - %f ; %f - %f\n", l0.x , point.x, l0.y, point.y);
    // printf("l: %f ; %f \n", (point.x - l0.x), (point.y - l0.y));
    vector_p = new_xy((point.x - l0.x), (point.y - l0.y));

    printf(" %f * %f - %f * %f\n", vector_l.x,vector_p.y,vector_p.x,vector_l.y);
    printf(" %f - %f\n", (vector_l.x * vector_p.y),(vector_p.x * vector_l.y));
    cross_prod = vector_l.x * vector_p.y - vector_p.x * vector_l.y;
    printf("result : %f\n", cross_prod);
     // cross_prod = (point.x - l0.x) * (ln.y - l0.y) - (ln.x - l0.x) * (point.y- l0.y);
    if (cross_prod > 0.0)
        return (1);
    else if (cross_prod < 0.0)
        return (-1);
    else
        return (0);

   
    // return ((int)cross_prod);
}

// INTERSECT: Calculate the point of INTERSECTion between two lines.
xy intersect(xy xy1, xy xy2, xy xy3, xy xy4){
    float vxs_12;
    float vxs_34;
    float y0;
    float x0;
    float xy;
// printf("INTER<<[%f ; %f]---[%f ; %f] X [%f ; %f]---[%f ; %f]\n", xy1.x, xy1.y, xy2.x,xy2.y,  xy3.x,xy3.y,  xy4.x,xy4.y);
    vxs_12 = VXS(xy1.x, xy1.y, xy2.x, xy2.y);
    vxs_34= VXS(xy3.x, xy3.y, xy4.x, xy4.y);
    x0 = VXS(vxs_12, (xy1.x - xy2.x), vxs_34, (xy3.x - xy4.x));
    y0 = VXS(vxs_12, (xy1.y - xy2.y), vxs_34, (xy3.y - xy4.y));
    xy = VXS((xy1.x - xy2.x), (xy1.y - xy2.y),
            (xy3.x - xy4.x), (xy3.y - xy4.y));
    xy = ((COMPARE(ABS(xy), 0.0)) ? 1.0 : xy);

    // printf(" INTER>> x:%f  y:%f | ",x0/xy,y0/xy);
    return (new_xy((x0 / xy), (y0 / xy)));
    // float temp;
    // if (xy1.x >= xy2.x)
    // {
    //     temp = xy2.x;
    //     xy2.x = xy1.x;
    //     xy1.x = temp;
    //     temp = xy2.y;
    //     xy2.y = xy1.y;
    //     xy1.y = temp;
    // }
    // if (xy3.x >= xy4.x)
    // {
    //     temp = xy4.x;
    //     xy4.x = xy3.x;
    //     xy3.x = temp;
    //     temp = xy4.y;
    //     xy4.y = xy3.y;
    //     xy3.y = temp;
    // }

    // float k1 = (xy2.y - xy1.y)/((COMPARE(ABS(xy2.x - xy1.x), 0.0)) ? 1.0 : (xy2.x - xy1.x));
    // float k2 = (xy4.y - xy3.y)/((COMPARE(ABS((xy4.x - xy3.x)), 0.0)) ? 1.0 : (xy4.x - xy3.x));
    // if (COMPARE(xy1.y, xy2.y))
    //     k1 = 0.0;
    // if (COMPARE(xy3.y, xy4.y))
    //     k2 = 0.0;
    // float b1 = xy1.y - k1 * xy1.x;
    // float b2 = xy3.y - k2 * xy3.x;

    // float x = (b2 - b1)/((COMPARE(ABS((k1 - k2)), 0.0)) ? 1.0 : (k1 - k2));
    // float y = k1 * x + b1;
    // return(new_xy(x , y));
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