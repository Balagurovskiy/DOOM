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

typedef struct		s_item
{
	int		sectorno;
	float	sx1;
	float	sx2;
}					t_item;

typedef struct		s_edge
{
	t_xy		v1;
	t_xy		v2;

	float		pcos;
	float		psin;

	t_xyz		t1;
	t_xyz		t2;
}					t_edge;

typedef struct		s_txt_data
{
	int		u0;
	int		u1;

	t_xy	org1;
	t_xy	org2;

	int		txtx;
}					t_txt_data;

typedef struct		s_screen
{
	t_item			queue[MAX_QUE];
	t_item			*head;
	t_item			*tail;
	t_item			now;

	int				ytop[W];
	int				ybottom[W];

	t_player		*player;
	t_sectors		*sector;
	SDL_Surface		*surface;

	t_texture_set	*txt;
	t_txt_data		txt_data;

	t_edge			edge;
}					t_screen;

typedef struct		s_txt_line
{
	int				x;
	int				y1;
	int				y2;
	t_scaler		scale_ty;
}					t_txt_line;

typedef struct		s_perspective
{
	t_xy	scale1;
	t_xy	scale2;

	float	x1;
	float	x2;
}					t_perspective;

void				render_towards(t_screen *scrn);

t_txt_line			set_textured_line(int x, int y1, int y2);
void				textured_line(t_screen *scrn,
							t_txt_line tl, SDL_Surface *t, int z);

t_perspective		perspective_init(t_edge edge);

void				view_intersection_with_wall(t_screen *scrn);

SDL_Surface			*play_animation(SDL_Surface *anims[], int size);

#endif
