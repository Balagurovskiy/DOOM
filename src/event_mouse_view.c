/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:19 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"

t_view_events		view_events_init(t_move_events *me)
{
	t_view_events		ve;

	SDL_GetRelativeMouseState(&(ve.x), &(ve.y));
	ve.move_vec[0] = 0.f;
	ve.move_vec[1] = 0.f;
	ve.pushing = me->wsad[0] || me->wsad[1] || me->wsad[2] || me->wsad[3];
	ve.acceleration = ve.pushing ? 0.4 : 0.2;
	if (ve.pushing)
		me->moving = 1;
	return (ve);
}

void				move_direction_switch(t_move_events *me,
											t_view_events *ve,
											t_player *player)
{
	if (me->wsad[0])
	{
		ve->move_vec[0] += player->anglecos * SPEED_KOEF(0.14f);
		ve->move_vec[1] += player->anglesin * SPEED_KOEF(0.14f);
	}
	if (me->wsad[1])
	{
		ve->move_vec[0] -= player->anglecos * SPEED_KOEF(0.06f);
		ve->move_vec[1] -= player->anglesin * SPEED_KOEF(0.06f);
	}
	if (me->wsad[2])
	{
		ve->move_vec[0] += player->anglesin * SPEED_KOEF(0.1f);
		ve->move_vec[1] -= player->anglecos * SPEED_KOEF(0.1f);
	}
	if (me->wsad[3])
	{
		ve->move_vec[0] -= player->anglesin * SPEED_KOEF(0.1f);
		ve->move_vec[1] += player->anglecos * SPEED_KOEF(0.1f);
	}
}

void				view_event(t_move_events *me,
							t_view_events *ve,
							t_player *player,
							t_sectors *sectors)
{
	player->angle += ve->x * 0.007f;
	me->yaw = CLAMP(me->yaw + ve->y * 0.05f, -5, 5);
	player->yaw = me->yaw - player->velocity.z * 0.5f;
	move_player(new_xy(0.0, 0.0), player, sectors);
	move_direction_switch(me, ve, player);
	VLCTY.x = VLCTY.x * (1 - ACCEL) + ve->move_vec[0] * ACCEL;
	VLCTY.y = VLCTY.y * (1 - ACCEL) + ve->move_vec[1] * ACCEL;
}
