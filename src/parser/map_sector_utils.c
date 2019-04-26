/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:06:29 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 13:06:32 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map_sector		*map_new_sector()
{
	t_map_sector	*new_node;

	new_node = (t_map_sector*)malloc(sizeof(t_map_sector));
	if (new_node == NULL)
		return (NULL);
	// new_node->neighbor = n;
	// new_node->x = x;
	// new_node->y = y;
	new_node->next = NULL;
	return (new_node);
}

// char			map_get_type(t_map *map, int x, int y)
// {
// 	t_map *m;

// 	if (map)
// 	{
// 		m = map;
// 		while (m)
// 		{
// 			if (m->x == x && m->y == y)
// 				return (m->type[0]);
// 			m = m->next;
// 		}
// 	}
// 	return ('0');
// }

void			map_add_sector(t_map_sector **first, t_map_sector *new)
{
	t_map_sector *f;

	if (*first != NULL)
	{
		f = *first;
		while (f)
		{
			if (f->next == NULL)
			{
				f->next = new;
				break ;
			}
			f = f->next;
		}
	}
	else
		*first = new;
}

void			map_del_sector(t_map_sector **node)
{
	t_map_sector *del;

	if (*node)
	{
		while (*node)
		{
			del = *node;
			*node = (*node)->next;
			if (del->vertex)
				map_del_vertex(&(del->vertex));
			// ft_memdel((void **)&(del->neighbor));
			if (del->next_level)
				free(del->next_level);
			free(del);
			del = NULL;
		}
	}
}
