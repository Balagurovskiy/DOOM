/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:09:42 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/11 17:09:44 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_atoi(const char *str)
{
	int i;
	int is_positive;
	int num;

	i = 0;
	num = 0;
	is_positive = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i += 1;
	if (str[i] == '-')
		is_positive = 0;
	if (str[i] == '+' || str[i] == '-')
		i += 1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10;
		num = num + str[i] - '0';
		i += 1;
	}
	if (is_positive == 0)
		num *= -1;
	return (num);
}
