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
        int collision_count = 0;
        while (s < (&PLAYER_SECT)->npoints){
            p.x = p.x + d.x;
            p.y = p.y + d.y;
            int icb = intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, THICC);
            if(icb )
                collision_count++;
            s++;
        }
        p = new_xy(player->where.x, player->where.y);
        s = 0;
        while (s < (&PLAYER_SECT)->npoints){

            p.x = p.x + d.x;
            p.y = p.y + d.y;
            int point = point_side_handle(p, d, VERT, s);
            int icb = intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, THICC);
            if(icb && point < 0) {
                    bumping(me, player, sector, &d,(collision_count == 1), s);
            }
            s++;
        }
//        while (s < PLAYER_SECT->npoints){
//            int inter = intersect_box_handle(p, d, VERT, s);
//            int point = point_side_handle(p, d, VERT, s);
////            printf("p:%d   i:%d\n",point, inter);
//            p.x = p.x + d.x;
//            p.y = p.y + d.y;
//            int icb = intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, 0.5);
////            if(inter && (point < 0))
//            if(icb )
//                bumping(me, player, sector, &d, s);
//            s++;
//        }
        move_player(new_xy(player->velocity.x, player->velocity.y), 
                            player, sector);
        me->falling = 1;
    }
}

void vert_collision_detection(move_events *me, player *player, sectors *sector){
    float nextz;

    me->ground = !me->falling;
    if(me->falling)
    {
        player->velocity.z -= 0.05f; /* Add gravity */
        nextz = player->where.z + player->velocity.z;
        if(EYE_HEIGHT+PLAYER_SECT.floor > PLAYER_SECT.ceil)
        {
            player->where.z = DUCK_HEIGHT;
            me->falling = 1;
            me->ducking = 1;
        }
        if(player->velocity.z < 0 && nextz  < PLAYER_SECT.floor + me->eyeheight) // When going down
        {
            /* Fix to ground */
            player->where.z = PLAYER_SECT.floor + me->eyeheight;
            player->velocity.z = 0;
            me->falling = 0;
            me->ground  = 1;
        }
        else if(player->velocity.z > 0 && (EYE_HEIGHT+PLAYER_SECT.floor+player->velocity.z) > PLAYER_SECT.ceil) // When going up
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