/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:38:21 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:42:33 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

char		*str_cut(char *line, int start, int end)
{
	char	*cut;
	int		length;
	int		i;

	i = -1;
	cut = NULL;
	length = end - start;
	if (length <= 0 || line == NULL)
		return (cut);
	cut = (char *)malloc(sizeof(char) * length);
	while (++i < length)
		cut[i] = line[start + i];
	cut[i - 1] = '\0';
	return (cut);
}

char		*cut_str_value(char *line, char *start, char *end)
{
	int	start_idx;
	int	end_idx;

	start_idx = ft_str_contains(line, start);
	end_idx = ft_str_contains(line, end);
	if (!start_idx || !end_idx)
		return (NULL);
	return (str_cut(line, start_idx, end_idx));
}

void		loop_str_to_value(char **line, char *value, int condition)
{
	if (condition)
		*line = *line + ft_str_contains(*line, value);
}

int			char_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int			str_isdigit(char *s)
{
	int	i;
	int	isdigit;

	i = -1;
	isdigit = 1;
	if (s)
		while (s[++i])
			if (!char_isdigit(s[i]) && (s[i] != '-'))
				isdigit = 0;
	return (isdigit);
}
