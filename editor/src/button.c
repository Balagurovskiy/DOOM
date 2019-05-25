/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:23:44 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/06 18:23:46 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

t_button		create_button(int x, int y, t_texture texture)
{
	t_button button;

	button.x = x;
	button.y = y;
	button.width = texture.rect.w;
	button.height = texture.rect.h;
	button.texture = texture;
	button.texture.rect.x = x;
	button.texture.rect.y = y;
	return (button);
}

t_ibutton		create_inc_button(int x, int y, t_texture minus, t_texture plus)
{
	t_ibutton button;

	button.plus = create_button(x, y, plus);
	button.minus = create_button(x, y + plus.rect.h, minus);
	button.min_value = MIN_SIZE;
	button.max_value = MAX_SIZE;
	return (button);
}

int				handle_btn_click(t_button button, int x, int y)
{
	if ((button.x < x) && ((button.width + button.x) > x) &&
		(button.y < y) && (button.height + button.y) > y)
		return (TRUE);
	return (FALSE);
}

int				handle_inc_btn_click(t_ibutton button, int x, int y, int *value)
{
	if ((*value) < button.max_value)
	{
		if (handle_btn_click(button.plus, x, y) == TRUE)
		{
			(*value)++;
			return (TRUE);
		}
	}
	if ((*value) > button.min_value)
	{
		if (handle_btn_click(button.minus, x, y) == TRUE)
		{
			(*value)--;
			return (TRUE);
		}
	}
	return (FALSE);
}
