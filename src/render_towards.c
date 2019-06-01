/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_towards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:13:04 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "defines.h"
# include "doom.h"
# include "render.h"
# include "render_wall.h"

edge_s		edge_init(player *player, sectors *sect, int s)
{
	edge_s edge;

	if (s > sect->npoints)
	{
		edge.v1.x = sect->object_xy[0].x - player->where.x;
		edge.v1.y = sect->object_xy[0].y - player->where.y;
		edge.v2.x = sect->object_xy[1].x - player->where.x;
		edge.v2.y = sect->object_xy[1].y - player->where.y;
	}
	else
	{
		edge.v1.x = sect->vertex[s+0].x - player->where.x;
		edge.v1.y = sect->vertex[s+0].y - player->where.y;
		edge.v2.x = sect->vertex[s+1].x - player->where.x;
		edge.v2.y = sect->vertex[s+1].y - player->where.y;
	}
	edge.pcos = player->anglecos;
	edge.psin = player->anglesin;
	edge.t1.x = edge.v1.x * edge.psin - edge.v1.y * edge.pcos;
	edge.t1.z = edge.v1.x * edge.pcos + edge.v1.y * edge.psin;
	edge.t2.x = edge.v2.x * edge.psin - edge.v2.y * edge.pcos;
	edge.t2.z = edge.v2.x * edge.pcos + edge.v2.y * edge.psin;
	return (edge);
}

void		schedule(screen *scrn, heights_s heights, int s)
{
	if (HAS_NGHBR_NOW(s) && NOT_END && HAS_NEXT_QUE)
	{
		scrn->head->sectorno = NGHBR_NOW(s);
		scrn->head->sx1 = heights.beginx;
		scrn->head->sx2 = heights.endx;
		if (++scrn->head == scrn->queue + MAX_QUE)
			scrn->head = scrn->queue;
	}
}

void		render_towards(screen *scrn)
{
	heights_s		heights;
	perspective_s	perspect;
	int				s;

	s = 0;
	while(s < (SECT_NOW->npoints + ((SECT_NOW->object >= 1) ? 1 : 0)))
	{
		if (s == SECT_NOW->npoints && SECT_NOW->object)
			s++;
		scrn->edge = edge_init(scrn->player, SECT_NOW, s);
		scrn->txt_data.u0 = 0;
		scrn->txt_data.u1 = scrn->txt->uppertextures->w - 1;
		if (IS_FRONT(scrn->edge))
		{
			view_intersection_with_wall(scrn);
			perspect = perspective_init(scrn->edge);
			if (perspect.x1 < perspect.x2)
			{
				if (perspect.x2 > scrn->now.sx1 && perspect.x1 < scrn->now.sx2)
				{
					heights = heights_init(scrn, perspect, s);
					render_the_wall(scrn, perspect, heights, s);
					schedule(scrn, heights, s);
				}
			}
		}
		s++;
	}
}
