/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static SDL_Rect		set_location(int x, int y, int w, int h)
{
	SDL_Rect location;

	location.x = x;
	location.y = y;
	location.w = w;
	location.h = h;
	return (location);
}

void				render_hud_text(char *mssg, SDL_Surface *surface,
												SDL_Rect location)
{
	static TTF_Font *font = NULL;

	if (ft_strequ(mssg, "#init"))
	{
		font = TTF_OpenFont("font/Roboto-Black.ttf", 16);
		if (font == NULL)
		{
			ft_putstr("EXCEPTION > font > invalid font file\n");
			catch_exception(1);
			return ;
		}
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

void				hud_pattern(t_player *p, SDL_Surface *surface)
{
	SDL_Rect	location;
	char		*hud_ints;

	location = set_location(W / 4, H, 50, 20);
	render_hud_text("NOTES", surface, location);
	location = set_location(W / 2, H, 50, 20);
	render_hud_text("HEALTH", surface, location);
	location.y = H + 25;
	hud_ints = ft_itoa(p->health);
	render_hud_text(hud_ints, surface, location);
	ft_memdel((void **)&hud_ints);
	location = set_location((W - W / 4), H, 50, 20);
	render_hud_text("KEYS", surface, location);
	location.y = H + 25;
	hud_ints = ft_itoa(p->key);
	render_hud_text(hud_ints, surface, location);
	ft_memdel((void **)&hud_ints);
}

void				draw_hud(char *tag, t_player *p, SDL_Surface *surface)
{
	SDL_Rect	location;

	location = set_location(0, H, W, 20);
	SDL_FillRect(surface, &location, 0xAC9E9C);
	location = set_location(0, H + 20, W, 40);
	SDL_FillRect(surface, &location, 0x0);
	if (!p || !surface)
	{
		render_hud_text(tag, NULL, location);
		return ;
	}
	hud_pattern(p, surface);
}
