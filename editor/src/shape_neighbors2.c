/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_neighbors2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:15:19 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/19 18:17:26 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static int		is_shape_has_sector(t_shape *shape, t_line line)
{
	t_point point2;

	point2.x = line.x1;
	point2.y = line.y1;
	shape->i = point_index_of_shapes(shape, line.x0, line.y0);
	if (shape->i > -1)
		return (check_point_neighbor_match(shape, shape->i, point2));
	return (FALSE);
}

static	void	update_neigh(t_shape *shape, t_line line, int shape_id)
{
	int index1;
	int index2;
	int point_index;

	index1 = point_index_of_shapes(shape, line.x0, line.y0);
	index2 = point_index_of_shapes(shape, line.x1, line.y1);
	point_index = get_neighbor_index(index1, index2);
	if (shape->sector_neighbor_id[point_index] == -1)
		shape->sector_neighbor_id[point_index] = shape_id;
}

static	void	update_default_neighbors(t_app *app, int shape_id)
{
	int i;

	i = 0;
	while (i < app->shapes[shape_id].point_count)
	{
		app->shapes[shape_id].sector_neighbor_id[i] = -1;
		i++;
	}
}

void			update_shape_neighbors(t_app *app, t_line line, int shape_id)
{
	int i;
	int n;
	int in;

	update_default_neighbors(app, shape_id);
	if (shape_id == 0)
		return ;
	i = 0;
	while (i < shape_id)
	{
		if (is_shape_has_sector(&app->shapes[i], line) == TRUE)
		{
			n = get_validation_p_id(app->shapes[i].i, app->shapes[i].j);
			in = is_p_shape(&app->shapes[shape_id], app->shapes[i].points[n]);
			if (in == TRUE)
				app->shapes_count--;
			if (in == FALSE)
			{
				update_neigh(&app->shapes[i], line, shape_id);
				update_neigh(&app->shapes[shape_id], line, app->shapes[i].id);
			}
			return ;
		}
		i++;
	}
}
