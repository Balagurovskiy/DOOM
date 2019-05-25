/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:02:18 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/25 21:02:24 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static	int		error_usage(void)
{
	ft_putstr(" ./level_editor [file_map_name]\n");
	return (0);
}

static	void	zero_props(t_app *app)
{
	app->shapes_count = 0;
	ft_bzero(&app->current_shape, sizeof(t_shape));
	app->current_shape.roof_h = CELL_SIZE;
	app->current_shape.id = 0;
	app->map_saved = FALSE;
	app->menu_panel_id_shape = 0;
}

void			exit_app(t_app *app)
{
	TTF_CloseFont(app->font);
	app->ssurface = NULL;
	app->gtexture = NULL;
	app->window = NULL;
	app->renderer = NULL;
}

void			run_app(t_app *app)
{
	zero_props(app);
	while (app->quit_state)
	{
		listen_game_event(app);
		if (app->current_shape.locked == FALSE)
			render_game_scene(app);
		else
		{
			sort_shapes_sectors(&app->current_shape);
			app->shapes[app->shapes_count] = app->current_shape;
			app->shapes_count++;
			update_shape_neighbors(app, app->joint_sector, app->joint_sec_id);
			ft_bzero(&app->current_shape, sizeof(app->current_shape));
			app->current_shape.roof_h = CELL_SIZE;
			app->current_shape.id = app->shapes_count;
			app->menu_panel_id_shape = app->current_shape.id - 1;
			app->menu_panel.selector_button.max_value = app->shapes_count - 1;
			update_menu_panel(app);
		}
	}
	if (save_map(app) == TRUE)
		ft_putstr("[SUCCESS]: File saved!\n");
	else
		error_open_file(app->fname);
	app->map_saved = TRUE;
}

int				main(int argc, char **argv)
{
	t_app		app;

	if (argc < 2)
	{
		if (error_usage() == 0)
			return (0);
	}
	ft_bzero(&app, sizeof(t_app));
	app.fname = ft_strdup(argv[1]);
	app.map_file_fd = open(app.fname, O_DIRECTORY);
	if (app.map_file_fd >= 0)
		error_folder(app.fname);
	else
	{
		init_app(&app);
		init_window(&app);
		init_menu_panel(&app);
		(app.quit_state & STATE_QUIT) ?
			exit_app(&app) : run_app(&app);
		exit_app(&app);
	}
	system("leaks level_editor");
	return (0);
}
