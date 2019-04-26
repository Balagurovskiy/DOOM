

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
    int *neighbors;           // Each edge may have a corresponding neighboring sector
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
    unsigned int total_sectors;
    int exit_doom;
}           player;


typedef struct  texture_set_s
{
    SDL_Surface *floortexture;
    SDL_Surface *ceiltexture;
    SDL_Surface *uppertextures;
    SDL_Surface *lowertextures;
    int          size;

}               texture_set_s;

typedef struct level_s
{
    sectors* (*init_sectors)();
    texture_set_s   (*init_textures)();
    int sectors;
    int start[3];
    int end[3];
    int next_level[3];
}           level_s;

sectors* m1();texture_set_s   t1();
sectors* m2();texture_set_s   t2();
sectors* m3();texture_set_s   t3();
sectors* sprite_test();

void render_screen(SDL_Surface *srf, player *pl, sectors *sct, texture_set_s *t);
void events(sectors *sectors, player *player);

void quit(sectors *sct, texture_set_s *t, player *p, level_s *l);
void        free_texture_set(texture_set_s *t);

void        sector_init(sectors* s, int sx[], int sy[], int n[]);
sectors*    init_map();
player      init_player(xy x_y, float a, sectors *s, unsigned int s_in, int num_s);
texture_set_s   texture_init();

#endif

