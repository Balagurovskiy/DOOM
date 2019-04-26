/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:01:50 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 12:02:58 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "parser.h"
void print(t_map *map){
	int i = 0;
	t_map_sector *s = map->sector;
	while (i < map->sector_size)
	{
		int ii = 0;
		while (ii < map->sector->vertex_size)
		{
			t_map_vertex *v = s->vertex;
			printf("x:%d ",v->x);
			printf("y:%d  ",v->y);
			printf("n:%d  ",v->neighbor);
			v = v->next;
			ii++;
		}

		printf("ns:%d  nm:%s | %d | %d \n",s->next_level_sector,s->next_level,i,ii);
		s = s->next;
		i++;
	}
	printf(">\n");
	printf("%s\n", map->floortexture);
	printf("%s\n", map->ceiltexture);
	printf("%s\n", map->uppertextures);
	printf("%s\n", map->lowertextures);
	printf("%d\n", map->texture_size);
	printf("<\n");
}

//int		main(int argc, char **argv)
//{
//
//	// if (argc != 2)
//	// 	ft_putstr("\t usage : <./exe> <filename>");
//	char *filename = "map.doom";
//	char *filename2 = "map2.doom";
//
//	t_map *map = (t_map *)for_each_gnl(filename2, (void *)&parser);
//	print(map);
//	printf("------------\n");
//	map = (t_map *)for_each_gnl(filename, (void *)&parser);
//	print(map);
//
////////////////////////////////////////////
//	// map_del_sector(&(map->sector));
//	// ft_memdel((void **)&(map->floortexture));
//	// ft_memdel((void **)&(map->ceiltexture));
//	// ft_memdel((void **)&(map->uppertextures));
//	// ft_memdel((void **)&(map->lowertextures));
//	// ft_memdel((void **)&map);
////////////////////////////////////////////
//	while(1);
//
//	return (0);
//}

//TODO
// free on exception
// if (catch_exception(0))
// {
// 		printf("EXCEPTION stat : %d\n\n",catch_exception(0));
// 		exit(0);
// }
