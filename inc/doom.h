

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

    int health;
    
    int action;
    int key;

    float gravity;
}           player;

typedef struct player_save
{
    int next_start;    
    char *next_lvl_temp;
    float angle;
    int key;
    int health;

}           player_save;

typedef struct  texture_set_s
{
    SDL_Surface *floortexture;
    SDL_Surface *ceiltexture;
    SDL_Surface *uppertextures;
    SDL_Surface *lowertextures;

    SDL_Surface *sky;
    SDL_Surface *door;
    SDL_Surface *dec[5];
    SDL_Surface *key[7];
    
    SDL_Surface *curr_object;
    SDL_Surface *passive_object;
    SDL_Surface *active_object;

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
void  goto_level(level_s *lvl, player *p, char *level_name);
void action_controller(player *player, level_s *lvl, char *file);
void door0000(player *p, level_s *lvl, char *file);

void        free_level(level_s *level);
void        free_texture_set(texture_set_s *t);
void        music(char *tag);

void render_massage(char *mssg, SDL_Surface *surface);
void message(char *file, player *p, SDL_Surface *surface);
void text_pattern_0(char *file, player *p, SDL_Surface *surface);
void text_pattern_01(char *file, player *p, SDL_Surface *surface);
void text_pattern_1(char *file, player *p, SDL_Surface *surface);
void text_pattern_2(char *file, player *p, SDL_Surface *surface);

char *save_file(char *file);

int ft_timer();
// void        sector_init(sectors* s, int sx[], int sy[], int n[]);

#endif

