/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:26:57 by mkachano          #+#    #+#             */
/*   Updated: 2019/04/06 16:36:56 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

void		render_shape(t_app *app, t_shape shape)
{
	int		i;
	t_line	line;
	t_point	point;
	t_point	point2;

	i = 1;
	while (i < shape.point_count)
	{
		point = shape.points[i - 1];
		point2 = shape.points[i];
		line.x0 = point.x;
		line.y0 = point.y;
		line.x1 = point2.x;
		line.y1 = point2.y;
		draw_line(app, line);
		i++;
	}
}

void		render_shapes(t_app *app)
{
	int		count;
	t_shape	shape;

	count = app->shapes_count - 1;
	while (count >= 0)
	{
		shape = app->shapes[count];
		render_shape(app, shape);
		count--;
	}
}

void		render_shape_control_points(t_app *app, t_shape shape)
{
	int		i;
	t_point	point;

	i = 1;
	while (i < shape.point_count)
	{
		point = shape.points[i - 1];
		draw_point(app, point.x, point.y);
		i++;
	}
}

void		render_shapes_control_points(t_app *app)
{
	int		i;
	int		count;
	t_shape	shape;
	t_point	point;

	count = app->shapes_count - 1;
	while (count >= 0)
	{
		shape = app->shapes[count];
		render_shape_control_points(app, shape);
		count--;
	}
}
