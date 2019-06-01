/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:13:20 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "utils.h"

xy		new_xy(float x, float y){
	xy	xy;

	xy.x = x;
	xy.y = y;
	return (xy);
}
int		equals_float(float a, float b)
{
	if (a >= 0 && b < 0)
		return (COMPARE(a, ABS(b)));
	if (b >= 0 && a < 0)
		return (COMPARE(ABS(a), b));
	if (b < 0 && a < 0)
		return (COMPARE(ABS(a),ABS(b)));
	return (COMPARE(a, b));
}

int		equals_xy(xy a, xy b)
{
	int	eq_x;
	int	eq_y;

	eq_x = equals_float(a.x, b.x);
	eq_y = equals_float(a.y, b.y);
	return (eq_y && eq_x);
}

xyz		new_xyz(float x, float y, float z){
	xyz	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.z = z;
	return (xyz);
}
