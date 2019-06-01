/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_point_side.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:13:15 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "utils.h"

float	point_side(xy p, xy xy0, xy xy1)
{
	float x1_x0;
	float y1_y0;
	float px_x0;
	float py_y0;

	x1_x0 = xy1.x - xy0.x;
	y1_y0 = xy1.y - xy0.y;
	px_x0 = p.x - xy0.x;
	py_y0 = p.y - xy0.y;
	return (VXS(x1_x0, y1_y0, px_x0, py_y0));
}

float	point_side_handle(xy p, xy d, xy *vert, int s)
{
	xy p_d;
	xy xy0;
	xy xy1;

	p_d.x = p.x + d.x;
	p_d.y = p.y + d.y;
	xy0.x = vert[s + 0].x;
	xy0.y = vert[s + 0].y;
	xy1.x = vert[s + 1].x;
	xy1.y = vert[s + 1].y;
	return (SIGN(point_side(p_d, xy0, xy1)));
}
