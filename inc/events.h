

#ifndef EVENTS_H
# define EVENTS_H

void event(sectors *sectors, player *player);

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors);

view_events view_events_init(move_events *me);

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors);

view_events view_events_init(move_events *me);

void vert_collision_detection(move_events *me, player *player, sectors *sector);

void hor_collision_detection(move_events *me, player *player, sectors *sectors);

void bumping(move_events *me, player *player,
             sectors *sector, xy *d, int can_bump, unsigned int s);

void move_player(xy d,player *player, sectors *sectors);

void key_events(move_events *me, player *player);

void jump_duck_key_event(move_events *me, player *player, unsigned int sym, SDL_Event e);

void move_key_event(move_events *me, unsigned int sym, SDL_Event e);

move_events move_events_init();

#endif
