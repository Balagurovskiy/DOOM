

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

    int object;
    xy  object_xy[2];
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
    
    int action;
    int key;

    float gravity;
}           player;


typedef struct  texture_set_s
{
    SDL_Surface *floortexture;
    SDL_Surface *ceiltexture;
    SDL_Surface *uppertextures;
    SDL_Surface *lowertextures;

    SDL_Surface *curr_object;
    SDL_Surface *passive_object;
    SDL_Surface *active_object;
    int          size;

}               texture_set_s;


typedef struct level_s
{
    sectors* sector;
    texture_set_s texture;
    int sectors_size;
    int start[3];
    int end[3];
    char *next_level[3];
}           level_s;


sectors* sprite_test();

void render_screen(SDL_Surface *srf, player *pl, level_s *lvl, int is_obj);
void events(sectors *sectors, player *player);

void change_level(level_s *lvl, player *p);
void action_controller(player *player, level_s *lvl, char *file);
void door1(player *p, level_s *lvl, char *file);

void        free_level(level_s *level);
void        free_texture_set(texture_set_s *t);

// void        sector_init(sectors* s, int sx[], int sy[], int n[]);

#endif

