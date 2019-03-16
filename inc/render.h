

#ifndef RENDER_H
# define RENDER_H

#include "defines.h"
//#include "utils.h"


typedef struct  item
{
    int sectorno;
    int sx1;
    int sx2;
}               item;

typedef  struct edge
{
    xy v1;
    xy v2;
    float pcos;
    float psin;
    xyz t1;
    xyz t2;
}               edge_s;

typedef struct  txt_data_s
{
         int u0;
         int u1;
         xy org1;
         xy org2;
         int txtx;
}               txt_data_s;
typedef struct  screen
{
    item queue[MAX_QUE];
    item *head;
    item *tail;
    item now;

    int ytop[W];
    int ybottom[W];

    player *player;
    sectors *sector;
    SDL_Surface *surface;

    texture_set_s *txt;
    txt_data_s     txt_data;

    edge_s  edge;

}               screen;


// #ifdef TextureMapping
//typedef int Texture[1024][1024];
//struct TextureSet { Texture texture, normalmap, lightmap, lightmap_diffuseonly; };
//#endif
//
///* Sectors: Floor and ceiling height; list of wall vertexes and neighbors */
//static struct sector
//{
//    float floor, ceil;
//    struct xy { float x, y; } *vertex; /* Each vertex has an x and y coordinate */
//    unsigned short npoints;            /* How many vertexes there are */
//    signed char *neighbors;            /* Each pair of vertexes may have a corresponding neighboring sector */
//#ifdef VisibilityTracking
//    int visible;
//#endif
//#ifdef TextureMapping
//    struct TextureSet *floortexture, *ceiltexture, *uppertextures, *lowertextures;
//#endif
//} *sectors = NULL;
typedef struct  line_s
{
    int x;
    int y1;
    int y2;
    int top;
    int middle;
    int bottom;
}               line_s;



typedef  struct perspective
{
    xy scale1;
    xy scale2;
    int x1;
    int x2;
}               perspective_s;

typedef struct scaler
{
    int result;
    int bop;
    int fd;
    int ca;
    int cache;
}              scaler_s;

typedef struct heights
{
    float yceil;
    float yfloor;
    float neighb_yceil;
    float neighb_yfloor;
    int beginx;
    int endx;
    scaler_s ya;
    scaler_s yb;
    scaler_s neighb_ya;
    scaler_s neighb_yb;
    scaler_s z;//shading only
}              heights_s;

typedef struct wall
{
    int z;
    int ya;
    int yb;
    int cya;
    int cyb;
    int nya;
    int nyb;
    int cnya;
    int cnyb;
}              wall_s;

void draw_screen(SDL_Surface *srf, player *pl, sectors *sct, texture_set_s *t);

#endif
