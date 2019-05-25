/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:35:29 by mkachano          #+#    #+#             */
/*   Updated: 2019/03/23 16:35:32 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int		update_shape_locked_state(t_shape *shape)
{
	int i;

	i = 1;
	if (shape->points[0].x == shape->points[shape->point_count - 1].x &&
		shape->points[0].y == shape->points[shape->point_count - 1].y)
	{
		shape->locked = TRUE;
		shape->x_max = shape->points[0].x;
		shape->x_min = shape->points[0].x;
		shape->y_max = shape->points[0].y;
		shape->y_min = shape->points[0].y;
		while (i < shape->point_count)
		{
			if (shape->points[i].x > shape->x_max)
				shape->x_max = shape->points[i].x;
			if (shape->points[i].x < shape->x_min)
				shape->x_min = shape->points[i].x;
			if (shape->points[i].y > shape->y_max)
				shape->y_max = shape->points[i].y;
			if (shape->points[i].y < shape->y_min)
				shape->y_min = shape->points[i].y;
			i++;
		}
	}
	return (shape->locked);
}

int		point_index_of_shapes(t_shape *shape, int x, int y)
{
	int			i;
	t_shape		*s;

	i = 0;
	s = shape;
	while (i < s->point_count)
	{
		if (s->points[i].x == x && s->points[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

int		is_point_control(t_app *app, int x, int y)
{
	int			count;
	t_shape		shape;

	count = app->shapes_count - 1;
	if (count >= 0)
	{
		while (count >= 0)
		{
			shape = app->shapes[count];
			if (point_index_of_shapes(&shape, x, y) > -1)
				return (TRUE);
			count--;
		}
	}
	return (FALSE);
}

int		check_point_neighbor_match(t_shape *shape, int index, t_point p)
{
	int point_count;
	int next_index;
	int prev_index;

	point_count = shape->point_count - 1;
	if (index < point_count)
		next_index = index + 1;
	if (index == point_count)
		next_index = 0;
	if (index == 0)
		prev_index = point_count - 1;
	if (index > 0)
		prev_index = index - 1;
	if (is_point_equal(shape->points[next_index], p) == TRUE)
	{
		shape->j = next_index;
		return (TRUE);
	}
	if (is_point_equal(shape->points[prev_index], p) == TRUE)
	{
		shape->j = shape->i;
		shape->i = prev_index;
		return (TRUE);
	}
	return (FALSE);
}

int		is_shapes_has_segment(t_app *app, t_point p1, t_point p2)
{
	int		count;
	int		index;
	int		count_shapes;

	count_shapes = 0;
	count = app->shapes_count - 1;
	if (count >= 0)
	{
		while (count >= 0)
		{
			index = point_index_of_shapes(&app->shapes[count], p2.x, p2.y);
			if (index > -1)
			{
				if (check_point_neighbor_match(&app->shapes[count],
						index, p1) == TRUE)
					count_shapes++;
			}
			count--;
		}
	}
	if (count_shapes == 1)
		return (TRUE);
	return (FALSE);
}
