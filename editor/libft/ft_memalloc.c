/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:46:04 by mkachano          #+#    #+#             */
/*   Updated: 2017/11/11 21:46:08 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem_area;

	if ((mem_area = malloc(size)) == NULL)
		return (mem_area);
	ft_memset(mem_area, 0, size);
	return (mem_area);
}
