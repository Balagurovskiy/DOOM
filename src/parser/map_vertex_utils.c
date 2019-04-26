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

t_map_vertex		*map_new_vertex()
{
	t_map_vertex	*new_node;

	new_node = (t_map_vertex*)malloc(sizeof(t_map_vertex));
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

void			map_add_vertex(t_map_vertex **first, t_map_vertex *new)
{
	t_map_vertex *f;

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

void			map_del_vertex(t_map_vertex **node)
{
	t_map_vertex *del;

	if (*node)
	{
		while (*node)
		{
			del = *node;
			*node = (*node)->next;
			// ft_memdel((void **)&(del->neighbor));
			free(del);
			del = NULL;
		}
	}
}
