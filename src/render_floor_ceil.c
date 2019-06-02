/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceil.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:23 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "parser.h"
#include "render_wall.h"

static void		switch_to_casual_ceil(t_screen *scrn, t_ceiling_floor *cf)
{
	float	rtx;
	float	rtz;

	rtx = cf->mapz * scrn->edge.pcos + cf->mapx * scrn->edge.psin;
	rtz = cf->mapz * scrn->edge.psin - cf->mapx * scrn->edge.pcos;
	cf->mapx = rtx + scrn->player->where.x;
	cf->mapz = rtz + scrn->player->where.y;
}

static void		init_f_c(t_screen *scrn, t_ceiling_floor *cf)
{
	float	lim;

	lim = ((H / 2 - cf->y) - scrn->player->yaw * H * V_FOV);
	cf->mapz = (cf->hei) * H * V_FOV / ((lim == 0.0) ? 1.0 : lim);
	cf->mapx = (cf->mapz) * (W / 2 - cf->x) / (W * H_FOV);
}

static void		put_txt_pixel(t_screen *scrn,
								t_ceiling_floor *cf,
								SDL_Surface *t)
{
	int	txtx;
	int	txtz;

	txtx = (int)(cf->mapx * 256) % t->w;
	txtz = (int)(cf->mapz * 256) % t->h;
	if (MAIN_IN && TXT_IN)
	{
		if (cf->with_shade)
			SCRN_PIX = fade_to_black(TXT_PIX, cf->z, BLACK_DIST + 50);
		else
			SCRN_PIX = TXT_PIX;
	}
}

static void		render_f_c_loop(t_screen *scrn,
							t_wall wall,
							t_heights heights,
							t_ceiling_floor *cf)
{
	SDL_Surface	*t;

	cf->with_shade = 0;
	cf->hei = cf->y < wall.cya ? heights.yceil : heights.yfloor;
	t = cf->y < wall.cya ? scrn->txt->sky : scrn->txt->floortexture;
	init_f_c(scrn, cf);
	if (IS_NOT_SKY)
	{
		switch_to_casual_ceil(scrn, cf);
		if (IS_CASUAL_CEIL)
			t = scrn->txt->ceiltexture;
		cf->with_shade = 1;
	}
	put_txt_pixel(scrn, cf, t);
}

void			render_floor_ceil(t_screen *scrn, t_wall wall,
									t_heights heights, int x)
{
	t_ceiling_floor	cf;

	cf.x = x;
	cf.y = scrn->ytop[cf.x] - 1;
	cf.z = wall.z;
	while (++cf.y <= scrn->ybottom[cf.x])
	{
		if (cf.y >= wall.cya && cf.y <= wall.cyb)
			cf.y = wall.cyb;
		else
			render_f_c_loop(scrn, wall, heights, &cf);
	}
}
