/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:17 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"

t_move_events	move_events_init(void)
{
	t_move_events	me;

	me.wsad[0] = 0;
	me.wsad[1] = 0;
	me.wsad[2] = 0;
	me.wsad[3] = 0;
	me.ground = 0;
	me.falling = 1;
	me.moving = 0;
	me.ducking = 0;
	me.yaw = 0;
	return (me);
}

void			move_player(t_xy d, t_player *player, t_sectors *sector)
{
	unsigned int		s;
	t_xy				p;

	p = new_xy(player->where.x, player->where.y);
	s = 0;
	while (s < PLAYER_SECT.npoints)
	{
		if (PLAYER_SECT.neighbors[s] >= 0
		&& intersect_box_handle(p, d, VERT, s)
				&& point_side_handle(p, d, VERT, s) < 0)
		{
			player->sector = PLAYER_SECT.neighbors[s];
			break ;
		}
		s++;
	}
	player->where.x += d.x;
	player->where.y += d.y;
	player->anglesin = sinf(player->angle);
	player->anglecos = cosf(player->angle);
}
