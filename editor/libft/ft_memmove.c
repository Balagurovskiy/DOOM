/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 01:53:47 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/26 01:53:50 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*str1;
	const char	*str2;

	str1 = (char *)dst;
	str2 = (const char *)src;
	if (str2 >= str1)
		str1 = ft_memcpy(str1, str2, len);
	else
	{
		str1 += len;
		str2 += len;
		while (len--)
		{
			str1 -= 1;
			str2 -= 1;
			*str1 = *str2;
		}
	}
	return (dst);
}
