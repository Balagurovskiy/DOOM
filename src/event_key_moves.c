#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"
//////////////////////////////////////////////////////////////////
///////         KEY EVENTS
//////////////////////////////////////////////////////////////////


move_events move_events_init(){
    move_events me;

    me.wsad[0] = 0;
    me.wsad[1] = 0;
    me.wsad[2] = 0;
    me.wsad[3] = 0;
    me.ground = 0;
    me.falling = 1;
    me.moving = 0;
    me.ducking = 0;
    me.yaw = 0;
    return (me);
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
void move_player(xy d, player *player, sectors *sector)
{
    unsigned int s;
    xy p;
     /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, POINT_SIDE will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    p = new_xy(player->where.x, player->where.y);
    s = 0;
    while (s < PLAYER_SECT->npoints){
        // printf("%d * %d\n", sect->neighbors[s],s);
        if(PLAYER_SECT->neighbors[s] >= 0
        && intersect_box_handle(p, d, VERT, s)
                && point_side_handle(p, d, VERT, s) < 0)
        {
            player->sector = PLAYER_SECT->neighbors[s];
            break;
        }
        s++;
    }
    player->where.x += d.x;
    player->where.y += d.y;
    player->anglesin = sinf(player->angle);
    player->anglecos = cosf(player->angle);
}