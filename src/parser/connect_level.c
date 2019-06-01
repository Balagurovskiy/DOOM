/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_level.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:27:38 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:30:36 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	connect_next_level(level_s *lvl, t_map *map)
{
	t_map_sector	*ms;
	int				i;
	int				exits;

	i = 3;
	while (i--)
		lvl->next_level[i] = NULL;
	i = 0;
	exits = 0;
	ms = map->sector;
	while (i < map->sector_size)
	{
		if (exits < 3 && ms->next_level_sector > -1 && ms->next_level)
		{
			lvl->end[exits] = i;
			lvl->next_level[exits] = ft_strjoin(ms->next_level, NULL);
			lvl->start[exits] = ms->next_level_sector;
			exits++;
		}
		ms = ms->next;
		i++;
	}
}
