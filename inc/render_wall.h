/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:44 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WALL_H
# define RENDER_WALL_H

# include "render.h"
# include "render_heights.h"

typedef struct	s_ceiling_floor
{
	float	hei;
	float	mapx;
	float	mapz;
	int		with_shade;
	int		x;
	int		y;
	int		z;
}				t_ceiling_floor;

typedef struct	s_wall
{
	int	z;
	int	ya;
	int	yb;
	int	cya;
	int	cyb;
	int	nya;
	int	nyb;
	int	cnya;
	int	cnyb;
}				t_wall;

int				fade_to_black(int col, double curr, double max);

void			render_the_wall(t_screen *scrn,
								t_perspective perspect,
								t_heights heights,
								int s);
t_perspective	perspective_init(t_edge edge);
void			view_intersection_with_wall(t_screen *scrn);
void			render_floor_ceil(t_screen *scrn,
									t_wall wall,
									t_heights heights,
									int x);

#endif
