

#ifndef RENDER_H
# define RENDER_H

# include "defines.h"
# include "doom.h"
# include "render_scaler.h"


# define MAIN_IN ((scrn->surface->w * scrn->surface->h * 3) > (y * W + x) && 0 <= (y * W + x))
# define TXT_IN ((t->w * t->h * 3) > (t->w * txtz + txtx) && 0 <= (t->w * txtz + txtx))

# define SCRN_PIX ((int*)scrn->surface->pixels)[y * W + x]
# define TXT_PIX ((int*)t->pixels)[t->w * txtz + txtx]


typedef struct  item
{
    int             sectorno;
    float             sx1;
    float             sx2;
}               item;

typedef  struct edge
{
    xy              v1;
    xy              v2;

    float           pcos;
    float           psin;

    xyz             t1;
    xyz             t2;
}               edge_s;

typedef struct  txt_data_s
{
     int            u0;
     int            u1;

     xy             org1;
     xy             org2;

     int            txtx;
}               txt_data_s;

typedef struct  screen
{
    item            queue[MAX_QUE];
    item            *head;
    item            *tail;
    item            now;

    int             ytop[W];
    int             ybottom[W];

    player          *player;
    sectors         *sector;
    SDL_Surface     *surface;
    int             isobj;

    texture_set_s   *txt;
    txt_data_s      txt_data;

    edge_s          edge;

}               screen;

typedef struct  line_s
{
    int x;
    int y1;
    int y2;
    int top;
    int middle;
    int bottom;
}               line_s;

typedef struct  txt_line_s
{
    int x;
    int y1;
    int y2;
    scaler_s scale_ty;
    SDL_Surface *texture;
}               txt_line_s;

typedef struct perspective
{
    xy scale1;
    xy scale2;

    float x1;
    float x2;
}               perspective_s;


//render.c
//void render_screen(SDL_Surface *srf, player *pl, level_s *lvl);

//render_towards.c
void render_towards(screen *scrn);


//render_heights.c
//heights_s heights_init(screen *scrn, perspective_s perspect, int s);

//render_line.c
void shaded_line(SDL_Surface *surface, int x, int y1, int y2, int top, int middle, int bottom);

txt_line_s set_textured_line(int x, int y1, int y2);
void textured_line(screen *scrn, txt_line_s tl, SDL_Surface *t, int z);



//render_perspective.c
perspective_s perspective_init(edge_s edge);

//render_wall_intersection.c
void view_intersection_with_wall(screen *scrn);


//render_scaler.c
//scaler_s scaler_init(int a, int b, int c, int d, int f);
//int scaler_next(scaler_s *s);
#endif
