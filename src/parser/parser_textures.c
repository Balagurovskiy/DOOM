/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 13:17:40 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:47:21 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	parse_texture_switch(char **txt_data, t_map **map, int *it)
{
	int	k;

	k = 0;
	(*it) = 0;
	while (txt_data && txt_data[k] && k < 4)
	{
		if ((*it) == 0)
			(*map)->floortexture = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 1)
			(*map)->ceiltexture = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 2)
			(*map)->uppertextures = ft_strjoin(txt_data[k], NULL);
		if ((*it) == 3)
			(*map)->lowertextures = ft_strjoin(txt_data[k], NULL);
		(*it) = iterate(4);
		k++;
	}
	k = 0;
	while (txt_data && txt_data[k])
		ft_memdel((void **)&(txt_data[k++]));
}

void	parse_texture(char *line, t_map **map)
{
	char	*txt;
	char	**txt_data;
	int		it;

	txt = cut_str_value(line, "texture:\0", ";\0");
	txt_data = ft_splinter(txt, ",{}");
	parse_texture_switch(txt_data, map, &it);
	if (it != 0 || !txt || !txt_data)
	{
		ft_putstr("EXCEPTION > parser > invalid texture data\n");
		catch_exception(1);
	}
	ft_memdel((void **)&(txt_data));
	ft_memdel((void **)&txt);
}
