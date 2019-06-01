/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_data_connector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:37:34 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:41:34 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "doom.h"

t_map		*get_map(char *file_name)
{
	static t_map	*map = NULL;

	if (ft_strequ(file_name, "#get"))
		return (map);
	else if (ft_strequ(file_name, "#del"))
	{
		map_del_sector(&(map->sector));
		ft_memdel((void **)&(map->floortexture));
		ft_memdel((void **)&(map->ceiltexture));
		ft_memdel((void **)&(map->uppertextures));
		ft_memdel((void **)&(map->lowertextures));
		ft_memdel((void **)&map);
		map = NULL;
	}
	else
		map = (t_map *)for_each_gnl(file_name, (void *)&parser);
	return (map);
}

level_s		connect_level(t_map *map)
{
	level_s	lvl;

	if (!map)
		catch_exception(1);
	if (catch_exception(0))
	{
		lvl.sectors_size = -1;
		return (lvl);
	}
	lvl.sector = connect_sectors(map);
	lvl.sectors_size = map->sector_size;
	lvl.texture = connect_textures(map);
	connect_next_level(&lvl, map);
	sector_validation(lvl);
	music("#play");
	return (lvl);
}
