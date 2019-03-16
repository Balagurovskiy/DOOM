

#ifndef DOOM_H
# define DOOM_H

#include "defines.h"
#include "utils.h"


/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
typedef struct sectors
{
    float floor;
    float ceil;
    xy *vertex; // Each vertex has an x and y coordinate
    char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned int npoints;               // How many vertexes there are
    
}           sectors;

/* Player: location */
typedef struct player
{
    xyz where;      // Current position
    xyz velocity;   // Current motion vector
    float angle;
    float anglesin;
    float anglecos;
    float yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned int sector;                        // Which sector the player is currently in
    unsigned int num_sectors;
}           player;

typedef struct  move_events
{
    int wsad[4];
    int ground;
    int falling;
    int moving;
    int ducking;

    float eyeheight;
    float yaw;
}               move_events;

typedef struct  view_events
{
    int x;
    int y;
    int pushing;
    float acceleration;
    float move_vec[2];
}              view_events;


typedef struct  texture_set_s
{
    SDL_Surface *floortexture;
    SDL_Surface *ceiltexture;
    SDL_Surface *uppertextures;
    SDL_Surface *lowertextures;

    int *f[1024];
    int *u[1024];
    int *c[1024];
    int *l[1024];
}               texture_set_s;

void draw_screen(SDL_Surface *srf, player *pl, sectors *sct, texture_set_s *t);
void event(sectors *sectors, player *player);

void        quit();

void        sector_init(sectors* s, int sx[], int sy[], int n[]);
sectors*    init_map(int num_sectors);
player      init_player(xy x_y, float a, sectors *s, unsigned int s_in, int num_s);
texture_set_s   texture_init();

#endif

