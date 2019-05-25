/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:53:21 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/12 00:53:23 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*new_str;

	if (!s)
		return (NULL);
	if ((new_str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	l = 0;
	while (l < len && s[start] != '\0')
	{
		new_str[l] = s[start + l];
		l += 1;
	}
	new_str[l] = '\0';
	return (new_str);
}
