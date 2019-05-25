/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:20:58 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/20 20:20:59 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int				load_icons(t_app *app)
{
	int		i;
	char	*files[6];

	i = 0;
	files[0] = "./images/textures-icons/wall0.png";
	files[1] = "./images/textures-icons/wall1.png";
	files[2] = "./images/textures-icons/wall2.png";
	files[3] = "./images/textures-icons/wall3.png";
	files[4] = "./images/textures-icons/wall4.png";
	files[5] = "./images/textures-icons/wall5.png";
	while (i < 6)
	{
		app->tmp_surface = load_image(files[i]);
		app->icons[i].texture = SDL_CreateTextureFromSurface(
				app->renderer, app->tmp_surface);
		app->icons[i].rect.w = app->tmp_surface->w / 2 - 2;
		app->icons[i].rect.h = app->tmp_surface->h / 2 - 2;
		SDL_FreeSurface(app->tmp_surface);
		i++;
	}
}

int				load_assets(t_app *app)
{
	app->tmp_surface = load_image("./images/menu/menu.png");
	app->menu_background = SDL_CreateTextureFromSurface(
			app->renderer, app->tmp_surface);
	SDL_FreeSurface(app->tmp_surface);
	app->tmp_surface = load_image("./images/button/button.png");
	app->test_texture.texture = SDL_CreateTextureFromSurface(
			app->renderer, app->tmp_surface);
	app->test_texture.rect.w = app->tmp_surface->w;
	app->test_texture.rect.h = app->tmp_surface->h;
	SDL_FreeSurface(app->tmp_surface);
	app->tmp_surface = load_image("./images/button/minus.png");
	app->textures[MINUS_TEXTURE].texture = SDL_CreateTextureFromSurface(
			app->renderer, app->tmp_surface);
	app->textures[MINUS_TEXTURE].rect.w = app->tmp_surface->w;
	app->textures[MINUS_TEXTURE].rect.h = app->tmp_surface->h;
	SDL_FreeSurface(app->tmp_surface);
	app->tmp_surface = load_image("./images/button/plus.png");
	app->textures[PLUS_TEXTURE].texture = SDL_CreateTextureFromSurface(
			app->renderer, app->tmp_surface);
	app->textures[PLUS_TEXTURE].rect.w = app->tmp_surface->w;
	app->textures[PLUS_TEXTURE].rect.h = app->tmp_surface->h;
	SDL_FreeSurface(app->tmp_surface);
	load_fonts(app);
	load_icons(app);
	return (TRUE);
}

void			init_render(t_app *app)
{
	Uint32			render_flags;

	render_flags = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	app->renderer = SDL_CreateRenderer(app->window, -1, render_flags);
	(app->renderer == NULL) ?\
	error_window_init("Render could not be created! SDL Error: ", app) : 0;
	SDL_SetRenderDrawColor(app->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(app->renderer);
}

void			init_app(t_app *app)
{
	app->window = NULL;
	app->ssurface = NULL;
	app->renderer = NULL;
	app->gtexture = NULL;
	app->game_state = STATE_MAIN;
	app->quit_state = 1;
}

void			init_window(t_app *app)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		ft_putstr(SDL_GetError());
		app->quit_state = STATE_QUIT;
	}
	if (!(app->quit_state & STATE_QUIT))
	{
		(TTF_Init() == -1) ? error_ttf_init() : 0;
		(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) ? \
		ft_putstr("Warning: Linear texture filtering not enabled!\n") : 0;
		app->window = SDL_CreateWindow("DOOM NUKEM LEVEL EDITOR",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		(app->window == NULL) ?\
		error_window_init("Window could not be created! SDL_Error: ", app) : 0;
		(!(app->quit_state & STATE_QUIT)) ? init_render(app) : 0;
		(!(app->quit_state & STATE_QUIT)) ? load_assets(app) : 0;
	}
}
