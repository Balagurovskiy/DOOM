/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_sector_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:37:05 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:01 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map_sector		*map_new_sector(void)
{
	t_map_sector	*new_node;

	new_node = (t_map_sector*)malloc(sizeof(t_map_sector));
	if (new_node == NULL)
		return (NULL);
	new_node->vertex = NULL;
	new_node->object = NULL;
	new_node->next = NULL;
	return (new_node);
}

void				map_add_sector(t_map_sector **first, t_map_sector *new)
{
	t_map_sector	*f;

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

void				map_del_sector(t_map_sector **node)
{
	t_map_sector	*del;

	if (*node)
	{
		while (*node)
		{
			del = *node;
			*node = (*node)->next;
			if (del->vertex)
				map_del_vertex(&(del->vertex));
			if (del->object)
				map_del_vertex(&(del->object));
			if (del->next_level)
				free(del->next_level);
			free(del);
			del = NULL;
		}
	}
}
