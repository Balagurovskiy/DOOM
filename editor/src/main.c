/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:55:13 by mkachano          #+#    #+#             */
/*   Updated: 2018/10/28 13:55:15 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"


static int			error_usage(void)
{
	ft_putstr(" ./level_editor [file_map_name]\n");
	return (0);
}

void				exit_app(t_app *app)
{
//	SDL_DestroyTexture(app->gtexture);
//	SDL_FreeSurface(app->ssurface);
//	SDL_DestroyRenderer(app->renderer);
//	SDL_DestroyWindow(app->window);
//
//    SDL_DestroyTexture(app->font.text_texture);
//    SDL_FreeSurface(app->font.text_surface);
	TTF_CloseFont(app->font);

	app->ssurface = NULL;
	app->gtexture = NULL;
	app->window = NULL;
	app->renderer = NULL;


//	TTF_Quit();
//	IMG_Quit();
//	SDL_Quit();
}


void				run_app(t_app *app)
{
	app->shapes_count = 0;
	ft_bzero(&app->current_shape, sizeof(t_shape));
	app->current_shape.roof_h = CELL_SIZE;
	app->current_shape.id = 0;
	app->map_saved = FALSE;
	app->menu_panel_id_shape = 0;

	while (app->quit_state)
	{
		listen_game_event(app);

		if (app->current_shape.locked == FALSE)
			render_game_scene(app);
		else
		{
			sort_shapes_sectors(&app->current_shape);

			// // print_shape(&app->current_shape, "AFTER AFTER");

			app->shapes[app->shapes_count] = app->current_shape;
			app->shapes_count++;

			update_shape_neighbors(app, app->joint_sector, app->joint_sector_id);


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

int					main(int argc, char **argv)
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
		(app.quit_state & STATE_QUIT) ? exit_app(&app) : run_app(&app);
		exit_app(&app);
	}

	system("leaks level_editor");

	return (0);
}
