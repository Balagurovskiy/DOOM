/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "parser.h"

t_player_save	make_player_save(t_level *lvl, t_player *p, int j)
{
	t_player_save	ps;

	ps.next_start = lvl->start[j];
	ps.angle = p->angle;
	ps.health = p->health;
	ps.key = p->key;
	ps.next_lvl_temp = ft_strjoin(lvl->next_level[j], NULL);
	return (ps);
}

void			change_level(t_level *lvl, t_player *p)
{
	int				j;
	t_player_save	ps;
	t_map			*map_temp;

	j = 3;
	while (--j >= 0)
	{
		if (p->sector == lvl->end[j] && lvl->next_level[j])
		{
			ps = make_player_save(lvl, p, j);
			map_temp = get_map(ps.next_lvl_temp);
			if (NEXT_LVLV_IS_VALID)
			{
				free_level(lvl);
				*lvl = connect_level(map_temp);
				*p = init_player(ps.angle, lvl->sector,
								ps.next_start, lvl->sectors_size);
				save_file(ps.next_lvl_temp);
				p->health = ps.health;
				p->key = ps.key;
			}
			ft_memdel((void**)&(ps.next_lvl_temp));
		}
	}
}

void			goto_level(t_level *lvl, t_player *p, char *level_name)
{
	t_map	*map_temp;

	map_temp = get_map(level_name);
	free_level(lvl);
	*lvl = connect_level(map_temp);
	*p = init_player(0.0, lvl->sector, 0, lvl->sectors_size);
	save_file(level_name);
}
