/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:37:51 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:42:02 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	parse_level_info(char **lvl_info,
							int *it,
							char **nxt_lvl,
							int *nxt_sctr)
{
	int		k;

	k = 0;
	while (lvl_info && lvl_info[k] && k < 2)
	{
		if (*it == 0)
			(*nxt_lvl) = ft_strjoin(lvl_info[k], NULL);
		if (*it == 1)
		{
			if (lvl_info[k] && str_isdigit(lvl_info[k]))
				(*nxt_sctr) = ft_atoi((const char *)lvl_info[k]);
			else
			{
				ft_putstr("EXCEPTION > parser > invalid level data\n");
				catch_exception(1);
			}
		}
		ft_memdel((void **)&(lvl_info[k]));
		(*it) = iterate(2);
		k++;
	}
}

char	*parse_level(char **line, int *nxt_sector)
{
	char	*level;
	char	**lvl_info;
	char	*nxt_level;
	int		it;

	nxt_level = NULL;
	level = cut_str_value(*line, "level:\0", ";\0");
	if (level)
	{
		lvl_info = ft_splinter(level, ",{}");
		it = 0;
		(*nxt_sector) = -1;
		parse_level_info(lvl_info, &it, &nxt_level, nxt_sector);
		if (it != 0 || !level || !lvl_info)
		{
			ft_putstr("EXCEPTION > parser > invalid level data format\n");
			catch_exception(1);
		}
		ft_memdel((void **)&(lvl_info));
		loop_str_to_value(line, ";\0", level != NULL);
	}
	ft_memdel((void **)&level);
	return (nxt_level);
}
