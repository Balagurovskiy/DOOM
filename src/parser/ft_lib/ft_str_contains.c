/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 15:56:23 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/16 15:56:27 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_str_contains(char *source, char *target)
{
	int target_len;
	int s;
	int t;

	s = 0;	
	if (source && target)
	{
		target_len = ft_strlen(target);
		while (source[s])
		{
			t = 0;
			while ((source[s] == target[t]) && target[t])
			{
				s++;
				t++;
			}
			if (t == target_len)
				return (s);
			s++;
		}
	}
	return (0);
}
