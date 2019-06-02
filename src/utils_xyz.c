/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:38 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "utils.h"

t_xy		new_xy(float x, float y)
{
	t_xy	xy;

	xy.x = x;
	xy.y = y;
	return (xy);
}

int			equals_float(float a, float b)
{
	if (a >= 0 && b < 0)
		return (COMPARE(a, ABS(b)));
	if (b >= 0 && a < 0)
		return (COMPARE(ABS(a), b));
	if (b < 0 && a < 0)
		return (COMPARE(ABS(a), ABS(b)));
	return (COMPARE(a, b));
}

int			equals_xy(t_xy a, t_xy b)
{
	int	eq_x;
	int	eq_y;

	eq_x = equals_float(a.x, b.x);
	eq_y = equals_float(a.y, b.y);
	return (eq_y && eq_x);
}

t_xyz		new_xyz(float x, float y, float z)
{
	t_xyz	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}
