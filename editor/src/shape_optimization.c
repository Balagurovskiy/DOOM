/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_optimization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:27:52 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/03 14:27:54 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int			is_shape_clockwise(t_shape *shape)
{
	int i;
	int j;
	int sum;

	i = 0;
	j = 1;
	sum = 0;
	while (i < shape->point_count - 1)
	{
		if (j == shape->point_count - 1)
			j = 0;
		sum += ((shape->points[j].x - shape->points[i].x)
				* (shape->points[j].y + shape->points[i].y));
		i++;
		j++;
	}
	if (sum > 0)
		return (FALSE);
	return (TRUE);
}

void		sort_shapes_sectors(t_shape *shape)
{
	int		i;
	int		j;
	t_point	points[MAX_POINT + 10];

	if (is_shape_clockwise(shape) == FALSE)
	{
		i = shape->point_count;
		j = 0;
		while (i >= 0)
		{
			points[j].x = shape->points[i - 1].x;
			points[j].y = shape->points[i - 1].y;
			i--;
			j++;
		}
		i = shape->point_count;
		j = 0;
		while (i >= 0)
		{
			shape->points[j].x = points[j].x;
			shape->points[j].y = points[j].y;
			i--;
			j++;
		}
	}
}

int			is_shape_convex(t_shape s)
{
	int		sign;
	int		i;
	int		n;
	double	cross;

	sign = FALSE;
	i = 0;
	n = s.point_count - 1;
	while (n > i)
	{
		s.dx1 = s.points[(i + 2) % n].x - s.points[(i + 1) % n].x;
		s.dy1 = s.points[(i + 2) % n].y - s.points[(i + 1) % n].y;
		s.dx2 = s.points[i].x - s.points[(i + 1) % n].x;
		s.dy2 = s.points[i].y - s.points[(i + 1) % n].y;
		cross = s.dx1 * s.dy2 - s.dy1 * s.dx2;
		if (i == 0)
			sign = (cross > 0) ? TRUE : FALSE;
		else
		{
			if (sign != ((cross > 0) ? TRUE : FALSE))
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
