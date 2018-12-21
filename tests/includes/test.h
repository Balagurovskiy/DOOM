/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woof.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <arudenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 15:21:05 by arudenko          #+#    #+#             */
/*   Updated: 2018/03/28 14:23:36 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOOF_H
# define WOOF_H

# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include <math.h>

# define WIDTH 1280
# define HEIGHT 1024
# define NUM_GUNS 4

typedef struct		s_wolf
{
	float			ppos_x;
	float			ppos_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			mv_speed;
	float			rot_speed;
	float			ra;
	float			rd_x;
	float			rd_y;
	float			rlx;
	float			rly;
	unsigned int	*buffer;
	unsigned int	*sight;
	int				hit;
	float			dd_x;
	float			dd_y;
	int				m_x;
	int				m_y;
	int				st_x;
	int				st_y;
	int				side;
	float			pwd;
	int				l_h;
	int				dr_s;
	int				dr_e;
	int				d;
	int				t_x;
	int				t_y;
	int				y;
	int				x;
	int				n;
	float			w_x;
	float			fl_xwall;
	float			fl_ywall;
	float			dist_wall;
	float			curr_dist;
	float			weight;
	int				fl_tx;
	int				fl_ty;
}					t_wolf;

typedef struct		s_sprite
{
	SDL_Surface		**frames;
	SDL_Rect		rect;
	int				fps;
	int				frametime;
	int				numframes;
	int				frametime_faces;
	int				fps_face;
	int				sn_face;
	int				sn;
	int				active;
	int				loop;
}					t_sprite;

typedef struct		s_sound
{
	Mix_Chunk		*chunks[5];
	Mix_Music		*back;
}					t_sound;

typedef struct		s_text
{
	TTF_Font		*font;
	SDL_Surface		*mesaga;
	SDL_Rect		text_rect;
	SDL_Color		text_color;
	int				bullet_left;
}					t_text;

typedef struct		s_obj
{
	float			sp_x;
	float			sp_y;
	float			inv_det;
	float			tr_x;
	float			tr_y;
	int				sprt_h;
	int				start_x;
	int				start_y;
	int				texture_x;
}					t_obj;

typedef struct		s_flist
{
	int				hor;
	int				vert;
	char			*line;
	char			*param;
	struct s_flist	*next;
}					t_flist;

typedef struct		s_sdl_manage
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Event		ev;
	SDL_Surface		**im_surf;
	SDL_Surface		*win_surface;
	SDL_Surface		*status_line;
	SDL_Rect		line_rect;
	SDL_Rect		chain_rect;
	int				**floor;
	t_wolf			*map;
	int				num;
	struct s_flist	*begin;
	t_sprite		*guns;
	t_sprite		face;
	t_sprite		fuck;
	t_text			text;
	t_obj			obj;
	SDL_Rect		face_rect;
	int				active_gun;
	int				current_gun;
	SDL_Surface		**menus;
	SDL_Rect		im[2];
	int				shoot;
	int				x;
	int				y;
	struct s_sound	sound;
}					t_sdl_manange;

#endif
