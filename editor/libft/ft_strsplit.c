/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:48:57 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/12 01:48:59 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_w(char const *s, char c)
{
	unsigned int	i;
	int				cntr;

	i = 0;
	cntr = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			cntr++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (cntr);
}

static char			*ft_strndup(const char *s, size_t n)
{
	char			*str;

	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

char				**ft_strsplit(char const *s, char c)
{
	int				i;
	int				j;
	int				k;
	char			**r;

	i = 0;
	k = 0;
	if (!s || (r = (char **)malloc(sizeof(char *) * (ft_w(s, c)) + 1)) == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i += 1;
		j = i;
		while (s[i] && s[i] != c)
			i += 1;
		if (i > j)
		{
			r[k] = ft_strndup(s + j, i - j);
			k += 1;
		}
	}
	r[k] = NULL;
	return (r);
}
