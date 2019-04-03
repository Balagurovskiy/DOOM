#include "defines.h"
#include "doom.h"
#include "events.h"

void events(sectors *sectors, player *player)
{
    static move_events    me;
    static view_events    ve;
    static int     init_time = 1;

    if (init_time)
        me = move_events_init();
    init_time = 0;
    me.eyeheight = (me.ducking) ? DUCK_HEIGHT : EYE_HEIGHT;
    key_events(&me, player, sectors);
    /* mouse aiMINg */
    ve = view_events_init(&me);
    view_event(&me, &ve, player, sectors);
    /* Vertical collision detection */
    vert_collision_detection(&me, player, sectors);
    /* Horizontal collision detection */
    hor_collision_detection(&me, player, sectors);
}