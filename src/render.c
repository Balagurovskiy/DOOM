/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:22 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "render.h"
#include "utils.h"

SDL_Surface			*play_animation(SDL_Surface *anims[], int size)
{
	static int	entry = 0;
	static int	back = 0;

	if (ft_timer())
	{
		if (back)
			entry--;
		else
			entry++;
	}
	if (entry > size - 1)
	{
		entry = size - 2;
		back = 1;
	}
	if (entry < 0)
	{
		entry = 1;
		back = 0;
	}
	if (size <= 2)
		entry = 0;
	return (anims[entry]);
}

static t_screen		screen_init(SDL_Surface *surface,
									t_player *player,
									t_sectors *sector,
									t_texture_set *t)
{
	t_screen			scrn;
	unsigned int		i;

	scrn.player = player;
	scrn.surface = surface;
	scrn.sector = sector;
	scrn.txt = t;
	scrn.head = scrn.queue;
	scrn.tail = scrn.queue;
	i = 0;
	while (i < W)
	{
		scrn.ytop[i] = 0;
		scrn.ybottom[i] = H - 1;
		i++;
	}
	scrn.head->sectorno = player->sector;
	scrn.head->sx1 = 0;
	scrn.head->sx2 = W - 1;
	if (++scrn.head == (scrn.queue + MAX_QUE))
		scrn.head = scrn.queue;
	return (scrn);
}

void				render_screen(SDL_Surface *srf,
									t_player *pl,
									t_level *lvl,
									int is_obj)
{
	t_screen			scrn;
	unsigned int		s;
	int					renderedsectors[pl->total_sectors];

	scrn = screen_init(srf, pl, lvl->sector, &(lvl->texture));
	s = 0;
	while (s < pl->total_sectors)
		renderedsectors[s++] = 0;
	while (scrn.head != scrn.tail)
	{
		scrn.now = *scrn.tail;
		if (++scrn.tail == scrn.queue + MAX_QUE)
			scrn.tail = scrn.queue;
		if (!(renderedsectors[scrn.now.sectorno] & 0x21))
		{
			++renderedsectors[scrn.now.sectorno];
			render_towards(&scrn);
			++renderedsectors[scrn.now.sectorno];
		}
	}
	SDL_Delay(10);
}
