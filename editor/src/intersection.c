/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:48:36 by mkachano          #+#    #+#             */
/*   Updated: 2019/03/23 16:48:39 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int				calc_intersect(t_line l1, t_line l2)
{
	double v1;
	double v2;
	double v3;
	double v4;

	v1 = (l2.x1 - l2.x0) * (l1.y0 - l2.y0) - (l2.y1 - l2.y0) * (l1.x0 - l2.x0);
	v2 = (l2.x1 - l2.x0) * (l1.y1 - l2.y0) - (l2.y1 - l2.y0) * (l1.x1 - l2.x0);
	v3 = (l1.x1 - l1.x0) * (l2.y0 - l1.y0) - (l1.y1 - l1.y0) * (l2.x0 - l1.x0);
	v4 = (l1.x1 - l1.x0) * (l2.y1 - l1.y0) - (l1.y1 - l1.y0) * (l2.x1 - l1.x0);
	if ((v1 * v2 < 0) && (v3 * v4 < 0))
		return (TRUE);
	return (FALSE);
}

int				is_line_intersect(t_shape *shape, int x, int y)
{
	int		lines_count;
	int		intersect;
	t_line	line1;
	t_line	line2;

	intersect = FALSE;
	lines_count = shape->point_count - 2;
	line1.x0 = x;
	line1.y0 = y;
	line1.x1 = shape->points[shape->point_count - 1].x;
	line1.y1 = shape->points[shape->point_count - 1].y;
	while (lines_count >= 0)
	{
		line2.x0 = shape->points[lines_count].x;
		line2.y0 = shape->points[lines_count].y;
		line2.x1 = shape->points[lines_count + 1].x;
		line2.y1 = shape->points[lines_count + 1].y;
		intersect = calc_intersect(line1, line2);
		if (intersect == TRUE)
			return (intersect);
		lines_count--;
	}
	return (intersect);
}

static	int		is_line_intersect_shapes_sec(t_app *app, int count, t_line l)
{
	t_shape	shape;
	int		lines_count;
	t_line	line2;
	int		intersect;

	lines_count = app->shapes[count].point_count - 2;
	shape = app->shapes[count];
	line2 = get_line(shape.points[0].x, shape.points[0].y,
			shape.points[lines_count + 1].x, shape.points[lines_count + 1].y);
	intersect = calc_intersect(l, line2);
	if (intersect == TRUE)
		return (intersect);
	while (lines_count >= 0)
	{
		line2 = get_line(shape.points[lines_count].x,
				shape.points[lines_count].y, shape.points[lines_count + 1].x,
				shape.points[lines_count + 1].y);
		intersect = calc_intersect(l, line2);
		if (intersect == TRUE)
			return (intersect);
		lines_count--;
	}
	return (FALSE);
}

int				is_line_intersect_shapes(t_app *app, t_point p1, t_point p2)
{
	int		count;
	t_line	line1;

	line1 = get_line(p1.x, p1.y, p2.x, p2.y);
	count = app->shapes_count - 1;
	if (count >= 0)
	{
		while (count >= 0)
		{
			if (is_line_intersect_shapes_sec(app, count, line1) == TRUE)
				return (TRUE);
			count--;
		}
	}
	return (FALSE);
}

int				is_point_intersect_shapes(t_app *app, t_point point)
{
	int	i;

	i = 0;
	while (i <= app->shapes_count - 1)
	{
		if (point_index_of_shapes(&app->shapes[i], point.x, point.y) == TRUE)
			return (FALSE);
		i++;
	}
	i = 0;
	while (i <= app->shapes_count - 1)
	{
		if (is_p_shape(&app->shapes[i], point) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
