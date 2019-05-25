/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:25:05 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/12 00:25:07 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*new_str;

	if (!s || !f)
		return (NULL);
	len = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (new_str == NULL)
		return (NULL);
	while (s[len] != '\0')
	{
		new_str[len] = f(len, s[len]);
		len += 1;
	}
	new_str[len] = '\0';
	return (new_str);
}
