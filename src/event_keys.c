#include "defines.h"
#include "doom.h"
#include "events.h"
//////////////////////////////////////////////////////////////////
///////         KEY EVENTS
//////////////////////////////////////////////////////////////////

void move_key_event(move_events *me, unsigned int sym, SDL_Event e){
    if(sym == 'w')
        me->wsad[0] = e.type == SDL_KEYDOWN;
    if(sym == 's')
        me->wsad[1] = e.type == SDL_KEYDOWN;
    if(sym == 'a')
        me->wsad[2] = e.type == SDL_KEYDOWN;
    if(sym == 'd')
        me->wsad[3] = e.type == SDL_KEYDOWN;
}

void jump_duck_key_event(move_events *me, player *player, unsigned int sym, SDL_Event e){
    if(sym == ' ')
        if(me->ground) {
            player->velocity.z += 0.5;
            me->falling = 1;
        }
        if(sym == SDLK_LCTRL || sym == SDLK_LCTRL){
            me->ducking = e.type == SDL_KEYDOWN;
            me->falling = 1;
        }
}

void key_events(move_events *me, player *player){
    SDL_Event e;
    
    while(SDL_PollEvent(&e)){
        unsigned int sym = e.key.keysym.sym;
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
            move_key_event(me, sym, e);
            jump_duck_key_event(me, player, sym, e);
            if(sym == SDLK_ESCAPE)
                quit();
        }         
        if (e.type == SDL_QUIT)
            quit();
    }
}
