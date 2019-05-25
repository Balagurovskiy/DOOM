/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:35:14 by mkachano          #+#    #+#             */
/*   Updated: 2018/10/25 19:35:16 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_LEVEL_EDITOR_H
# define DOOM_LEVEL_EDITOR_H


#include "SDL.h"
# include "SDL_image.h"
# include "SDL_timer.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"
# include <dirent.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define GRID_OFFSET_X 0
# define GRID_OFFSET_Y 0


# define CELL_SIZE 16


# define STATE_QUIT (1 << 2)
# define STATE_MAIN (1 << 0)
# define STATE_MENU (1 << 1)
# define STATE_PLAY (1 << 2)

# define MAP_START_VALID 1
# define MAP_INITED 2

# define TRUE 1
# define FALSE 0
# define OPEN_ERROR -1

# define MINUS_TEXTURE 0
# define PLUS_TEXTURE 1
# define SAVE_TEXTURE 2
# define ICONS_COUNT 6

# define MAX_SIZE 50
# define MIN_SIZE 0

# define MAX_POINT 4
# define MAX_SHAPE 20


typedef struct	s_line
{
    int		x0;
    int		y0;
    int		x1;
    int		y1;
    int		color;
}				t_line;

typedef struct		s_textures
{
	SDL_Surface		**ptr_texture;
	int				count;
	char			**names;
	char			**names_with_path;
}					t_textures;

typedef struct      s_texture
{
    SDL_Texture     *texture;
    SDL_Rect        rect;
}                   t_texture;

typedef struct		s_font
{
    TTF_Font		*text_font;
}   				t_font;


typedef struct		s_text
{
    SDL_Texture		*texture;
    SDL_Rect		rectangle;
}   				t_text;

typedef struct      s_button
{
    int             x;
    int             y;
    int             width;
    int             height;
    t_texture       texture;
}                   t_button;

typedef struct      s_ibutton
{
    t_button        plus;
    t_button        minus;
    t_text          value;
    int             max_value;
    int             min_value;
    int             x;
    int             y;
}                   t_ibutton;

typedef struct		s_point
{
	int 			x;
	int				y;
}                   t_point;

typedef struct      s_shape
{
	int             id;
	int             locked;
	int             active;
	int             floor_h;
	int             roof_h;
	t_point         points[100];
	int             point_count;
	int             sector_neighbor_id[MAX_POINT];
	int             i;
	int             j;
	int             x_max;
	int             x_min;
	int             y_max;
	int             y_min;
}                   t_shape;

typedef struct		s_menu
{
	SDL_Surface		*ptr_texture;
	int				status;
	int				rnd;
	int				count;
	char			**names;
	char			**names_with_path;
}					t_menu;



typedef struct      s_menu_panel
{
    int             icon_result[4];
    t_button        icon_button[4];
    t_text          sector;
    t_text          floor;
    t_text          ceil;
    t_ibutton    selector_button;
    t_ibutton    floor_button;
    t_ibutton    ceil_button;
    t_button        exit_button;
    t_button        save_button;
}                   t_menu_panel;

typedef struct		s_app
{

	int             render_shape;
	t_shape         current_shape;
	t_shape         shapes[100];
	int             shapes_count;
	int             map_file_fd;
	char            *fname;
    t_point         mouse_move;
	int             map_saved;
	int             offset_x;
	int             offset_y;

    TTF_Font		*font;

    SDL_Surface		*tmp_surface;
    SDL_Texture     *menu_background;
    SDL_Texture     *button_background;


    t_texture       test_texture;
    t_texture       textures[10];
    t_texture       icons[6];

    t_line          joint_sector;
	int             joint_sector_id;

    t_menu_panel    menu_panel;
    int             menu_panel_id_shape;

	t_menu			menu;

	SDL_Window		*window;
	SDL_Surface		*ssurface;
	SDL_Renderer	*renderer;
	SDL_Texture		*gtexture;
	SDL_Event		event;
	SDL_Event		mpevent;
	const Uint8		*keyboard_state;
	int				quit_state;
	int				game_state;
}					t_app;

int					error_window_init(char *message, t_app *app);
int					error_image_init(char *message, t_app *app);
void				error_open_file(char *path);
void                error_folder(char *path);
void				error_ttf_init(void);
void				error_open_folder(void);
t_ibutton        create_inc_button(int max_value, int min_value, t_texture minus, t_texture plus);

int                 handle_btn_click(t_button button, int x, int y);
int                 handle_inc_btn_click(t_ibutton button, int x, int y, int *value);

void				init_window(t_app *app);
void				init_app(t_app *app);
void				listen_game_event(t_app *app);
void                add_point_sector(t_shape *shape, t_point point);

void				render(t_app *app);
void				render_game_scene(t_app *app);
int					atoi_base(char *str, int base);
SDL_Surface			*load_image(char *path);
int					is_file(const char *path);
void				run_app(t_app *app);

void				exit_app(t_app *sc_control);


int					draw_line(t_app *app, t_line line_p);
void                save_number_fd(int number, int fd);

int					get_validation_p_id(int i, int j);
int                 save_map(t_app *app);
void                new_shape(t_shape *shape);
int                 update_shape_locked_state(t_shape *shape);
t_point             get_valid_point_position(int x, int y);
int                 is_line_intersect(t_shape *shape, int x, int y);
void                render_point_wrapper(t_app *app, int x, int y);

void                draw_point(t_app *app, int x, int y);
void                render_shapes(t_app *app);
void                render_shapes_control_points(t_app *app);
int                 is_point_control(t_app *app, int x, int y);
int                 is_shapes_has_segment(t_app *app, t_point p1, t_point p2);
int                 is_point_equal(t_point p1, t_point p2);
int                 point_index_of_shapes(t_shape *shape, int x, int y);
int                 calc_intersect(t_line l1, t_line l2);
int                 is_line_intersect_shapes(t_app *app, t_point p1, t_point p2);
t_line	            get_line(int x0, int y0, int x1, int y1);
void                update_shape_neighbors(t_app *app, t_line line, int shape_id);
int                 check_point_neighbor_match(t_shape *shape, int index, t_point p);
void                sort_shapes_sectors(t_shape *shape);
void                print_shape(t_shape *shape, char *id);
void                print_point(t_point point);
void                edit_game_scene(t_app *app, t_point point_click);
int                 is_p_shape(t_shape *shape, t_point point);
int                 is_point_intersect_shapes(t_app *app, t_point point);
int                 load_assets(t_app *app);
int                 load_fonts(t_app *app);
int				    render_text(t_app *app);
void                create_text(t_app *app, char *text, t_text *text_obj, t_point point);
void                init_menu_panel(t_app *app);
void                update_menu_panel(t_app *app);
char		        *itoa_extended(int n);
void                edit_menu(t_app *app, t_point point_click);
t_button            create_button(int x, int y, t_texture texture);
void                render_menu_panel(t_app *app);
void                render_shape(t_app *app, t_shape shape);
void                render_shape_control_points(t_app *app, t_shape shape);
void				render_game_shapes(t_app *app);
void				render_grid(t_app *app);

#endif
