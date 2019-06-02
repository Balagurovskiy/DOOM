/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_heights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:24 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "render_heights.h"

float		set_heights(float height, float z, float yaw, float scale_y)
{
	return (H / 2 + (-YAW(height, z, yaw) * scale_y));
}

void		set_heights_floor_ceil(t_heights *heights,
									t_player *p,
									t_sectors *s,
									int nghbr)
{
	heights->neighb_yceil = 0;
	heights->neighb_yfloor = 0;
	if (nghbr)
	{
		heights->neighb_yceil = s->ceil - p->where.z;
		heights->neighb_yfloor = s->floor - p->where.z;
	}
	if (nghbr == -2)
	{
		heights->yceil = s->ceil - p->where.z;
		heights->yfloor = s->floor - p->where.z;
	}
}

void		set_heights_x(t_heights *heights,
							t_perspective perspect,
							t_screen *scrn)
{
	heights->beginx = MAX(perspect.x1, scrn->now.sx1);
	heights->endx = MIN(perspect.x2, scrn->now.sx2);
}

void		set_heights_y(t_heights *h,
							t_player *pl,
							t_edge edge,
							t_perspective p)
{
	float	y1a;
	float	y1b;
	float	y2a;
	float	y2b;

	y1a = set_heights(h->yceil, edge.t1.z, pl->yaw, p.scale1.y);
	y1b = set_heights(h->yfloor, edge.t1.z, pl->yaw, p.scale1.y);
	y2a = set_heights(h->yceil, edge.t2.z, pl->yaw, p.scale2.y);
	y2b = set_heights(h->yfloor, edge.t2.z, pl->yaw, p.scale2.y);
	h->z = scaler_init(set_scaler(p.x1, h->beginx, p.x2),
						edge.t1.z * 8.0, edge.t2.z * 8.0);
	h->ya = scaler_init(set_scaler(p.x1, h->beginx, p.x2), y1a, y2a);
	h->yb = scaler_init(set_scaler(p.x1, h->beginx, p.x2), y1b, y2b);
	y1a = set_heights(h->neighb_yceil, edge.t1.z, pl->yaw, p.scale1.y);
	y1b = set_heights(h->neighb_yfloor, edge.t1.z, pl->yaw, p.scale1.y);
	y2a = set_heights(h->neighb_yceil, edge.t2.z, pl->yaw, p.scale2.y);
	y2b = set_heights(h->neighb_yfloor, edge.t2.z, pl->yaw, p.scale2.y);
	h->neighb_ya = scaler_init(set_scaler(p.x1, h->beginx, p.x2), y1a, y2a);
	h->neighb_yb = scaler_init(set_scaler(p.x1, h->beginx, p.x2), y1b, y2b);
}

t_heights	heights_init(t_screen *scrn, t_perspective perspect, int s)
{
	t_heights	heights;

	set_heights_x(&heights, perspect, scrn);
	set_heights_floor_ceil(&heights, scrn->player, SECT_NOW, -2);
	set_heights_floor_ceil(&heights, scrn->player,
							SECT_NGHBR_NOW(s), HAS_NGHBR_NOW(s));
	set_heights_y(&heights, scrn->player, scrn->edge, perspect);
	return (heights);
}
