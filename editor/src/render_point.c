/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:05:23 by mkachano          #+#    #+#             */
/*   Updated: 2019/04/06 13:05:25 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int			is_point_equal(t_point p1, t_point p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return (TRUE);
	return (FALSE);
}

void		draw_point(t_app *app, int x, int y)
{
	SDL_RenderDrawPoint(app->renderer, x - 1, y - 1);
	SDL_RenderDrawPoint(app->renderer, x, y - 1);
	SDL_RenderDrawPoint(app->renderer, x + 1, y - 1);
	SDL_RenderDrawPoint(app->renderer, x - 1, y);
	SDL_RenderDrawPoint(app->renderer, x, y);
	SDL_RenderDrawPoint(app->renderer, x + 1, y);
	SDL_RenderDrawPoint(app->renderer, x - 1, y + 1);
	SDL_RenderDrawPoint(app->renderer, x, y + 1);
	SDL_RenderDrawPoint(app->renderer, x + 1, y + 1);
}

void		render_point_wrapper(t_app *app, int x, int y)
{
	SDL_RenderDrawPoint(app->renderer, x, y);
}
