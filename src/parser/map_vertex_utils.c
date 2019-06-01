/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vertex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:37:14 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:41:16 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_map_vertex		*map_new_vertex(void)
{
	t_map_vertex	*new_node;

	new_node = (t_map_vertex*)malloc(sizeof(t_map_vertex));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

void				map_add_vertex(t_map_vertex **first, t_map_vertex *new)
{
	t_map_vertex	*f;

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

void				map_del_vertex(t_map_vertex **node)
{
	t_map_vertex	*del;

	if (*node)
	{
		while (*node)
		{
			del = *node;
			*node = (*node)->next;
			free(del);
			del = NULL;
		}
	}
}
