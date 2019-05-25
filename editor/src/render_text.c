/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:01:53 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/05 12:01:54 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int		load_fonts(t_app *app)
{
	app->font = TTF_OpenFont("./fonts/roboto-bold.ttf", 22);
	if (!app->font)
	{
		ft_putendl(SDL_GetError());
		return (0);
	}
	return (1);
}

void	create_text(t_app *app, char *text, t_text *text_obj, t_point point)
{
	int				width;
	int				height;
	SDL_Surface		*text_surface;
	SDL_Color		rgb;

	rgb.r = 255;
	rgb.g = 255;
	rgb.b = 255;
	text_surface = TTF_RenderText_Solid(app->font, text, rgb);
	text_obj->texture = SDL_CreateTextureFromSurface(app->renderer,
			text_surface);
	SDL_QueryTexture(text_obj->texture, NULL, NULL, &width, &height);
	text_obj->rectangle.x = point.x;
	text_obj->rectangle.y = point.y;
	text_obj->rectangle.w = width;
	text_obj->rectangle.h = height;
	SDL_FreeSurface(text_surface);
}

int		render_text(t_app *app)
{
	SDL_RenderCopy(app->renderer, app->menu_panel.ceil.texture,
			NULL, &app->menu_panel.ceil.rectangle);
	SDL_RenderCopy(app->renderer, app->menu_panel.floor.texture,
			NULL, &app->menu_panel.floor.rectangle);
	SDL_RenderCopy(app->renderer, app->menu_panel.sector.texture,
			NULL, &app->menu_panel.sector.rectangle);
}
