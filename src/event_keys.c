/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:12:43 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "events.h"

void	move_key_event(move_events *me, unsigned int sym, SDL_Event e)
{
	if(sym == 'w')
		me->wsad[0] = e.type == SDL_KEYDOWN;
	if(sym == 's')
		me->wsad[1] = e.type == SDL_KEYDOWN;
	if(sym == 'a')
		me->wsad[2] = e.type == SDL_KEYDOWN;
	if(sym == 'd')
		me->wsad[3] = e.type == SDL_KEYDOWN;
}

void	jump_duck_key_event(move_events *me,
						player *player,
						unsigned int sym,
						SDL_Event e)
{
	if(sym == ' ' && !me->ducking)
	{
		if (me->ground)
		{
			player->velocity.z += 0.7;
			me->falling = 1;
		}
	}
	if(sym == SDLK_RCTRL || sym == SDLK_LCTRL)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (me->ducking)
				me->ducking = 0;
			else
				me->ducking = 1;
		}
		me->falling = 1;
	}
}

void	key_events(move_events *me, player *player)
{
	SDL_Event e;
	unsigned int sym;

	while(SDL_PollEvent(&e))
	{
		sym = e.key.keysym.sym;
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			move_key_event(me, sym, e);
			if(sym == 'e')
				player->action = e.type == SDL_KEYDOWN;
			jump_duck_key_event(me, player, sym, e);
			if(sym == SDLK_ESCAPE)
				player->exit_doom = 1;
		}
		if (e.type == SDL_QUIT)
			player->exit_doom = 1;
	}
}
