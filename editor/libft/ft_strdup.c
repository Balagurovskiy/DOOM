/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 04:04:19 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/26 04:04:21 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*res_str;

	i = 0;
	len = ft_strlen(s1);
	if (!(res_str = (char *)malloc(sizeof(*res_str) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		res_str[i] = s1[i];
		i++;
	}
	res_str[i] = '\0';
	return (res_str);
}
