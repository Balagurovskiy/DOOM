/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:00:04 by mkachano          #+#    #+#             */
/*   Updated: 2018/10/28 14:00:06 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

void			render(t_app *app)
{
	SDL_FreeSurface(app->ssurface);
	SDL_RenderClear(app->renderer);
	SDL_RenderPresent(app->renderer);
}

void			render_button(t_app *app, t_button button)
{
	SDL_RenderCopy(app->renderer,
			button.texture.texture,
			NULL,
			&button.texture.rect);
}

void			render_menu_panel(t_app *app)
{
	int i;

	i = 0;
	SDL_RenderCopy(app->renderer, app->menu_background, NULL, NULL);
	render_button(app, app->menu_panel.selector_button.plus);
	render_button(app, app->menu_panel.selector_button.minus);
	render_button(app, app->menu_panel.ceil_button.plus);
	render_button(app, app->menu_panel.ceil_button.minus);
	render_button(app, app->menu_panel.floor_button.plus);
	render_button(app, app->menu_panel.floor_button.minus);
	render_button(app, app->menu_panel.save_button);
	while (i < 4)
	{
		render_button(app, app->menu_panel.icon_button[i]);
		i++;
	}
	render_text(app);
}

void			render_game_shapes(t_app *app)
{
	render_grid(app);
	app->render_shape = TRUE;
	SDL_SetRenderDrawColor(app->renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	render_shapes(app);
	SDL_SetRenderDrawColor(app->renderer, 0xFF, 0xDD, 0x99, 0xFF);
	render_shapes_control_points(app);
	if (app->current_shape.point_count == 0 && app->shapes_count > 0)
	{
		SDL_SetRenderDrawColor(app->renderer, 0x99, 0x00, 0xEE, 0xFF);
		render_shape(app, app->shapes[app->menu_panel_id_shape]);
		SDL_SetRenderDrawColor(app->renderer, 0xEE, 0x00, 0xEE, 0xFF);
		render_shape_control_points(app, app->shapes[app->menu_panel_id_shape]);
	}
	SDL_SetRenderDrawColor(app->renderer, 0xCC, 0xCC, 0xCC, 0xFF);
	render_shape(app, app->current_shape);
	app->render_shape = FALSE;
}

void			render_game_scene(t_app *app)
{
	t_point		point;
	t_line		line;
	t_shape		*shape;
	t_point		p;

	app->render_shape = FALSE;
	SDL_SetRenderDrawColor(app->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(app->renderer);
	SDL_SetRenderDrawColor(app->renderer, 0x22, 0x11, 0x00, 0xFF);
	render_game_shapes(app);
	shape = &app->current_shape;
	if (shape->point_count > 0)
	{
		p = get_valid_point_position(app->mouse_move.x, app->mouse_move.y);
		if (is_line_intersect(shape, p.x, p.y) == TRUE)
			SDL_SetRenderDrawColor(app->renderer, 0xFF, 0x00, 0x00, 0xFF);
		if (is_line_intersect_shapes(app,
				shape->points[shape->point_count - 1], p) == TRUE)
			SDL_SetRenderDrawColor(app->renderer, 0xFF, 0x00, 0x00, 0xFF);
		point = shape->points[shape->point_count - 1];
		line = get_line(point.x, point.y, p.x, p.y);
		draw_line(app, line);
	}
	render_menu_panel(app);
	SDL_RenderPresent(app->renderer);
}
