/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:12:31 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "parser.h"

void	change_level(level_s *lvl, player *p)
{
	int			j;
	player_save	ps;
	t_map		*map_temp;

	j = 3;
	while(j-- && j >= 0)
	{
		if(p->sector == lvl->end[j] && lvl->next_level[j])
		{
			ps.next_start = lvl->start[j];
			ps.angle = p->angle;
			ps.health = p->health;
			ps.key = p->key;
			ps.next_lvl_temp = ft_strjoin(lvl->next_level[j], NULL);
			map_temp = get_map(ps.next_lvl_temp);
			if (map_temp && ps.next_start >= 0 && ps.next_start < lvl->sectors_size)
			{
				free_level(lvl);
				*lvl = connect_level(map_temp);
				*p = init_player(ps.angle, lvl->sector, ps.next_start, lvl->sectors_size);
				save_file(ps.next_lvl_temp);
				p->health = ps.health;
				p->key = ps.key;
			}
			ft_memdel((void**)&(ps.next_lvl_temp));
		}
	}
}

void	goto_level(level_s *lvl, player *p, char *level_name)
{
	t_map	*map_temp;

	map_temp = get_map(level_name);
	free_level(lvl);
	*lvl = connect_level(map_temp);
	*p = init_player(0.0, lvl->sector, 0, lvl->sectors_size);
	save_file(level_name);
}

void	action_got_key(player *p, level_s *lvl)
{
	if(lvl->sector[p->sector].object == 7 && p->action){
		lvl->sector[p->sector].object = 8;
		p->key = 1;
	}
}

void	action_open_door(player *p,
					level_s *lvl,
					char *file,
					void (*f)(player *p, level_s *l, char *f))
{
	if(lvl->sector[p->sector].object == 1 &&
		p->action && p->key)
	{
		p->key = 0;
		lvl->sector[p->sector].object = 0;
		(*f)(p, lvl, file);
	}
}

void	action_controller(player *player, level_s *lvl, char *file)
{
	action_got_key(player, lvl);
	action_open_door(player, lvl, file, &door0000);
}