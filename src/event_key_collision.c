#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"
//////////////////////////////////////////////////////////////////
///////         collision
//////////////////////////////////////////////////////////////////
int get_collision_count(xy p, xy d, player *player, sectors *sector)
{
    unsigned int s;
    int collision_count;

    s = 0;
    collision_count = 0;
    while (s < (&PLAYER_SECT)->npoints)
    {
        p.x = p.x + d.x;
        p.y = p.y + d.y;
        if(intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, THICC))
            collision_count++;
        s++;
    }
    return (collision_count);
}

void hor_collision_detection(move_events *me, player *player, sectors *sector)
{
    xy p;
    xy d;
    unsigned int s;
    int collision_count;

    if(me->moving)
    {
        p = new_xy(player->where.x, player->where.y);
        d = new_xy(player->velocity.x, player->velocity.y);
        collision_count = get_collision_count(p, d, player, sector);
        s = 0;
        while (s < (&PLAYER_SECT)->npoints){
            p.x = p.x + d.x;
            p.y = p.y + d.y;
            if(intersert_circle_bound(VERT[s + 0], VERT[s + 1], p, THICC)
                && point_side_handle(p, d, VERT, s) < 0) {
                    bumping(me, player, sector, &d,(collision_count == 1), s);
            }
            s++;
        }
        move_player(new_xy(player->velocity.x, player->velocity.y), 
                            player, sector);
        me->falling = 1;
    }
}

static void vert_collision_switch(move_events *me,
                                    player *player,
                                    sectors *sector)
{
    if (EYE_HEIGHT + PLAYER_SECT.floor > PLAYER_SECT.ceil)
    {
        player->where.z = DUCK_HEIGHT;
        me->falling = 1;
        me->ducking = 1;
    }
    if(player->velocity.z < 0 && UNDER_CEIL) // When going down
    {
        /* Fix to ground */
        player->where.z = PLAYER_SECT.floor + me->eyeheight;
        player->velocity.z = 0;
        me->falling = 0;
        me->ground  = 1;
    }
    else if(player->velocity.z > 0 && JUMP_HEIGHT > PLAYER_SECT.ceil) // When going up
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

void vert_collision_detection(move_events *me, player *player, sectors *sector)
{
    me->ground = !me->falling;
    if(me->falling)
    {
        player->velocity.z -= player->gravity; /* Add gravity */        
        vert_collision_switch(me, player, sector);
    }
}