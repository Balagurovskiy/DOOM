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

typedef struct  move_events
{
    int wsad[4];
    int ground;
    int falling;
    int moving;
    int ducking;

    float eyeheight;
    float yaw;

	int can_bump;
	unsigned int s;
}               move_events;

typedef struct  view_events
{
    int x;
    int y;
    int pushing;
    float acceleration;
    float move_vec[2];
}              view_events;

void events(level_s *lvl, player *player, SDL_Window *win, SDL_Surface *surface);

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors);

view_events view_events_init(move_events *me);

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors);

view_events view_events_init(move_events *me);

void vert_collision_detection(move_events *me, player *player, sectors *sector);

void hor_collision_detection(move_events *me, player *player, sectors *sectors);

void bumping(move_events *me, player *player, sectors *sector, xy *d);

void move_player(xy d,player *player, sectors *sectors);

void key_events(move_events *me, player *player);

void jump_duck_key_event(move_events *me, player *player, unsigned int sym, SDL_Event e);

void move_key_event(move_events *me, unsigned int sym, SDL_Event e);

move_events move_events_init();

#endif
