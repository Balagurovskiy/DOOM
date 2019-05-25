/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:01:10 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/25 21:01:15 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

void		add_point_sector(t_shape *shape, t_point point)
{
	int index;

	index = shape->point_count;
	shape->points[index].x = point.x;
	shape->points[index].y = point.y;
	shape->point_count += 1;
}

void		on_mouse_click_up(t_app *app)
{
	int		x;
	int		y;
	t_point	point_click;
	t_point	point;

	SDL_GetMouseState(&x, &y);
	point.x = x;
	point.y = y;
	point_click = get_valid_point_position(x, y);
	if (app->current_shape.point_count == 0)
		app->mouse_move = point_click;
	if (y > 80)
	{
		edit_game_scene(app, point_click);
	}
	else
	{
		if (app->current_shape.point_count == 0 && app->shapes_count > 0)
			edit_menu(app, point);
	}
}

void		on_mouse_move(t_app *app)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	if (app->current_shape.point_count > 0)
	{
		app->mouse_move.x = x;
		app->mouse_move.y = y;
	}
}

void		listen_game_event(t_app *app)
{
	if (SDL_PollEvent(&app->event))
	{
		if (app->event.type == SDL_MOUSEBUTTONUP)
			on_mouse_click_up(app);
		if (app->event.type == SDL_MOUSEMOTION)
			on_mouse_move(app);
		app->keyboard_state = SDL_GetKeyboardState(NULL);
		(app->event.type == SDL_QUIT || \
		app->keyboard_state[SDL_SCANCODE_ESCAPE]) ? \
		(app->quit_state = 0) : 0;
		if (app->event.type == SDL_QUIT)
			app->quit_state = 0;
	}
}

void		render_grid(t_app *app)
{
	int		i;
	t_line	line;

	i = WINDOW_WIDTH;
	while (i)
	{
		if (i % CELL_SIZE == 0)
		{
			line = get_line(i, 0 + GRID_OFFSET_Y, i,
					WINDOW_HEIGHT + GRID_OFFSET_Y);
			draw_line(app, line);
		}
		i--;
	}
	i = WINDOW_HEIGHT;
	while (i)
	{
		if (i % CELL_SIZE == 0)
		{
			line = get_line(0, i + GRID_OFFSET_Y,
					WINDOW_WIDTH, i + GRID_OFFSET_Y);
			draw_line(app, line);
		}
		i--;
	}
}
