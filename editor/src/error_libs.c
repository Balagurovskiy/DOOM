/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_libs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:08:55 by mkachano          #+#    #+#             */
/*   Updated: 2018/10/28 14:08:57 by mkachano         ###   ########.fr       */
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
