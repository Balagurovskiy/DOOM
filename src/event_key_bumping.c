/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key_bumping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:12:37 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"

void bumping(move_events *me,
			player *player,
			sectors *sector,
			xy *d)
{
	float hole_low;
	float hole_high;
	xy xyd;

	hole_low = 9e9;
	hole_high = -9e9;
	if(PLAYER_NGHBR(me->s) >= 0)
	{
		hole_low  = MAX((&PLAYER_SECT)->floor, PLAYER_NGHBR_SECT(me->s).floor);
		hole_high = MIN((&PLAYER_SECT)->ceil,  PLAYER_NGHBR_SECT(me->s).ceil);
	}
	if((hole_high < (player->where.z + HEAD_MARGIN))
	|| (hole_low  > (player->where.z - me->eyeheight + KNEE_HEIGHT)))
	{
		if (me->can_bump){
			xyd.x = VERT[me->s + 1].x - VERT[me->s + 0].x;
			xyd.y = VERT[me->s + 1].y - VERT[me->s + 0].y;
			player->velocity.x = xyd.x * (d->x * xyd.x + d->y * xyd.y)
								 / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
			player->velocity.y = xyd.y * (d->x * xyd.x + d->y * xyd.y)
								 / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
		}else{
			player->velocity.x=0;
			player->velocity.y=0;
		}
		me->moving = 0;
	}
}