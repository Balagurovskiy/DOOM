#include "defines.h"
#include "doom.h"
#include "events.h"
#include "utils.h"
//////////////////////////////////////////////////////////////////
///////         MOUSE EVENTS
//////////////////////////////////////////////////////////////////

view_events view_events_init(move_events *me){
    view_events ve;

    SDL_GetRelativeMouseState(&(ve.x), &(ve.y));
    ve.move_vec[0] = 0.f;
    ve.move_vec[1] = 0.f;
    ve.pushing = me->wsad[0] || me->wsad[1] || me->wsad[2] || me->wsad[3];
    ve.acceleration = ve.pushing ? 0.4 : 0.2;
    if(ve.pushing)
        me->moving = 1;
    return (ve);
}

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors){
    player->angle += ve->x * 0.03f;
    me->yaw = CLAMP(me->yaw + ve->y * 0.05f, -5, 5);// +/- ve->y = inverse mouse
    player->yaw = me->yaw - player->velocity.z * 0.5f;
    move_player(new_xy(0.0, 0.0), player, sectors);
    if(me->wsad[0]) {
        ve->move_vec[0] += player->anglecos * 0.2f;
        ve->move_vec[1] += player->anglesin * 0.2f;
    }
    if(me->wsad[1]) {
        ve->move_vec[0] -= player->anglecos * 0.06f;
        ve->move_vec[1] -= player->anglesin * 0.06f;
    }
    if(me->wsad[2]) {
        ve->move_vec[0] += player->anglesin * 0.1f;
        ve->move_vec[1] -= player->anglecos * 0.1f;
    }
    if(me->wsad[3]) {
        ve->move_vec[0] -= player->anglesin * 0.1f;
        ve->move_vec[1] += player->anglecos * 0.1f;
    }
    player->velocity.x = player->velocity.x * (1 - ve->acceleration) + ve->move_vec[0] * ve->acceleration;
    player->velocity.y = player->velocity.y * (1 - ve->acceleration) + ve->move_vec[1] * ve->acceleration;    
}