
#ifndef RENDER_WALL_H
# define RENDER_WALL_H

# include "render.h"
# include "render_heights.h"


typedef struct ceiling_floor
{
    float hei;
    float mapx;
    float mapz;
    int with_shade;
    int x;
    int y;
    int z;
}              ceiling_floor_s;

typedef struct wall
{
    int z;
    int ya;
    int yb;
    int cya;
    int cyb;
    int nya;
    int nyb;
    int cnya;
    int cnyb;
}              wall_s;

int		fade_to_black(int col, double curr, double max);

//render_wall.c
void render_the_wall(screen *scrn, perspective_s perspect, heights_s heights, int s);
perspective_s perspective_init(edge_s edge);
void view_intersection_with_wall(screen *scrn);
//render_floor_ceil.c
void render_floor_ceil(screen *scrn, wall_s wall, heights_s heights, int x);

#endif