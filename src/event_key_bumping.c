/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_bumping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:16 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"

t_xy	init_hole(t_move_events *me, t_player *player, t_sectors *sector)
{
	t_xy	hole;

	hole.x = 9e9;
	hole.y = -9e9;
	if (PLAYER_NGHBR(me->s) >= 0)
	{
		hole.x = MAX((&PLAYER_SECT)->floor, PLAYER_NGHBR_SECT(me->s).floor);
		hole.y = MIN((&PLAYER_SECT)->ceil, PLAYER_NGHBR_SECT(me->s).ceil);
	}
	return (hole);
}

void	bumping(t_move_events *me,
			t_player *player,
			t_sectors *sector,
			t_xy *d)
{
	t_xy	hole;
	t_xy	xyd;

	hole = init_hole(me, player, sector);
	if (IS_HOLE_HIGH || IS_HOLE_LOW)
	{
		if (me->can_bump)
		{
			xyd.x = VERT[me->s + 1].x - VERT[me->s + 0].x;
			xyd.y = VERT[me->s + 1].y - VERT[me->s + 0].y;
			player->velocity.x = xyd.x * VEL_SUM / SAFE_VEL_POW;
			player->velocity.y = xyd.y * VEL_SUM / SAFE_VEL_POW;
		}
		else
		{
			player->velocity.x = 0;
			player->velocity.y = 0;
		}
		me->moving = 0;
	}
}
