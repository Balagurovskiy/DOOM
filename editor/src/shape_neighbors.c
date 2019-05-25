/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:09:43 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/02 16:09:45 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int				get_validation_p_id(int i, int j)
{
	int min;
	int max;

	min = (i > j) ? j : i;
	max = (i > j) ? i : j;
	if ((max - min) == 1 && max != 3)
		return (max + 1);
	else if ((max - min) > 1)
		return (min + 1);
	return (0);
}

int				get_neighbor_index(int i, int j)
{
	if (i == 0 || j == 0)
	{
		if (i == 0)
			return ((j == (i + 1)) ? i : j);
		if (j == 0)
			return ((i == (j + 1)) ? j : i);
	}
	return ((i > j) ? j : i);
}

static	int		is_in_polygon(t_point p1, t_point p2, double x, double y)
{
	double xi;
	double yi;
	double xj;
	double yj;

	xi = (double)p1.x;
	yi = (double)p1.y;
	xj = (double)p2.x;
	yj = (double)p2.y;
	if (((yi > y) != (yj > y))
		&& (yj - yi != 0 && x < (xj - xi) * (y - yi) / (yj - yi) + xi))
		return (TRUE);
	return (FALSE);
}

int				is_p_shape(t_shape *shape, t_point point)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = 0;
	j = shape->point_count - 2;
	x = (double)point.x;
	y = (double)point.y;
	if (point.x < shape->x_min || point.x > shape->x_max ||
		point.y < shape->y_min || point.y > shape->y_max)
		return (FALSE);
	while (i < shape->point_count - 1)
	{
		if (is_in_polygon(shape->points[j], shape->points[i], x, y) == TRUE)
			return (TRUE);
		j = i++;
	}
	return (FALSE);
}

t_point			get_valid_point_position(int x, int y)
{
	t_point	point;
	int		mod_x;
	int		mod_y;

	mod_x = x % CELL_SIZE;
	mod_y = y % CELL_SIZE;
	x = x - mod_x;
	y = y - mod_y;
	point.x = x < 0 ? 0 : x;
	point.y = y < 0 ? 0 : y;
	return (point);
}
