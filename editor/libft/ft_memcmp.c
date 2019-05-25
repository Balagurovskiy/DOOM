/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 03:56:28 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/26 03:56:31 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*pt1;
	unsigned char	*pt2;

	if (n == 0)
		return (0);
	i = 0;
	pt1 = (unsigned char *)s1;
	pt2 = (unsigned char *)s2;
	while (n--)
	{
		if (pt1[i] != pt2[i])
			return (pt1[i] - pt2[i]);
		i++;
	}
	return (0);
}
