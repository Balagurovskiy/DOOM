/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:54:18 by mkachano          #+#    #+#             */
/*   Updated: 2018/10/28 13:54:22 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

SDL_Surface			*load_image(char *path)
{
	SDL_Surface		*converted;
	SDL_Surface		*tmp;
	SDL_PixelFormat	pixel_format;
	Uint32			color_key;

	tmp = NULL;
	converted = NULL;
	pixel_format.BitsPerPixel = 32;
	pixel_format.BytesPerPixel = 4;
	pixel_format.palette = NULL;
	pixel_format.Rmask = 0;
	pixel_format.Gmask = 0;
	pixel_format.Bmask = 0;
	pixel_format.Amask = 0;
	if ((tmp = IMG_Load(path)) != NULL)
	{
		converted = SDL_ConvertSurface(tmp, &pixel_format, 0);
		color_key = SDL_MapRGB(converted->format, 0, 0, 0);
		SDL_SetColorKey(converted, SDL_RLEACCEL, color_key);
	}
	SDL_FreeSurface(tmp);
	return (converted);
}
