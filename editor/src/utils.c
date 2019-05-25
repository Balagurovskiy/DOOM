/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:00:18 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/19 18:00:19 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static int		numbers_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char		*number_assign(int n, int end, char *res)
{
	if (n < 0)
	{
		res[0] = '-';
		end++;
		while (end != 1)
		{
			res[end-- - 1] = ((n % 10) * -1) + '0';
			n = n / 10;
		}
	}
	else
	{
		while (end != 0)
		{
			res[end-- - 1] = (n % 10) + '0';
			n = n / 10;
		}
	}
	return (res);
}

char			*itoa_extended(int n)
{
	int		nums;
	char	*res;

	nums = numbers_count(n);
	if (n < 0)
		res = ft_strnew(nums + 1);
	else
		res = ft_strnew(nums);
	if (res == NULL)
		return (NULL);
	else
		res = number_assign(n, nums, res);
	return (res);
}

void			save_number_fd(int number, int fd)
{
	char *tmp;

	tmp = itoa_extended(number);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

void			free_memory(char **src, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(src[i++]);
	free(src);
}
