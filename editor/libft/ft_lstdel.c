/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 23:42:48 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/18 23:42:52 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*link_holder;
	t_list	*next_link_holder;

	link_holder = *alst;
	if (del != NULL)
	{
		while (link_holder != NULL)
		{
			next_link_holder = link_holder->next;
			del(link_holder->content, link_holder->content_size);
			free(link_holder);
			link_holder = next_link_holder;
		}
		*alst = NULL;
	}
}
