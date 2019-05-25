/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 00:05:36 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/19 00:05:41 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *holder;

	if (lst != NULL && f != NULL)
	{
		holder = f(lst);
		if (holder != NULL && lst->next != NULL)
		{
			holder->next = ft_lstmap(lst->next, f);
		}
		return (holder);
	}
	return (NULL);
}
