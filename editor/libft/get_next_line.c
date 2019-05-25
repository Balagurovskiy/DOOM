/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:08:55 by mkachano          #+#    #+#             */
/*   Updated: 2018/03/31 13:54:44 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_data_by_fd(int fd, t_list **list)
{
	t_list	*node;

	node = *list;
	while (node)
	{
		if (node->content_size == (size_t)fd)
			return (node);
		node = node->next;
	}
	node = ft_lstnew("\0", fd);
	ft_lstadd(list, node);
	return (node);
}

int				index_of(char chr, char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			return (i);
		i += 1;
	}
	return (-1);
}

int				write_next_line(int idx, t_list *fd_data, char **line)
{
	char	*tmp;
	size_t	str_length;

	*line = ft_strsub(fd_data->content, 0, idx);
	GNL_MALLOC_CHECK(*line);
	str_length = ft_strlen(fd_data->content);
	if (idx < (int)str_length)
	{
		tmp = fd_data->content;
		fd_data->content = ft_strsub(fd_data->content, (idx + 1), str_length);
		GNL_MALLOC_CHECK(fd_data->content);
		ft_strdel(&tmp);
	}
	else
	{
		ft_strclr(fd_data->content);
	}
	return (1);
}

int				read_next_line(int fd, t_list *fd_data, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;
	int		idx;
	size_t	context_size;
	size_t	str_length;

	if ((idx = index_of('\n', fd_data->content)) < 0)
	{
		while ((context_size = read(fd, buffer, BUFF_SIZE)) > 0)
		{
			buffer[context_size] = '\0';
			tmp = fd_data->content;
			fd_data->content = ft_strjoin(tmp, buffer);
			GNL_MALLOC_CHECK(fd_data->content);
			ft_strdel(&tmp);
			if (index_of('\n', buffer) >= 0)
				break ;
		}
		str_length = ft_strlen(fd_data->content);
		if (context_size < BUFF_SIZE && (!str_length))
			return (0);
		idx = (context_size == 0 && str_length)
		? str_length : index_of('\n', fd_data->content);
	}
	return (write_next_line(idx, fd_data, line));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*data;
	t_list			*fd_data;

	if ((fd < 0 || BUFF_SIZE < 1 || line == NULL || read(fd, "", 0) < 0))
		return (-1);
	fd_data = get_data_by_fd(fd, &data);
	GNL_MALLOC_CHECK(fd_data);
	return (read_next_line(fd, fd_data, line));
}
