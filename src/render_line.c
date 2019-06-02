/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:25 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "render.h"

t_txt_line		set_textured_line(int x, int y1, int y2)
{
	t_txt_line tl;

	tl.x = x;
	tl.y1 = y1;
	tl.y2 = y2;
	return (tl);
}

float			to_black(float chanel, double current, double max)
{
	float result;

	result = chanel * ((max - (current - 15)) / max);
	if (result > chanel)
		return (chanel);
	return (result);
}

int				fade_to_black(int color, double current, double max)
{
	double		rgb[3];
	int			i;

	if (current < 0)
		return (current);
	if (current >= max)
		current = max;
	rgb[0] = color & 255;
	rgb[1] = (color >> 8) & 255;
	rgb[2] = (color >> 16) & 255;
	i = 3;
	while (i--)
		rgb[i] = to_black(rgb[i], current, max);
	return (rgb[0] + ((int)rgb[1] << 8) + (((int)rgb[2]) << 16));
}

void			textured_line(t_screen *scrn, t_txt_line tl,
								SDL_Surface *t, int z)
{
	int	y;
	int	*pixels;
	int	txtz;
	int	txtx;

	pixels = (int*)scrn->surface->pixels;
	tl.y1 = CLAMP(tl.y1, 0, H - 1);
	tl.y2 = CLAMP(tl.y2, 0, H - 1);
	pixels += tl.y1 * W + tl.x;
	y = tl.y1;
	while (y <= tl.y2)
	{
		txtz = scaler_next(&(tl.scale_ty)) % t->h;
		txtx = scrn->txt_data.txtx % t->w;
		if (TXT_IN && TXT_PIX != 0x0)
			*pixels = fade_to_black(TXT_PIX, z, BLACK_DIST);
		pixels += W;
		++y;
	}
}
