/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_level_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 11:50:25 by mkachano          #+#    #+#             */
/*   Updated: 2019/03/23 11:50:28 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static	void	update_map_offset(t_app *app)
{
	int		i;
	int		j;

	i = 0;
	while (i < app->shapes_count)
	{
		j = 0;
		while (j < app->shapes[i].point_count)
		{
			if (i == 0 && j == 0)
			{
				app->offset_x = app->shapes[i].points[j].x;
				app->offset_y = app->shapes[i].points[j].y;
			}
			else
			{
				if (app->offset_x > app->shapes[i].points[j].x)
					app->offset_x = app->shapes[i].points[j].x;
				if (app->offset_y > app->shapes[i].points[j].y)
					app->offset_y = app->shapes[i].points[j].y;
			}
			j++;
		}
		i++;
	}
}

void			save_texture(t_app *app, int fd)
{
	int i;

	i = 0;
	ft_putstr_fd("texture:{", fd);
	while (i < 4)
	{
		if (i)
			ft_putstr_fd(",", fd);
		ft_putstr_fd("textures/walls/wall", fd);
		save_number_fd((int)((app->menu_panel.icon_result[i])), fd);
		ft_putstr_fd(".png", fd);
		i++;
	}
	ft_putstr_fd("};\n", fd);
}

void			save_shape(t_shape s, int fd, int offset_x, int offset_y)
{
	int		i;

	i = 0;
	ft_putstr_fd("ceil:", fd);
	save_number_fd(s.roof_h, fd);
	ft_putstr_fd(";", fd);
	ft_putstr_fd("floor:", fd);
	save_number_fd(s.floor_h, fd);
	ft_putstr_fd(";", fd);
	ft_putstr_fd("sector:", fd);
	while (i < s.point_count - 1)
	{
		ft_putstr_fd("{", fd);
		save_number_fd((int)((s.points[i].x - offset_x) / CELL_SIZE), fd);
		ft_putstr_fd(",", fd);
		save_number_fd((int)((s.points[i].y - offset_y) / CELL_SIZE), fd);
		ft_putstr_fd(",", fd);
		save_number_fd(s.sector_neighbor_id[i], fd);
		ft_putstr_fd("}", fd);
		i++;
	}
	ft_putstr_fd(";", fd);
	ft_putstr_fd("\n", fd);
}

int				save_map(t_app *app)
{
	t_shape	shape;
	int		fd;
	int		i;

	i = 0;
	update_map_offset(app);
	if ((app->map_file_fd = open(app->fname, O_WRONLY | O_TRUNC)) != OPEN_ERROR)
	{
		if (app->shapes_count > 0)
		{
			fd = open(app->fname, O_WRONLY);
			save_texture(app, fd);
			while (i < app->shapes_count)
			{
				shape = app->shapes[i];
				save_shape(shape, fd, app->offset_x, app->offset_y);
				i++;
			}
			close(fd);
		}
		close(app->map_file_fd);
		return (TRUE);
	}
	return (FALSE);
}
