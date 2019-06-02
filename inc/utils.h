/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:48 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct	s_xy
{
	float	x;
	float	y;
}				t_xy;

typedef struct	s_xyz
{
	float x;
	float y;
	float z;
}				t_xyz;

t_xy			new_xy(float x, float y);
int				equals_xy(t_xy a, t_xy b);
int				equals_float(float a, float b);

t_xyz			new_xyz(float x, float y, float z);

int				point_is_on_line(t_xy point, t_xy l0, t_xy ln);

t_xy			intersect(t_xy xy1, t_xy xy2, t_xy xy3, t_xy xy4);

int				intersect_box(t_xy xy0, t_xy xy1, t_xy xy2, t_xy xy3);

int				intersect_box_handle(t_xy p, t_xy d, t_xy *vert, int s);

float			point_side(t_xy p, t_xy xy0, t_xy xy1);

float			point_side_handle(t_xy p, t_xy d, t_xy *vert, int s);

int				intersert_circle_bound(t_xy line_p0,
										t_xy line_pn,
										t_xy center,
										float radius);

#endif
