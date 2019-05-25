# include "libft.h"
#include "parser.h"

int line_with_sector_data(char *line)
{
	int ceil;
	int floor;
	int sector;

	ceil = ft_str_contains(line, "ceil:\0");
	floor = ft_str_contains(line, "floor:\0");
	sector = ft_str_contains(line, "sector:\0");
	return (ceil && floor && sector);
}

void parse_line(char **line, t_map_sector **map_sector)
{
	t_map_sector *map_sector_new;

	map_sector_new = map_new_sector();
	if (!map_sector_new)
		return ;
	map_sector_new->ceil = parse_singe_value(line, "ceil:\0", ";\0");
	map_sector_new->floor = parse_singe_value(line, "floor:\0", ";\0");
	map_sector_new->floor = ((map_sector_new->ceil <= map_sector_new->floor) ?
								0 : map_sector_new->floor);
	map_sector_new->vertex = parse_sector(line, &(map_sector_new->vertex_size));
	map_sector_new->object = parse_sector_object(line);
	map_sector_new->next_level = parse_level(line, &(map_sector_new->next_level_sector));
	map_add_sector(map_sector, map_sector_new);
}

void parse_texture_switch(char **txt_data, t_map **map, int *it)
{
	int  k;

	k = 0;
	(*it) = 0;
	while (txt_data && txt_data[k] && k < 4)
	{
		if ((*it) == 0)
			(*map)->floortexture = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 1)
			(*map)->ceiltexture = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 2)
			(*map)->uppertextures = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 3)
			(*map)->lowertextures = ft_strjoin(txt_data[k], NULL);		
		(*it) = iterate(4);
		k++;
	}
	k = 0;
	while(txt_data && txt_data[k])
		ft_memdel((void **)&(txt_data[k++]));
}
void parse_texture(char *line, t_map **map)
{
	char *txt;
	char **txt_data;
	int it;

	txt = cut_str_value(line, "texture:\0", ";\0");
	txt_data = ft_splinter(txt, ",{}");
	parse_texture_switch(txt_data, map, &it);
	if (it != 0 || !txt || !txt_data)
	{
		ft_putstr("EXCEPTION > parser > invalid texture data\n");
		catch_exception(1);
	}
	ft_memdel((void **)&(txt_data));
	ft_memdel((void **)&txt);
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

t_map   *map_init()
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map) * 1);
	map->floortexture =  NULL;
	map->ceiltexture =  NULL;
	map->uppertextures =  NULL;
	map->lowertextures =  NULL;
	map->sector = NULL;
	map->sector_size = 0;
	return (map);
}

t_map   *parser(char *line, int status)
{
	static 					t_map *map = NULL;
	static int 				entry = 0;
	static t_map_sector 	*map_sector = NULL;

	if(status && !catch_exception(0))
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

