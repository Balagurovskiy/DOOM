/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 12:33:30 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/18 12:33:33 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*result;

	if ((result = (char *)malloc(sizeof(char) * 2)) == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(result, "-2147483648"));
	if (n < 0)
	{
		result[0] = '-';
		result[1] = '\0';
		result = ft_strjoin(result, ft_itoa(-n));
	}
	else if (n >= 10)
		result = ft_strjoin(ft_itoa(n / 10), ft_itoa(n % 10));
	else if (n >= 0 && n < 10)
	{
		result[0] = n + '0';
		result[1] = '\0';
	}
	return (result);
}
