
#include "defines.h"
#include "doom.h"
#include "render.h"
#include "utils.h"

//////////////////////////////////////////////////////////////////
///////         DRAW
//////////////////////////////////////////////////////////////////


static screen screen_init(SDL_Surface *surface, player *player, sectors *sector, texture_set_s *t) {
     screen scrn;
     unsigned int i;

     scrn.player = player;
     scrn.surface = surface;
     scrn.sector = sector;
     scrn.txt = t;
     scrn.head = scrn.queue;
     scrn.tail = scrn.queue;
     i = 0;
     while (i < W){
         scrn.ytop[i] = 0;
         scrn.ybottom[i] = H - 1;
         i++;
     }
     /* Begin whole-screen rendering from where the player is. */
     scrn.head->sectorno = player->sector;
     scrn.head->sx1 = 0;
     scrn.head->sx2 = W - 1;
     if(++scrn.head == (scrn.queue + MAX_QUE))
         scrn.head = scrn.queue;
     return (scrn);
 }



static void line(SDL_Surface *surface, int x, int y1,int y2, int top,int middle,int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = CLAMP(y1, 0, H-1);
    y2 = CLAMP(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}

scaler_s scaler_init(a, b, c, d, f)
{
    scaler_s s;

    s.result = d + (b - 1 - a) * (f - d) / (c - a);
    s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
    s.fd = ABS(f - d);
    s.ca = ABS(c - a);
    s.cache = (int)((b - 1 - a) * ABS(f - d)) % ABS(c - a);
    return (s);
}

int scaler_next(scaler_s *s)
{
    s->cache += s->fd;
    while (s->cache >= s->ca)
    {
        s->result += s->bop;
        s->cache -= s->ca;
    }
    return s->result;
}

static void line2(SDL_Surface *surface, int x, int y1,int y2, scaler_s ty,unsigned txtx, int *t[])
{
    int *pix = (int*) surface->pixels;
    y1 = CLAMP(y1, 0, H-1);
    y2 = CLAMP(y2, 0, H-1);
    pix += y1 * W + x;

    for(int y = y1; y <= y2; ++y)
    {
        unsigned txty = scaler_next(&ty);

        *pix = t[txtx % 1024][txty % 1024];
        pix += W;
    }
}

edge_s edge_init(player *player, sectors *sect, int s)
{
    edge_s edge;
    /* Acquire the x,y coordinates of the two vertexes forming the edge of the sector */
    /* Transform the vertices into the player's view */
    edge.v1.x = sect->vertex[s+0].x - player->where.x;
    edge.v1.y = sect->vertex[s+0].y - player->where.y;
    edge.v2.x = sect->vertex[s+1].x - player->where.x;
    edge.v2.y = sect->vertex[s+1].y - player->where.y;
    /* Rotate them around the player's view */
    edge.pcos = player->anglecos;
    edge.psin = player->anglesin;
    edge.t1.x = edge.v1.x * edge.psin - edge.v1.y * edge.pcos;
    edge.t1.z = edge.v1.x * edge.pcos + edge.v1.y * edge.psin;
    edge.t2.x = edge.v2.x * edge.psin - edge.v2.y * edge.pcos;
    edge.t2.z = edge.v2.x * edge.pcos + edge.v2.y * edge.psin;
    return (edge);
}

void view_intersection_with_wall(screen *scrn)
{
    xy i1;
    xy i2;
    /////////////////TextureMapping
//             int u0;
//             int u1;
//             xy org1;
//             xy org2;
/////////////////
    if (scrn->edge.t1.z <= 0 || scrn->edge.t2.z <= 0) {
        // Find an intersetion between the wall and the approximate edges of player's view
        i1 = intersect(EDGE_T(scrn->edge.t1), EDGE_T(scrn->edge.t2),
                new_xy(-NEAR_SIDE, NEARZ), new_xy(-FAR_SIDE, FARZ));
        i2 = intersect(EDGE_T(scrn->edge.t1), EDGE_T(scrn->edge.t2),
                new_xy(NEAR_SIDE, NEARZ), new_xy(FAR_SIDE, FARZ));
/////////////////TextureMapping
        scrn->txt_data.u0 = 0;
        scrn->txt_data.u1 = 1023;
        scrn->txt_data.org1.x = scrn->edge.t1.x;
        scrn->txt_data.org1.y = scrn->edge.t1.z;
        scrn->txt_data.org2.x = scrn->edge.t2.x;
        scrn->txt_data.org2.y = scrn->edge.t2.z;
/////////////////
        if (scrn->edge.t1.z < NEARZ) {
            if (i1.y > 0) {
                scrn->edge.t1.x = i1.x;
                scrn->edge.t1.z = i1.y;
            } else {
                scrn->edge.t1.x = i2.x;
                scrn->edge.t1.z = i2.y;
            }
        }
        if (scrn->edge.t2.z < NEARZ) {
            if (i1.y > 0) {
                scrn->edge.t2.x = i1.x;
                scrn->edge.t2.z = i1.y;
            } else {
                scrn->edge.t2.x = i2.x;
                scrn->edge.t2.z = i2.y;
            }
        }
/////////////////TextureMapping
                 if(ABS(scrn->edge.t2.x - scrn->edge.t1.x) > ABS(scrn->edge.t2.z - scrn->edge.t1.z)) {
                     scrn->txt_data.u0 = (scrn->edge.t1.x - scrn->txt_data.org1.x) * 1023 / (scrn->txt_data.org2.x - scrn->txt_data.org1.x);
                     scrn->txt_data.u1 = (scrn->edge.t2.x - scrn->txt_data.org1.x) * 1023 / (scrn->txt_data.org2.x - scrn->txt_data.org1.x);
                 }else {
                     scrn->txt_data.u0 = (scrn->edge.t1.z - scrn->txt_data.org1.y) * 1023 / (scrn->txt_data.org2.y - scrn->txt_data.org1.y);
                     scrn->txt_data.u1 = (scrn->edge.t2.z - scrn->txt_data.org1.y) * 1023 / (scrn->txt_data.org2.y - scrn->txt_data.org1.y);
                 }
/////////////////
    }
}
float get_scale(float z, char side)
{
    float fside;

    if (side == 'y')
        fside = H * V_FOV;
    if (side == 'x')
        fside = W * H_FOV;
    return (fside / z);
}

int set_heights(float height, float z, float yaw, float scale_y)
{
   return (H / 2 + (int)(-YAW(height, z, yaw) * scale_y));
}

perspective_s perspective_init(edge_s edge)
{
    perspective_s perspect;

    perspect.scale1.x = get_scale(edge.t1.z, 'x');
    perspect.scale1.y = get_scale(edge.t1.z, 'y');
    perspect.x1 = W / 2 + (int)(-edge.t1.x * perspect.scale1.x);
    perspect.scale2.x = get_scale(edge.t2.z, 'x');
    perspect.scale2.y  = get_scale(edge.t2.z, 'y');
    perspect.x2 = W / 2 + (int)(-edge.t2.x * perspect.scale2.x);
    return (perspect);
}

void set_heights_floor_ceil(heights_s *heights, player *p, sectors *s, int nghbr)
{
    heights->neighb_yceil = 0;
    heights->neighb_yfloor = 0;
    if (nghbr) {
        /* Something is showing through this wall (portal). */
        /* Perspective-transform the floor and ceiling coordinates of the neighboring sector. */
        heights->neighb_yceil = s->ceil - p->where.z;
        heights->neighb_yfloor = s->floor - p->where.z;
    }
    if (nghbr == -2)  {
        heights->yceil = s->ceil - p->where.z;//SECT_NOW
        heights->yfloor = s->floor - p->where.z;
    }
}

void set_heights_x(heights_s *heights, perspective_s perspect, screen *scrn)
{
    heights->beginx = MAX(perspect.x1, scrn->now.sx1);
    heights->endx = MIN(perspect.x2, scrn->now.sx2);
}

void set_heights_y(heights_s *h, player *pl, edge_s edge, perspective_s p)
{
    int y1a;
    int y1b;
    int y2a;
    int y2b;

    y1a = set_heights(h->yceil, edge.t1.z, pl->yaw, p.scale1.y);
    y1b = set_heights(h->yfloor, edge.t1.z, pl->yaw, p.scale1.y);
    y2a = set_heights(h->yceil, edge.t2.z, pl->yaw, p.scale2.y);
    y2b = set_heights(h->yfloor, edge.t2.z, pl->yaw, p.scale2.y);
    ///////////////// ! NOT ! TextureMapping
    h->z = scaler_init(p.x1, h->beginx, p.x2, edge.t1.z * 8, edge.t2.z * 8);
    /////////////////
    h->ya = scaler_init(p.x1, h->beginx, p.x2, y1a, y2a);
    h->yb = scaler_init(p.x1, h->beginx, p.x2, y1b, y2b);
    y1a = set_heights(h->neighb_yceil, edge.t1.z, pl->yaw, p.scale1.y);
    y1b = set_heights(h->neighb_yfloor, edge.t1.z, pl->yaw, p.scale1.y);
    y2a = set_heights(h->neighb_yceil, edge.t2.z, pl->yaw, p.scale2.y);
    y2b = set_heights(h->neighb_yfloor, edge.t2.z, pl->yaw, p.scale2.y);
    h->neighb_ya = scaler_init(p.x1, h->beginx, p.x2, y1a, y2a);
    h->neighb_yb = scaler_init(p.x1, h->beginx, p.x2, y1b, y2b);
}

heights_s heights_init(screen *scrn, perspective_s perspect, int s)
{
    heights_s heights;

    set_heights_x(&heights, perspect, scrn);
    set_heights_floor_ceil(&heights, scrn->player, SECT_NOW, -2);
    set_heights_floor_ceil(&heights, scrn->player, SECT_NGHBR_NOW(s), HAS_NGHBR_NOW(s));
    set_heights_y(&heights, scrn->player, scrn->edge, perspect);
    return (heights);
}

wall_s wall_init(screen *scrn, heights_s *heights, int x, perspective_s persp)
{
    wall_s wall;

    /////////////////  TextureMapping
                    scrn->txt_data.txtx = (scrn->txt_data.u0 * ((persp.x2 - x) * scrn->edge.t2.z) + scrn->txt_data.u1*((x - persp.x1)*scrn->edge.t1.z)) / ((persp.x2 - x) * scrn->edge.t2.z + (x - persp.x1) * scrn->edge.t1.z);
    /////////////////
    ///////////////// ! NOT ! TextureMapping
    /* Calculate the Z coordinate for this point. (Only used for lighting.) */
//    wall.z = scaler_next(&(heights->z));
    /////////////////
    /* Acquire the Y coordinates for our floor & ceiling for this X coordinate */
    wall.ya = scaler_next(&(heights->ya));
    wall.yb = scaler_next(&(heights->yb));
    /* CLAMP the ya & yb */
    wall.cya = CLAMP(wall.ya, scrn->ytop[x], scrn->ybottom[x]);
    wall.cyb = CLAMP(wall.yb, scrn->ytop[x], scrn->ybottom[x]);
    return (wall);
}

void set_neighbor_wall(wall_s *wall, screen *scrn, heights_s *heights, int x)
{
    wall->nya = scaler_next(&(heights->neighb_ya));
    wall->nyb = scaler_next(&(heights->neighb_yb));
    /* CLAMP ya2 & yb2 */
    wall->cnya = CLAMP(wall->nya, scrn->ytop[x], scrn->ybottom[x]);
    wall->cnyb = CLAMP(wall->nyb, scrn->ytop[x], scrn->ybottom[x]);
}

void render_the_wall(screen *scrn, perspective_s perspect, heights_s heights, int s)
{
    wall_s wall;

    for (int x = heights.beginx; x <= heights.endx; ++x) {

        wall = wall_init(scrn, &heights, x, perspect);

        /////////////////  TextureMapping
        // Texture-mapping for floors and ceilings is not very optimal in my program.
        // I'm converting each screen-pixel into map-coordinates by doing the perspect
        // transformation in reverse, and using these map-coordinates as indexes into texture.
        // This involves a few division calculations _per_ pixel, and would have been way
        // too slow for the platforms targeted by Doom and Duke3D.
        // In any case, there's no neat way to do it.
        // It is why the SNES port of Doom didn't do floor & ceiling textures at all.
        /////////////////
//               for(int y=scrn->ytop[x]; y<=scrn->ybottom[x]; ++y)
//               {
//                   if(y >= wall.cya && y <= wall.cyb) { y = wall.cyb; continue; }
//                   float hei = y < wall.cya ? heights.yceil    : heights.yfloor;
//                   float mapx, mapz;
//                   CeilingFloorScreenCoordinatesToMapCoordinates(hei, x,y,  mapx,mapz);
//                   unsigned txtx = (mapx * 256), txtz = (mapz * 256);
//                   const struct TextureSet* txt = y < wall.cya ? sect->ceiltexture : sect->floortexture;
//
//             int pel = txt->texture[txtz % 1024][txtx % 1024];
//
//             ((int*)surface->pixels)[y*W+x] = pel;
//         }
//
//        for(int y=scrn->ytop[x]; y<=scrn->ybottom[x]; ++y)
//        {
//            if(y >= wall.cya && y <= wall.cyb)
//            {
//                y = wall.cyb;
//                continue;
//            }
//            float hei = y < wall.cya ? heights.yceil    : heights.yfloor;
//            float mapx, mapz;
////            CeilingFloorScreenCoordinatesToMapCoordinates(hei, x,y,  mapx,mapz);
//            unsigned txtx = (mapx * 256), txtz = (mapz * 256);
//            int **txt = y < wall.cya ? scrn->txt->c : scrn->txt->f;
//
//            int pel = txt[txtz % 1024][txtx % 1024];

//            ((int*)scrn->surface->pixels)[y*W+x] = pel;
//        }
        ///////////////// ELSE
        /* Render ceiling: everything above this sector's ceiling height. */
        line(scrn->surface, x, scrn->ytop[x], wall.cya - 1, 0x111111, 0x222222, 0x111111);
        /* Render floor: everything below this sector's floor height. */
        line(scrn->surface, x, wall.cyb + 1, scrn->ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);
        /////////////////


        /* Is there another sector behind this edge? */
        if (HAS_NGHBR_NOW(s)) {
            /* Same for _their_ floor and ceiling */
            set_neighbor_wall(&wall, scrn, &heights, x);
            /* If our ceiling is higher than their ceiling, render upper wall */
            ///////////////// TextureMapping
            //                     line2(x, wall.cya, wall.cnya-1, (scaler_s)scaler_init(wall.ya,wall.cya,wall.yb, 0,1023), wall.txtx, &sect->uppertextures[s]);
            line2(scrn->surface,x, wall.cya, wall.cnya-1, (scaler_s)scaler_init(wall.ya,wall.cya,wall.yb, 0,1023),  scrn->txt_data.txtx, scrn->txt->u);
            ///////////////// ELSE
//            line(scrn->surface, x, wall.cya, wall.cnya - 1, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R1(wall.z), 0);
            /////////////////
            scrn->ytop[x] = CLAMP(MAX(wall.cya, wall.cnya), scrn->ytop[x], H - 1);

            // If our floor is lower than their floor, render bottom wall
            ///////////////// TextureMapping
            //                     line2(x, wall.cnyb+1, wall.cyb, (scaler_s)scaler_init(wall.ya,cnyb+1,wall.yb, 0,1023), wall.txtx, &sect->lowertextures[s]);
            line2(scrn->surface,x, wall.cnyb+1, wall.cyb, (scaler_s)scaler_init(wall.ya,wall.cya+1,wall.yb, 0,1023),  scrn->txt_data.txtx, scrn->txt->l);
            ///////////////// ELSE
//            line(scrn->surface, x, wall.cnyb + 1, wall.cyb, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R2(wall.z), 0);
            /////////////////
            scrn->ybottom[x] = CLAMP(MIN(wall.cyb, wall.cnyb), 0, scrn->ybottom[x]);
        } else {
            /* There's no neighbor. Render wall. */
            ///////////////// TextureMapping
            //                     line2(x, cya,cyb, (scaler_s_s)scaler_init(ya,cya,yb, 0,1023), txtx, &sect->uppertextures[s]);
            line2(scrn->surface,x, wall.cya, wall.cyb, (scaler_s)scaler_init(wall.ya,wall.cya+1,wall.yb, 0,1023),  scrn->txt_data.txtx, scrn->txt->u);
            ///////////////// ELSE
//            line(scrn->surface, x, wall.cya, wall.cyb, 0, x == perspect.x1 || x == perspect.x2 ? 0 : R(wall.z), 0);
            /////////////////
        }
    }
}

void schedule(screen *scrn, heights_s heights, int s)
{
    if (HAS_NGHBR_NOW(s) && NOT_END && HAS_NEXT_QUE)
    {
        scrn->head->sectorno = NGHBR_NOW(s);
        scrn->head->sx1 = heights.beginx;
        scrn->head->sx2 = heights.endx;
        if (++scrn->head == scrn->queue + MAX_QUE)
            scrn->head = scrn->queue;
    }
}

void render(screen *scrn)
{
    heights_s heights;
    perspective_s perspect;

    /* Render each wall of this sector that is facing towards player-> */
    for(int s = 0; s < SECT_NOW->npoints; ++s)
    {
        scrn->edge = edge_init(scrn->player, SECT_NOW, s);
        /* Is the wall at least partially in front of the player? */
        if (IS_FRONT(scrn->edge))
        {
            /* If it's partially behind the player, clip it against player's view frustrum */
                view_intersection_with_wall(scrn);
            /* Do perspect transformation */
                perspect = perspective_init(scrn->edge);
                if (perspect.x1 < perspect.x2) {
                    if (perspect.x2 > scrn->now.sx1 && perspect.x1 < scrn->now.sx2) {
                        /* Acquire and transform the floor and ceiling heights */
                        heights = heights_init(scrn, perspect, s);
                        /* Render the wall. */
                        render_the_wall(scrn, perspect, heights, s);
                        /* Schedule the other sector for rendering within the window formed by this wall. */
                        schedule(scrn, heights, s);
                    }
                }
        }
    }
}

void draw_screen(SDL_Surface *srf, player *pl, sectors *sct, texture_set_s *t)
{
    screen scrn;
    unsigned int s;
    int renderedsectors[pl->num_sectors];

    scrn = screen_init(srf, pl, sct, t);
    s = 0;
    while (s < pl->num_sectors)
         renderedsectors[s++] = 0;
    while(scrn.head != scrn.tail)
    {
        /* Pick a sector & slice from scrn.queue to draw */
        scrn.now = *scrn.tail;
        if(++scrn.tail == scrn.queue +MAX_QUE)
            scrn.tail = scrn.queue;
        if(!(renderedsectors[scrn.now.sectorno] & 0x21)) // Odd = still rendering, 0x20 = give up
        {
            ++renderedsectors[scrn.now.sectorno];
            render(&scrn);
            ++renderedsectors[scrn.now.sectorno];
        }
    }
}