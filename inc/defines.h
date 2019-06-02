/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:19:49 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdlib.h>
# include <math.h>
# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"
# include "time.h"

/*
** window size
*/
# define W 640
/*
** 1280 820 640
*/
# define H 480
/*
** 720 640 480
*/
/*
** Camera height from floor when standing
*/
# define EYE_HEIGHT 6
/*
** Camera height from floor when crouching
*/
# define DUCK_HEIGHT 3.5
/*
** bounding radius
*/
# define THICC 0.7
/*
** distance after change texture rgb to darker
*/
# define BLACK_DIST 50
/*
** How much room there is above camera before the scrn.head hits the ceiling
*/
# define HEAD_MARGIN 0.5
/*
** How tall obstacles the player can simply walk over without jumping
*/
# define KNEE_HEIGHT 2
/*
** Affects the horizontal field of vision(never >= 180 degrees though)
*/
# define H_FOV (0.9 * H / W)
/*
** Affects the vertical field of vision
*/
# define V_FOV (0.15)
/*
** MAX number of pending portal renders
*/
# define MAX_QUE 33

# define ABS(a) ((a) < 0 ? -(a) : (a))
/*
** Choose smaller of two scalars.
*/
# define MIN(a,b) (((a) < (b)) ? (a) : (b))
/*
** Choose greater of two scalars.
*/
# define MAX(a,b) (((a) > (b)) ? (a) : (b))
/*
** Choose CLAMP value into set range.
*/
# define CLAMP(a, mi, ma) MIN(MAX(a, mi), ma)

# define SIGN(v) (((v) > 0) - ((v) < 0))
/*
** Vector cross product
*/
# define VXS(x0, y0, x1, y1) ((x0 * y1) - (x1 * y0))
/*
** DeterMINe whether the two number ranges OVERLAP.
*/
# define MVM(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1))
# define MAM(a0, a1, b0, b1) (MIN(b0, b1) <= MAX(a0, a1))
# define OVERLAP(a0, a1, b0, b1) (MVM(a0, a1, b0, b1) && MAM(a0, a1, b0, b1))

# define YAW(y, z, pyaw) (y + z * pyaw)

# define TIME_SPEED 100

# define PLAYER_SECT sector[player->sector]
# define PLAYER_NGHBR(s) (&PLAYER_SECT)->neighbors[s]
# define PLAYER_NGHBR_SECT(s) sector[PLAYER_NGHBR(s)]
# define VERT (&PLAYER_SECT)->vertex

# define SECT_NOW (&scrn->sector[scrn->now.sectorno])
# define NGHBR_NOW(s) SECT_NOW->neighbors[s]
# define SECT_NGHBR_NOW(s) &scrn->sector[NGHBR_NOW(s)]
# define HAS_NGHBR_NOW(s) NGHBR_NOW(s) >= 0
/*
** intersection wall with camera
*/
# define NEARZ 0.0001
# define NEAR_SIDE 0.0001

# define FAR_SIDE 20.0
# define FARZ 5.0

# define EDGE_T(t) new_xy(t.x, t.z)
# define IS_FRONT(edge) (edge.t1.z > 0 || edge.t2.z > 0)
# define HAS_NEXT_QUE ((scrn->head + MAX_QUE + 1 - scrn->tail) % MAX_QUE)
# define NOT_END (heights.endx >= heights.beginx)

# define ACC 0.01
# define COMPARE(a, b) ABS(a - b) < ACC

#endif
