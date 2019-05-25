/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 22:17:55 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/18 22:17:58 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*struct_list;

	struct_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (struct_list == NULL)
		return (NULL);
	if (content == NULL)
	{
		struct_list->content = NULL;
		struct_list->content_size = 0;
	}
	else
	{
		struct_list->content = malloc(content_size);
		if (struct_list->content == NULL)
			return (NULL);
		ft_memmove(struct_list->content, content, content_size);
		struct_list->content_size = content_size;
	}
	struct_list->next = NULL;
	return (struct_list);
}
