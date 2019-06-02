/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:30 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# define DUCK_KOEF(k) ((me->ducking == 1) ? (k / 1.5) : 0.0)
# define SPEED_KOEF(k) (k - DUCK_KOEF(k));

# define JUMP_HEIGHT (EYE_HEIGHT + PLAYER_SECT.floor + player->velocity.z)
# define NEXTZ (player->where.z + player->velocity.z)
# define UNDER_CEIL (NEXTZ < PLAYER_SECT.floor + me->eyeheight)

# define ACCEL ve->acceleration
# define VLCTY player->velocity

# define IS_HOLE_HIGH (hole.y < (player->where.z + HEAD_MARGIN))
# define FOOT_HEIGHT player->where.z - me->eyeheight
# define IS_HOLE_LOW (hole.x  > (FOOT_HEIGHT + KNEE_HEIGHT))

# define VEL_SUM (d->x * xyd.x + d->y * xyd.y)
# define VEL_POW (pow(xyd.x, 2.0) + pow(xyd.y, 2.0))
# define SAFE_VEL_POW ((VEL_POW == 0.0) ? 1.0 : VEL_POW)

# define IN_SIDE point_side_handle(p, d, VERT, s) < 0
# define IN_CIRCLE intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, THICC)

typedef struct		s_move_events
{
	int				wsad[4];
	int				ground;
	int				falling;
	int				moving;
	int				ducking;

	float			eyeheight;
	float			yaw;

	int				can_bump;
	unsigned int	s;
}					t_move_events;

typedef struct		s_view_events
{
	int			x;
	int			y;
	int			pushing;
	float		acceleration;
	float		move_vec[2];
}					t_view_events;

void				events(t_level *lvl, t_player *player,
							SDL_Window *win, SDL_Surface *surface);

void				view_event(t_move_events *me, t_view_events *ve,
								t_player *player, t_sectors *sectors);

t_view_events		view_events_init(t_move_events *me);

void				view_event(t_move_events *me, t_view_events *ve,
								t_player *player, t_sectors *sectors);

t_view_events		view_events_init(t_move_events *me);

void				vert_collision_detection(t_move_events *me,
										t_player *player, t_sectors *sector);

void				hor_collision_detection(t_move_events *me,
										t_player *player, t_sectors *sectors);

void				bumping(t_move_events *me, t_player *player,
							t_sectors *sector, t_xy *d);

void				move_player(t_xy d, t_player *player, t_sectors *sectors);

void				key_events(t_move_events *me, t_player *player);

void				jump_duck_key_event(t_move_events *me,
							t_player *player, unsigned int sym, SDL_Event e);

void				move_key_event(t_move_events *me,
									unsigned int sym, SDL_Event e);

t_move_events		move_events_init(void);

#endif
