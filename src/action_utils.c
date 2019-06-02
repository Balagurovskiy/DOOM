/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	action_got_key(t_player *p, t_level *lvl)
{
	if (lvl->sector[p->sector].object == 7 && p->action)
	{
		lvl->sector[p->sector].object = 8;
		p->key = 1;
	}
}

void	action_open_door(t_player *p,
					t_level *lvl,
					char *file,
					void (*f)(t_player *p, t_level *l, char *f))
{
	if (lvl->sector[p->sector].object == 1 &&
		p->action && p->key)
	{
		p->key = 0;
		lvl->sector[p->sector].object = 0;
		(*f)(p, lvl, file);
	}
}

void	action_controller(t_player *player, t_level *lvl, char *file)
{
	action_got_key(player, lvl);
	action_open_door(player, lvl, file, &door0000);
}
