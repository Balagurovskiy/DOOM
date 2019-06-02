/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
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
#include "libft.h"

void	death(SDL_Window *win, SDL_Surface *surface,
				t_player *player, t_level *lvl)
{
	if (player->health == 0)
	{
		render_massage("You died :(((", surface);
		SDL_UpdateWindowSurface(win);
		SDL_Delay(2000);
		if (ft_str_contains(save_file("#get"), ".story\0"))
			goto_level(lvl, player, "level/0000.story");
		else
			goto_level(lvl, player, save_file("#get"));
		player->health = 3;
		player->key = 0;
	}
}

void	events(t_level *lvl, t_player *player,
				SDL_Window *win, SDL_Surface *surface)
{
	static t_move_events		me;
	static t_view_events		ve;
	static int					init_time = 1;

	death(win, surface, player, lvl);
	if (init_time)
		me = move_events_init();
	init_time = 0;
	me.eyeheight = (me.ducking) ? DUCK_HEIGHT : EYE_HEIGHT;
	key_events(&me, player);
	ve = view_events_init(&me);
	view_event(&me, &ve, player, lvl->sector);
	vert_collision_detection(&me, player, lvl->sector);
	hor_collision_detection(&me, player, lvl->sector);
}
