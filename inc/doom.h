/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:23 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "defines.h"
# include "utils.h"

/*
** Sectors: Floor and ceiling height; list of edge vertices and neighbors
*/
typedef struct		s_sectors
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	int				*neighbors;
	unsigned int	npoints;

	int				object;
	t_xy			object_xy[2];
}					t_sectors;

/*
** Player data
** 	Current position
** 	Current motion vector
** 	Looking towards (and sin() and cos() thereof)
** 	Which sector the t_player is currently in
*/
typedef struct		s_player
{
	t_xyz			where;
	t_xyz			velocity;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;
	unsigned int	sector;
	unsigned int	total_sectors;

	int				exit_doom;

	int				health;

	int				action;
	int				key;

	float			gravity;
}					t_player;

/*
** save player data for next level
*/
typedef struct		s_player_save
{
	int				next_start;
	char			*next_lvl_temp;
	float			angle;
	int				key;
	int				health;

}					t_player_save;

typedef struct		s_texture_set
{
	SDL_Surface		*floortexture;
	SDL_Surface		*ceiltexture;
	SDL_Surface		*uppertextures;
	SDL_Surface		*lowertextures;

	SDL_Surface		*sky;
	SDL_Surface		*door;
	SDL_Surface		*dec[5];
	SDL_Surface		*key[7];

	SDL_Surface		*current;
}					t_texture_set;

typedef struct		s_level
{
	t_sectors		*sector;
	t_texture_set	texture;
	int				sectors_size;
	int				start[3];
	int				end[3];
	char			*next_level[3];
}					t_level;

# define START_POS (ps.next_start >= 0)
# define START_IN (ps.next_start < lvl->sectors_size)
# define NEXT_LVLV_IS_VALID (map_temp && START_POS && START_IN)

void				render_screen(SDL_Surface *srf,
									t_player *pl,
									t_level *lvl,
									int is_obj);
void				events(t_level *lvl,
							t_player *player,
							SDL_Window *win,
							SDL_Surface *surface);

void				change_level(t_level *lvl, t_player *p);
void				goto_level(t_level *lvl, t_player *p, char *level_name);

void				action_controller(t_player *player,
										t_level *lvl, char *file);
void				door0000(t_player *p, t_level *lvl, char *file);

void				free_level(t_level *level);
void				free_texture_set(t_texture_set *t);

void				music(char *tag);

void				blit_massage_surface(char *mssg,
										SDL_Surface *surface,
										TTF_Font *font,
										SDL_Rect *location);
void				render_massage(char *mssg, SDL_Surface *surface);
void				message(char *file, t_player *p, SDL_Surface *surface);
void				text_pattern_0(char *file, t_player *p,
								SDL_Surface *surface);
void				text_pattern_01(char *file, t_player *p,
								SDL_Surface *surface);
void				text_pattern_1(char *file, t_player *p,
								SDL_Surface *surface);
void				text_pattern_2(char *file, t_player *p,
								SDL_Surface *surface);

void				draw_hud(char *tag, t_player *p, SDL_Surface *surface);

char				*save_file(char *file);

int					ft_timer();

#endif
