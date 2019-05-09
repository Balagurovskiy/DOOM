/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_each_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 16:26:36 by obalagur          #+#    #+#             */
/*   Updated: 2018/04/07 16:26:40 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <fcntl.h>

void			*for_each_gnl(char *file, void *(*f)(char *, int))
{
	char	*line;
	int		fd;
	void	*res;

	line = NULL;
	res = NULL;
	fd = open(file, O_RDONLY);
	if (*f)
		res = (*f)(NULL, 0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*f)
			res = (*f)(line, 1);
		if (line)
			ft_strdel(&line);
	}
	close(fd);
	return (res);
}
