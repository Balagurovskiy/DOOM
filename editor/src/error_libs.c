/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_libs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:00:34 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/25 21:00:36 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int			error_image_init(char *message, t_app *app)
{
	ft_putstr(message);
	ft_putstr(IMG_GetError());
	app->quit_state = STATE_QUIT;
	return (1);
}

int			error_window_init(char *message, t_app *app)
{
	ft_putstr(message);
	ft_putstr(SDL_GetError());
	app->quit_state = STATE_QUIT;
	return (1);
}

void		error_ttf_init(void)
{
	ft_putstr("Init SDL_Error: \n");
	ft_putstr(SDL_GetError());
	exit(2);
}
