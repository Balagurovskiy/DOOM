/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_level.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:27:38 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:45:58 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	safe_put(t_level **lvl, t_map_sector *ms, int *exits, int i)
{
	if ((*exits) > 3)
		return ;
	if (ms->next_level_sector > -1 && ms->next_level)
	{
		(*lvl)->end[(*exits)] = i;
		(*lvl)->next_level[(*exits)] = ft_strjoin(ms->next_level, NULL);
		(*lvl)->start[(*exits)] = ms->next_level_sector;
		(*exits)++;
	}
}

void		connect_next_level(t_level *lvl, t_map *map)
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
		safe_put(&lvl, ms, &exits, i);
		ms = ms->next;
		i++;
	}
}
