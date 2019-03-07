#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"
//////////////////////////////////////////////////////////////////
///////         collision
//////////////////////////////////////////////////////////////////

void hor_collision_detection(move_events *me, player *player, sectors *sector){
    xy p;
    xy d;
    unsigned int s;

    if(me->moving)
    {
        p = new_xy(player->where.x, player->where.y);
        d = new_xy(player->velocity.x, player->velocity.y);
        /* Check if the player is about to cross one of the sector's edges */
        s = 0;
        while (s < PLAYER_SECT->npoints){
            int inter = intersect_box_handle(p, d, VERT, s);
            int point = point_side_handle(p, d, VERT, s);
            if(inter && (point < 0))
                bumping(me, player, sector, &d, s);
            s++;
        }
        move_player(new_xy(player->velocity.x, player->velocity.y), 
                            player, sector);
        me->falling = 1;
    }
}

void vert_collision_detection(move_events *me, player *player, sectors *sectors){
    float nextz;

    me->ground = !me->falling;
    if(me->falling)
    {
        player->velocity.z -= 0.05f; /* Add gravity */
        nextz = player->where.z + player->velocity.z;
        if(player->velocity.z < 0 && nextz  < sectors[player->sector].floor + me->eyeheight) // When going down
        {
            /* Fix to ground */
            player->where.z = sectors[player->sector].floor + me->eyeheight;
            player->velocity.z = 0;
            me->falling = 0;
            me->ground  = 1;
        }
        else if(player->velocity.z > 0 && nextz > sectors[player->sector].ceil) // When going up
        {
            /* Prevent jumping above ceiling */
            player->velocity.z = 0;
            me->falling = 1;
        }
        if(me->falling)
        {
            player->where.z += player->velocity.z;
            me->moving = 1;
        }
    }
}