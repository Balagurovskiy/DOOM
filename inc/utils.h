

#ifndef UTILS_H
# define UTILS_H

typedef struct  xy
{
    float x;
    float y;
}               xy;

typedef struct  xyz
{
    float x;
    float y;
    float z;
}               xyz;

xy new_xy(float x, float y);
int equals_xy(xy a, xy b);
int equals_float(float a, float b);

xyz new_xyz(float x, float y, float z);

int point_is_on_line(xy point, xy l0, xy ln);

xy intersect(xy xy1, xy xy2, xy xy3, xy xy4);

int intersect_box(xy xy0, xy xy1, xy xy2, xy xy3);

int intersect_box_handle(xy p, xy d, xy* vert, int s);

float point_side(xy p, xy xy0, xy xy1);

float point_side_handle(xy p, xy d, xy* vert, int s);

int intersert_circle_bound(xy line_p0, xy line_pn, xy center, float radius);

#endif
