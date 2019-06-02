/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:37:42 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:03 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int		line_with_sector_data(char *line)
{
	int	ceil;
	int	floor;
	int	sector;

	ceil = ft_str_contains(line, "ceil:\0");
	floor = ft_str_contains(line, "floor:\0");
	sector = ft_str_contains(line, "sector:\0");
	return (ceil && floor && sector);
}

void	parse_line(char **line, t_map_sector **map_sector)
{
	t_map_sector	*map_s_new;

	map_s_new = map_new_sector();
	if (!map_s_new)
		return ;
	map_s_new->ceil = parse_singe_value(line, "ceil:\0", ";\0");
	map_s_new->floor = parse_singe_value(line, "floor:\0", ";\0");
	map_s_new->floor = ((map_s_new->ceil <= map_s_new->floor) ?
								0 : map_s_new->floor);
	map_s_new->vertex = parse_sector(line, &(map_s_new->vertex_size));
	map_s_new->object = parse_sector_object(line);
	map_s_new->next_level_sector = -1;
	map_s_new->next_level = parse_level(line, &(map_s_new->next_level_sector));
	map_add_sector(map_sector, map_s_new);
}

void	parser_refresh(int *entry, t_map **map, t_map_sector **sector)
{
	(*entry) = 0;
	if (!(*map))
		return ;
	map_del_sector(sector);
	ft_memdel((void **)&((*map)->floortexture));
	ft_memdel((void **)&((*map)->ceiltexture));
	ft_memdel((void **)&((*map)->uppertextures));
	ft_memdel((void **)&((*map)->lowertextures));
	ft_memdel((void **)map);
	(*map) = NULL;
}

t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map) * 1);
	map->floortexture = NULL;
	map->ceiltexture = NULL;
	map->uppertextures = NULL;
	map->lowertextures = NULL;
	map->sector = NULL;
	map->sector_size = 0;
	return (map);
}

t_map	*parser(char *line, int status)
{
	static t_map			*map = NULL;
	static int				entry = 0;
	static t_map_sector		*map_sector = NULL;

	if (status && !catch_exception(0))
	{
		if (line)
		{
			if (entry == 0)
				map = map_init();
			if (ft_str_contains(line, "texture:\0"))
				parse_texture(line, &map);
			if (line_with_sector_data(line))
			{
				parse_line(&line, &map_sector);
				map->sector = map_sector;
				map->sector_size++;
			}
			entry++;
		}
	}
	else if (!status)
		parser_refresh(&entry, &map, &map_sector);
	return (map);
}
