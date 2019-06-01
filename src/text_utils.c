/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:13:09 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "parser.h"

static SDL_Color	set_color(int r, int g, int b)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

static SDL_Rect		get_location(void)
{
	SDL_Rect location;

	location.x = W / 2 - W / 3;
	location.y = H / 2 + H / 4;
	location.w = 100;
	location.h = 100;
	return (location);
}

static void			blit_massage_surface(char *mssg, SDL_Surface *surface,
										TTF_Font *font,
										SDL_Rect *location)
{
	SDL_Surface *surf_massage;

	surf_massage = TTF_RenderText_Shaded(font, mssg,
								set_color(255, 255, 255),
								set_color(0, 0, 0));
	SDL_BlitSurface(surf_massage, NULL, surface, location);
	if (surf_massage)
		SDL_FreeSurface(surf_massage);
}

void				render_massage(char *mssg, SDL_Surface *surface)
{
	static TTF_Font *font = NULL;
	static SDL_Rect location;

	if (ft_strequ(mssg, "#init"))
	{
		font = TTF_OpenFont("font/Roboto-Black.ttf", 24);
		if (font == NULL)
		{
			ft_putstr("EXCEPTION > font > invalid font file\n");
			catch_exception(1);
			return ;
		}
		location = get_location();
	}
	else if (ft_strequ(mssg, "#del"))
	{
		if (font)
		{
			TTF_CloseFont(font);
		}
	}
	else
		blit_massage_surface(mssg, surface, font, &location);
}

void				message(char *file, player *p, SDL_Surface *surface)
{
	if (!p || !surface)
	{
		render_massage(file, NULL);
		return ;
	}
	text_pattern_0(file, p, surface);
	text_pattern_01(file, p, surface);
	text_pattern_1(file, p, surface);
	text_pattern_2(file, p, surface);
}
