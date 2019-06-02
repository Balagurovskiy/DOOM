/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_heights.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:40 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_HEIGHTS_H
# define RENDER_HEIGHTS_H

# include "render.h"

typedef struct		s_heights
{
	float		yceil;
	float		yfloor;
	float		neighb_yceil;
	float		neighb_yfloor;
	float		beginx;
	float		endx;

	t_scaler	ya;
	t_scaler	yb;
	t_scaler	neighb_ya;
	t_scaler	neighb_yb;
	t_scaler	z;
}					t_heights;

t_heights			heights_init(t_screen *scrn, t_perspective perspect, int s);

#endif
