/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 16:44:06 by obalagur          #+#    #+#             */
/*   Updated: 2017/12/02 11:29:04 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void		itoa_putnbr(char *res, size_t *i, int n)
{
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		(*i) = 2;
		n = 147483648;
	}
	if (n < 0)
	{
		res[0] = '-';
		(*i) = 1;
		n = -n;
	}
	if (n < 10)
	{
		res[(*i)] = n + '0';
		(*i)++;
	}
	else
	{
		itoa_putnbr(res, i, (n / 10));
		itoa_putnbr(res, i, (n % 10));
	}
}

char			*ft_itoa(int n)
{
	char		*res;
	size_t		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * ft_intlen(n) + 1);
	if (res == NULL)
		return (NULL);
	itoa_putnbr(res, &i, n);
	res[i] = '\0';
	return (res);
}
