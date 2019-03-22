#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"

void bumping(move_events *me, player *player,
            sectors *sector, xy *d, int can_bump, unsigned int s){
    float hole_low;
    float hole_high;
    xy xyd;

    hole_low = 9e9;
    hole_high = -9e9;
    if(PLAYER_NGHBR(s) >= 0)
    {
    /* Check where the hole is. */
        hole_low  = MAX((&PLAYER_SECT)->floor, PLAYER_NGHBR_SECT(s).floor);
        hole_high = MIN((&PLAYER_SECT)->ceil,  PLAYER_NGHBR_SECT(s).ceil);
    }
    /* Check whether we're bumping into a wall. */
    if((hole_high < (player->where.z + HEAD_MARGIN))
    || (hole_low  > (player->where.z - me->eyeheight + KNEE_HEIGHT)))
    {
        if (can_bump){
            /* Bumps into a wall! Slide along the wall. */
            /* This formula is from Wikipedia article "vector projection". */
            xyd.x = VERT[s + 1].x - VERT[s + 0].x;
            xyd.y = VERT[s + 1].y - VERT[s + 0].y;
            player->velocity.x = xyd.x * (d->x * xyd.x + d->y * xyd.y)
                                 / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
            player->velocity.y = xyd.y * (d->x * xyd.x + d->y * xyd.y)
                                 / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
        }else{
            player->velocity.x=0;
            player->velocity.y=0;
        }
        me->moving = 0;
    }
}