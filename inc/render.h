/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:38 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include "defines.h"
# include "doom.h"
# include "render_scaler.h"

# define MAX_SURF_SIZE scrn->surface->w * scrn->surface->h * 3
# define MAIN_IS_LESS MAX_SURF_SIZE > (cf->y * W + cf->x)
# define MAIN_IS_MORE_0 0 <= (cf->y * W + cf->x)
# define MAIN_IN (MAIN_IS_LESS && MAIN_IS_MORE_0)

# define TXT_IS_LESS (t->w * t->h * 3) > (t->w * txtz + txtx)
# define TXT_IS_MORE_0 (0 <= (t->w * txtz + txtx))
# define TXT_IN (TXT_IS_LESS && TXT_IS_MORE_0)

# define SCRN_PIX ((int*)scrn->surface->pixels)[cf->y * W + cf->x]
# define TXT_PIX ((int*)t->pixels)[t->w * txtz + txtx]

# define T1X scrn->edge.t1.x
# define T2X scrn->edge.t2.x
# define T1Z scrn->edge.t1.z
# define T2Z scrn->edge.t2.z
# define ORG1X scrn->txt_data.org1.x
# define ORG2X scrn->txt_data.org2.x
# define ORG1Y scrn->txt_data.org1.y
# define ORG2Y scrn->txt_data.org2.y
# define TXTW scrn->txt->uppertextures->w

# define IS_ABOVE_SKY (heights.yceil + scrn->player->where.z) <= 30
# define IS_NOT_SKY IS_ABOVE_SKY || (cf->y >= wall.cya)
# define IS_CASUAL_CEIL IS_ABOVE_SKY && cf->y < wall.cya


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

SDL_Surface		*play_animation(SDL_Surface *anims[], int size);
//render_scaler.c
//scaler_s scaler_init(int a, int b, int c, int d, int f);
//int scaler_next(scaler_s *s);
#endif
