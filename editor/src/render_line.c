/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 20:01:32 by mkachano          #+#    #+#             */
/*   Updated: 2019/03/17 20:01:35 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static	void			render_line_low(t_app *app, t_line line)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = dy * (-1);
	}
	d = 2 * dy - dx;
	while (line.x0 < line.x1)
	{
		render_point_wrapper(app, line.x0, line.y0);
		if (d > 0)
		{
			line.y0 = line.y0 + yi;
			d = d - 2 * dx;
		}
		d = d + 2 * dy;
		line.x0 += 1;
	}
}

static	void			render_line_high(t_app *app, t_line line)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = dx * (-1);
	}
	d = 2 * dx - dy;
	while (line.y0 < line.y1)
	{
		render_point_wrapper(app, line.x0, line.y0);
		if (d > 0)
		{
			line.x0 = line.x0 + xi;
			d = d - 2 * dy;
		}
		d = d + 2 * dx;
		line.y0 += 1;
	}
}

t_line					get_line(int x0, int y0, int x1, int y1)
{
	t_line	line;

	line.x0 = x0;
	line.y0 = y0;
	line.x1 = x1;
	line.y1 = y1;
	return (line);
}

int						draw_line(t_app *app, t_line line_p)
{
	t_line line;

	if (abs(line_p.y1 - line_p.y0) < abs(line_p.x1 - line_p.x0))
	{
		if (line_p.x0 > line_p.x1)
			line = get_line(line_p.x1, line_p.y1, line_p.x0, line_p.y0);
		else
			line = get_line(line_p.x0, line_p.y0, line_p.x1, line_p.y1);
		line.color = line_p.color;
		render_line_low(app, line);
	}
	else
	{
		if (line_p.y0 > line_p.y1)
			line = get_line(line_p.x1, line_p.y1, line_p.x0, line_p.y0);
		else
			line = get_line(line_p.x0, line_p.y0, line_p.x1, line_p.y1);
		line.color = line_p.color;
		render_line_high(app, line);
	}
	return (0);
}
