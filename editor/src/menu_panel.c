/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_panel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 18:25:56 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/05 18:25:58 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

void			init_menu_panel(t_app *app)
{
	int	i;
	int	pos[4];

	i = 0;
	pos[0] = 50;
	pos[1] = 145;
	pos[2] = 215;
	pos[3] = 325;
	app->menu_panel.selector_button = create_inc_button(130, 5,
			app->textures[MINUS_TEXTURE], app->textures[PLUS_TEXTURE]);
	app->menu_panel.selector_button.max_value = 0;
	app->menu_panel.ceil_button = create_inc_button(320, 5,
			app->textures[MINUS_TEXTURE], app->textures[PLUS_TEXTURE]);
	app->menu_panel.floor_button = create_inc_button(505, 5,
			app->textures[MINUS_TEXTURE], app->textures[PLUS_TEXTURE]);
	app->menu_panel.save_button = create_button(560, 20, app->test_texture);
	while (i < 4)
	{
		app->menu_panel.icon_result[i] = i;
		app->menu_panel.icon_button[i] =
				create_button(pos[i], 55, app->icons[i]);
		i++;
	}
}

void			update_menu_panel(t_app *app)
{
	t_point	point;
	t_shape	shape;
	char	*str;

	if (app->menu_panel_id_shape < 0)
		return ;
	shape = app->shapes[app->menu_panel_id_shape];
	point.x = 100;
	point.y = 3;
	str = itoa_extended(app->menu_panel_id_shape);
	create_text(app, str, &app->menu_panel.sector, point);
	free(str);
	point.x += 180;
	str = itoa_extended(shape.roof_h);
	create_text(app, str, &app->menu_panel.ceil, point);
	free(str);
	point.x += 195;
	str = itoa_extended(shape.floor_h);
	create_text(app, str, &app->menu_panel.floor, point);
	free(str);
}

static	void	edit_menu2(t_app *app, t_point point_click)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		if (handle_btn_click(app->menu_panel.icon_button[i],
				point_click.x, point_click.y) == TRUE)
		{
			app->menu_panel.icon_result[i]++;
			if (app->menu_panel.icon_result[i] >= ICONS_COUNT)
				app->menu_panel.icon_result[i] = 0;
			app->menu_panel.icon_button[i].texture.texture =
					app->icons[app->menu_panel.icon_result[i]].texture;
		}
		i++;
	}
}

void			edit_menu(t_app *app, t_point point_click)
{
	t_shape		*shape;

	shape = &app->shapes[app->menu_panel_id_shape];
	if (handle_inc_btn_click(app->menu_panel.selector_button,
			point_click.x, point_click.y, &app->menu_panel_id_shape) == TRUE)
		update_menu_panel(app);
	if (handle_inc_btn_click(app->menu_panel.ceil_button,
			point_click.x, point_click.y, &shape->roof_h) == TRUE)
		update_menu_panel(app);
	if (handle_inc_btn_click(app->menu_panel.floor_button,
			point_click.x, point_click.y, &shape->floor_h) == TRUE)
		update_menu_panel(app);
	if (handle_btn_click(app->menu_panel.save_button,
			point_click.x, point_click.y) == TRUE)
		app->quit_state = 0;
	edit_menu2(app, point_click);
}
