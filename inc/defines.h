
#ifndef DEFINES_H
# define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "SDL_image.h"

/* Define window size */
#define W 640//1280
#define H 480//720
/* Define various vision related constants */
#define EYE_HEIGHT  6    // Camera height from floor when standing
#define DUCK_HEIGHT 2.5  // And when crouching
#define HEAD_MARGIN 1    // How much room there is above camera before the scrn.head hits the ceiling
#define KNEE_HEIGHT 2    // How tall obstacles the player can simply walk over without jumping
#define H_FOV (1.0 * 0.73f*H / W)  // Affects the horizontal field of vision(never >= 180 degrees though)
#define V_FOV (1.0 * .2f)    // Affects the vertical field of vision
#define MAX_QUE 32   // MAXimum number of pending portal renders
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MIN(a,b)             (((a) < (b)) ? (a) : (b)) // MIN: Choose smaller of two scalars.
#define MAX(a,b)             (((a) > (b)) ? (a) : (b)) // MAX: Choose greater of two scalars.
#define CLAMP(a, mi, ma)      MIN(MAX(a, mi), ma)         // CLAMP: CLAMP value into set range.
#define SIGN(v) (((v) > 0) - ((v) < 0))    // sign: Return the sign of a value (-1, 0 or 1)
#define VXS(x0, y0, x1, y1)    ((x0 * y1) - (x1 * y0))   // VXS: Vector cross product
// OVERLAP:  DeterMINe whether the two number ranges OVERLAP.

#define MVM(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1))
#define MAM(a0, a1, b0, b1) (MIN(b0, b1) <= MAX(a0, a1))
#define OVERLAP(a0, a1, b0, b1) (MVM(a0, a1, b0, b1) && MAM(a0, a1, b0, b1))

#define YAW(y, z, pyaw) (y + z * pyaw)

#define PLAYER_SECT (&sector[player->sector])
#define PLAYER_NGHBR(s) PLAYER_SECT->neighbors[s]
#define PLAYER_NGHBR_SECT(s) sector[PLAYER_NGHBR(s)]
#define VERT PLAYER_SECT->vertex

#define SECT_NOW (&scrn->sector[scrn->now.sectorno])
#define NGHBR_NOW(s) SECT_NOW->neighbors[s]
#define SECT_NGHBR_NOW(s) &scrn->sector[NGHBR_NOW(s)]
#define HAS_NGHBR_NOW(s) NGHBR_NOW(s) >= 0

#define R1(z) 0x000101 * (255 - z)
#define R2(z) 0x040007 * (31 - (z / 8))
#define R(z) 0x010001 * (255 - z) //0x010101 - shaded white

#define NEARZ 1e-4f
#define FARZ 5
#define NEAR_SIDE 1e-5f
#define FAR_SIDE 20.f

#define EDGE_T(t) new_xy(t.x, t.z)
//!(edge.t1.z <= 0 && edge.t2.z <= 0)
#define IS_FRONT(edge) (edge.t1.z > 0 || edge.t2.z > 0)
#define HAS_NEXT_QUE ((scrn->head + MAX_QUE + 1 - scrn->tail) % MAX_QUE)
#define NOT_END (heights.endx >= heights.beginx)


#endif
