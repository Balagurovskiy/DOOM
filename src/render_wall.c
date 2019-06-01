/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:13:06 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "render_wall.h"

wall_s			wall_init(screen *scrn,
							heights_s *heights,
							int x,
							perspective_s persp)
{
	wall_s	wall;
	float	p1;
	float	p2;
	float	p;

	p1 = scrn->txt_data.u0 * (persp.x2 - x) * scrn->edge.t2.z;
	p2 = scrn->txt_data.u1 * ((x - persp.x1) * scrn->edge.t1.z);
	p = ((persp.x2 - x) * scrn->edge.t2.z + (x - persp.x1) * scrn->edge.t1.z);
	scrn->txt_data.txtx = (p1 + p2) / ((COMPARE(ABS(p), 0.0)) ? 1.0 : p);
	wall.z = scaler_next(&(heights->z));
	wall.ya = scaler_next(&(heights->ya));
	wall.yb = scaler_next(&(heights->yb));
	wall.cya = CLAMP(wall.ya, scrn->ytop[x], scrn->ybottom[x]);
	wall.cyb = CLAMP(wall.yb, scrn->ytop[x], scrn->ybottom[x]);
	return (wall);
}

static void		render_wall_line(screen *scrn,
								txt_line_s tl,
								scaler_set_s ss,
								int z)
{
	tl.scale_ty = scaler_init(ss, 0, (scrn->txt->current->w - 1));
	textured_line(scrn, tl, scrn->txt->current, z);
}

void			set_neighbor_wall(wall_s *wall,
				screen *scrn,
				heights_s *heights,
				int x)
{
	wall->nya = scaler_next(&(heights->neighb_ya));
	wall->nyb = scaler_next(&(heights->neighb_yb));
	wall->cnya = CLAMP(wall->nya, scrn->ytop[x], scrn->ybottom[x]);
	wall->cnyb = CLAMP(wall->nyb, scrn->ytop[x], scrn->ybottom[x]);
	scrn->txt->current = scrn->txt->uppertextures;
	render_wall_line(scrn,
					set_textured_line(x, wall->cya, (wall->cnya - 1)),
					set_scaler(wall->ya, wall->cya, wall->yb),
					wall->z);
	scrn->ytop[x] = CLAMP(MAX(wall->cya, wall->cnya), scrn->ytop[x], H - 1);
	scrn->txt->current = scrn->txt->lowertextures;
	render_wall_line(scrn,
					set_textured_line(x, (wall->cnyb + 1), wall->cyb),
					set_scaler(wall->ya, (wall->cnyb + 1), wall->yb),
					wall->z);
}

SDL_Surface		*texture_switch(screen *scrn, int s)
{
	if (SECT_NOW->npoints < s)
	{
		if (SECT_NOW->object == 1)
			return (scrn->txt->door);
		if (SECT_NOW->object == 2)
			return (scrn->txt->dec[0]);
		if (SECT_NOW->object == 3)
			return (scrn->txt->dec[1]);
		if (SECT_NOW->object == 4)
			return (scrn->txt->dec[2]);
		if (SECT_NOW->object == 5)
			return (scrn->txt->dec[3]);
		if (SECT_NOW->object == 6)
			return (scrn->txt->dec[4]);
		if (SECT_NOW->object == 7)
			return (play_animation(scrn->txt->key, 6));
		if (SECT_NOW->object == 8)
			return (scrn->txt->key[6]);
	}
	return (scrn->txt->uppertextures);
}

void			render_the_wall(screen *scrn,
					perspective_s perspect,
					heights_s heights,
					int s)
{
	wall_s	wall;
	int		x;

	x = heights.beginx;
	while (++x <= heights.endx)
	{
		wall = wall_init(scrn, &heights, x, perspect);
		if (SECT_NOW->npoints > s)
			render_floor_ceil(scrn, wall, heights, x);
		if (HAS_NGHBR_NOW(s))
		{
			set_neighbor_wall(&wall, scrn, &heights, x);
			scrn->ybottom[x] = CLAMP(MIN(wall.cyb, wall.cnyb),
										0, scrn->ybottom[x]);
		}
		else
		{
			scrn->txt->current = texture_switch(scrn, s);
			render_wall_line(scrn,
							set_textured_line(x, wall.cya, wall.cyb),
							set_scaler(wall.ya, wall.cya, wall.yb),
							wall.z);
		}
	}
}
