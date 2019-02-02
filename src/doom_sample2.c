#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <SDL.h>
#include "SDL2/SDL.h"

/* Define window size */
#define W 640//1280
#define H 480//720
/* Define various vision related constants */
#define EYE_HEIGHT  6    // Camera height from floor when standing
#define DUCK_HEIGHT 2.5  // And when crouching
#define HEAD_MARGIN 1    // How much room there is above camera before the scrn.head hits the ceiling
#define KNEE_HEIGHT 2    // How tall obstacles the player can simply walk over without jumping
#define H_FOV (0.73f * H)  // Affects the horizontal field of vision
#define V_FOV (.2f * H)    // Affects the vertical field of vision
#define MAX_QUE 32   // MAXimum number of pending portal renders



typedef struct  xy
{
    float x;
    float y;
}               xy;

typedef struct  xyz
{
    float x;
    float y;
    float z;
}               xyz;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
typedef struct sectors
{
    float floor;
    float ceil;
    xy *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
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
    unsigned int NumSectors;
}           player;

typedef struct  item
{
    int sectorno;
    int sx1;
    int sx2;
}               item;

typedef struct  screen
{
    item queue[MAX_QUE];
    item *head;
    item *tail;
    item now;

    int ytop[W];
    int ybottom[W];
}               screen;

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
}               view_events;





// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define MIN(a,b)             (((a) < (b)) ? (a) : (b)) // MIN: Choose smaller of two scalars.
#define MAX(a,b)             (((a) > (b)) ? (a) : (b)) // MAX: Choose greater of two scalars.
#define CLAMP(a, mi, ma)      MIN(MAX(a, mi), ma)         // CLAMP: CLAMP value into set range.
#define VXS(x0, y0, x1, y1)    ((x0 * y1) - (x1 * y0))   // VXS: Vector cross product
// OVERLAP:  DeterMINe whether the two number ranges OVERLAP.
#define OVERLAP(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1) && MIN(b0, b1) <= MAX(a0, a1))
// INTERSECT_BOX: DeterMINe whether two 2D-boxes INTERSECT.


#define SECT (&sectors[player->sector])
#define VERT  SECT->vertex












//////////////////////////////////////////////////////////////////
///////         UTIL
//////////////////////////////////////////////////////////////////


void    quit(){
    // UnloadData(sectors);
    // SDL_Quit();
    exit(0);
}



xy new_xy(float x, float y){
    xy xy;

    xy.x = x;
    xy.y = y;
    return (xy);
}

xyz new_xyz(float x, float y, float z){
    xyz xyz;

    xyz.x = x;
    xyz.y = y;
    xyz.z = z;
    return (xyz);
}

// INTERSECT_BOX: DeterMINe whether two 2D-boxes INTERSECT.
int intersect_box(xy xy0, xy xy1, xy xy2, xy xy3){
    int overlap_x;
    int overlap_y;

    overlap_x = OVERLAP(xy0.x, xy1.x, xy2.x, xy3.x);
    overlap_y = OVERLAP(xy0.y, xy1.y, xy2.y, xy3.y);
    return (overlap_x  && overlap_y);
}

int intersect_box_handle(xy p, xy d, xy* vert, int s){
    xy p_d;
    xy vert0;
    xy vert1;

    p_d.x = p.x + d.x;
    p_d.y = p.y + d.y;
    vert0.x = vert[s + 0].x;
    vert0.y = vert[s + 0].y;
    vert1.x = vert[s + 1].x;
    vert1.y = vert[s + 1].y;
    return (intersect_box(p, p_d, vert0, vert1));
}

// POINT_SIDE: DeterMINe which side of a line the point is on. Return value: <0, =0 or >0.
float point_side(xy p, xy xy0, xy xy1){
    float x1_x0;
    float y1_y0;
    float px_x0;
    float py_y0;

    x1_x0 = xy1.x - xy0.x;
    y1_y0 = xy1.y - xy0.y;
    px_x0 = p.x - xy0.x;
    py_y0 = p.y - xy0.y;
    return (VXS(x1_x0, y1_y0, px_x0, py_y0));
}

float point_side_handle(xy p, xy d, xy* vert, int s){
    xy p_d;
    xy xy0;
    xy xy1;

    p_d.x = p.x + d.x;
    p_d.y = p.y + d.y;
    xy0.x = vert[s + 0].x;
    xy0.y = vert[s + 0].y;
    xy1.x = vert[s + 1].x;
    xy1.y = vert[s + 1].y;       
    return (point_side(p_d, xy0, xy1));
}

// INTERSECT: Calculate the point of INTERSECTion between two lines.
xy intersect(xy xy1, xy xy2, xy xy3, xy xy4){
    float vxs_12;
    float vxs_34;
    float y0;
    float x0;
    float xy;

    vxs_12 = VXS(xy1.x, xy1.y, xy2.x, xy2.y);
    vxs_34= VXS(xy3.x, xy3.y, xy4.x, xy4.y);
    x0 = VXS(vxs_12, (xy1.x - xy2.x), vxs_34, (xy3.x - xy4.x));
    y0 = VXS(vxs_12, (xy1.y - xy2.y), vxs_34, (xy3.y - xy4.y));
    xy = VXS((xy1.x - xy2.x), (xy1.y - xy2.y),
            (xy3.x - xy4.x), (xy3.y - xy4.y));
    return (new_xy((x0 / xy), (y0 / xy)));
}








//////////////////////////////////////////////////////////////////
///////        LOAD
//////////////////////////////////////////////////////////////////
player player_init(float x, float y, float angle, unsigned int n){
    player player;

    player.where.x = x;
    player.where.y = y;
    player.where.z = 0.0;
    player.velocity.x = 0;
    player.velocity.y = 0;
    player.velocity.z = 0;
    player.angle = angle;
    player.anglesin = 0;
    player.anglecos = 0;
    player.yaw = 0;
    player.sector = n;
    return (player);
}

static void LoadData(player *player, sectors **sector)
{

///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    sectors *sectors = *sector;

    FILE* fp = fopen("map.txt", "rt");//map-clear
    if(!fp) { perror("map.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int n, m, NumVertices = 0;
    unsigned int NumSectors = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                    { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sectors* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; ){ 
                    num = realloc(num, ++m * sizeof(*num)); 
                    num[m-1] = word[0]=='x' ? -1 : atoi(word); 
                    // printf("%d_%d\n", num[m-1], (m-1));
                }
                // printf("%d=\n", m);
                sect->npoints   = m /= 2;
                // printf("%d\n", m);
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) {
                    sect->neighbors[n] = num[m + n]; 
                    // printf("neib:%d--n:%d---num:%d[%d]\n", sect->neighbors[n], (n),num[m + n],(m + n));
                }
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                *player = player_init(v.x, v.y, angle, n); // TODO: Range checking
                player->where.z = sectors[player->sector].floor + EYE_HEIGHT;
        }
        player->NumSectors = NumSectors;

        printf("%u * %f\n", (&sectors[NumSectors-1])->npoints,(&sectors[NumSectors-1])->floor);printf("!!!!!!!!!!!!!\n");
    fclose(fp);
    free(vert);
}
static void UnloadData(sectors *sectors, player *player)
{
    for(unsigned a=0; a<player->NumSectors; ++a) free(sectors[a].vertex);
    for(unsigned a=0; a<player->NumSectors; ++a) free(sectors[a].neighbors);
    player->NumSectors = 0;
    free(sectors);
    sectors    = NULL;
   
}










//////////////////////////////////////////////////////////////////
///////         DRAW
//////////////////////////////////////////////////////////////////


// static SDL_Surface *surface = NULL;

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface *surface)
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

void approximate_edges(xy *t, xy near, xy i1, xy i2){
    if(t->y < near.y){
        if(i1.y > 0)
        {
            t->x = i1.x;
            t->y = i1.y;
        }
        else
        {
            t->x = i2.x;
            t->y = i2.y;
        }
    }
}

void frustrum(xy *t1, xy *t2){
    xy near;
    xy far;
    xy i2;
    xy i1;

    near = new_xy(1e-5f, 1e-4f);
    far = new_xy(20.f, 5);
    // Find an INTERSECTion between the wall and the approximate edges of player's view
    i2 = intersect(*t1, *t2, near, far);
    near.x *= -1.0;
    far.x *= -1.0;
    i1 = intersect(*t1, *t2, near, far);
    approximate_edges(t1, near, i1, i2);
    approximate_edges(t2, near, i1, i2);
}


screen screen_init(unsigned int player_sector){
    screen scrn;
    unsigned int i;

    scrn.head = scrn.queue;
    scrn.tail = scrn.queue;
    i = 0;
    while (i < W){
        scrn.ytop[i] = 0;
        scrn.ybottom[i] = H - 1;
        i++;
    }
    /* Begin whole-screen rendering from where the player is. */
    scrn.head->sectorno = player_sector;
    scrn.head->sx1 = 0;
    scrn.head->sx2 = W - 1;
    if(++scrn.head == (scrn.queue + MAX_QUE))
        scrn.head = scrn.queue;
    return (scrn);
}

static void DrawScreen(SDL_Surface *surface, player *player, sectors *sectors)
{
    screen scrn;
    int renderedsectors[player->NumSectors];

    unsigned int s;

    scrn = screen_init(player->sector);

    s = 0;
    while (s < player->NumSectors)
        renderedsectors[s++] = 0;

    while(scrn.head != scrn.tail) // render any other scrn.queued sectors
    {
        /* Pick a sector & slice from the scrn.queue to draw */
        scrn.now = *scrn.tail;
        if(++scrn.tail == scrn.queue+MAX_QUE) scrn.tail = scrn.queue;

        if(renderedsectors[scrn.now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
        ++renderedsectors[scrn.now.sectorno];
        struct sectors*  sect = &sectors[scrn.now.sectorno];
        /* Render each wall of this sector that is facing towards player-> */


        ///////////// SEGMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!
printf("  * %p\n", sect);printf("!!!!!!!!!!!!!\n");
        ////////////////////    sect->npoints   ////////////////
        for(s = 0; s < sect->npoints; ++s)
        {
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            float vx1 = sect->vertex[s+0].x - player->where.x, vy1 = sect->vertex[s+0].y - player->where.y;
            float vx2 = sect->vertex[s+1].x - player->where.x, vy2 = sect->vertex[s+1].y - player->where.y;
            /* Rotate them around the player's view */
            float pcos = player->anglecos, psin = player->anglesin;

            xy t1 = new_xy((vx1 * psin - vy1 * pcos), (vx1 * pcos + vy1 * psin));
            xy t2 = new_xy((vx2 * psin - vy2 * pcos), (vx2 * pcos + vy2 * psin));
            /* Is the wall at least partially in front of the player? */
            if(t1.y <= 0 && t2.y <= 0) continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            frustrum(&t1, &t2);

            /* Do perspective transformation */
            float xscale1 = H_FOV / t1.y, yscale1 = V_FOV / t1.y;    
            int x1 = W / 2 - (int)(t1.x * xscale1);
            float xscale2 = H_FOV / t2.y, yscale2 = V_FOV / t2.y;    
            int x2 = W / 2 - (int)(t2.x * xscale2);
            if(x1 >= x2 || x2 < scrn.now.sx1 || x1 > scrn.now.sx2) continue; // Only render if it's visible
            /* Acquire the floor and ceiling heights, relative to where the player's view is */
            float yceil  = sect->ceil  - player->where.z;
            float yfloor = sect->floor - player->where.z;
            /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
            int neighbor = sect->neighbors[s];
            float nyceil=0, nyfloor=0;
            ////////   ATTENTION !!! NO NEIGHBORS !!!
            if(neighbor >= 0) // Is another sector showing through this portal?
            {
                nyceil  = sectors[neighbor].ceil  - player->where.z;
                nyfloor = sectors[neighbor].floor - player->where.z;
            }
            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
            #define Yaw(y,z) (y + z * player->yaw)
            int y1a  = H/2 - (int)(Yaw(yceil, t1.y) * yscale1);
            int y1b = H/2 - (int)(Yaw(yfloor, t1.y) * yscale1);
            int y2a  = H/2 - (int)(Yaw(yceil, t2.y) * yscale2);
            int y2b = H/2 - (int)(Yaw(yfloor, t2.y) * yscale2);
            /* The same for the neighboring sector */
            int ny1a = H/2 - (int)(Yaw(nyceil, t1.y) * yscale1), ny1b = H/2 - (int)(Yaw(nyfloor, t1.y) * yscale1);
            int ny2a = H/2 - (int)(Yaw(nyceil, t2.y) * yscale2), ny2b = H/2 - (int)(Yaw(nyfloor, t2.y) * yscale2);

            /* Render the wall. */
            int beginx = MAX(x1, scrn.now.sx1), endx = MIN(x2, scrn.now.sx2);
            for(int x = beginx; x <= endx; ++x)
            {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = ((x - x1) * (t2.y - t1.y) / (x2-x1) + t1.y) * 8;
                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. CLAMP them. */
                int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = CLAMP(ya, scrn.ytop[x],scrn.ybottom[x]); // top
                int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = CLAMP(yb, scrn.ytop[x],scrn.ybottom[x]); // bottom

                /* Render ceiling: everything above this sector's ceiling height. */
                vline(x, scrn.ytop[x], cya-1, 0x111111 ,0x222222,0x111111, surface);
                /* Render floor: everything below this sector's floor height. */
                vline(x, cyb+1, scrn.ybottom[x], 0x0000FF,0x0000AA,0x0000FF, surface);

                /* Is there another sector behind this edge? */
                if(neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = CLAMP(nya, scrn.ytop[x],scrn.ybottom[x]);
                    int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = CLAMP(nyb, scrn.ytop[x],scrn.ybottom[x]);
                    /* If our ceiling is higher than their ceiling, render upper wall */
                    unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                    vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0, surface); // Between our and their ceiling
                    scrn.ytop[x] = CLAMP(MAX(cya, cnya), scrn.ytop[x], H-1);   // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom wall */
                    vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0, surface); // Between their and our floor
                    scrn.ybottom[x] = CLAMP(MIN(cyb, cnyb), 0, scrn.ybottom[x]); // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = 0x010101 * (255-z);
                    vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0, surface);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this wall. */
            if(neighbor >= 0 && endx >= beginx && (scrn.head+MAX_QUE+1-scrn.tail)%MAX_QUE)
            {
                *scrn.head = (struct item) { neighbor, beginx, endx };
                if(++scrn.head == scrn.queue+MAX_QUE) scrn.head = scrn.queue;
            }
        } // for s in sector's edges
    ++renderedsectors[scrn.now.sectorno];
    } 
}










//////////////////////////////////////////////////////////////////
///////         KEY EVENTS
//////////////////////////////////////////////////////////////////


move_events move_events_init(){
    move_events me;

    me.wsad[0] = 0;
    me.wsad[1] = 0;
    me.wsad[2] = 0;
    me.wsad[3] = 0;
    me.ground = 0;
    me.falling = 1;
    me.moving = 0;
    me.ducking = 0;
    me.yaw = 0;
    return (me);
}

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

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(xy d, player *player, sectors *sectors)
{
    unsigned int s;
    xy p;
     /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, POINT_SIDE will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    p = new_xy(player->where.x, player->where.y);
    s = 0;
    while (s < SECT->npoints){
        // printf("%d * %d\n", sect->neighbors[s],s);
        if(SECT->neighbors[s] >= 0
        && intersect_box_handle(p, d, VERT, s)
                && point_side_handle(p, d, VERT, s) < 0)
        {
            player->sector = SECT->neighbors[s];
            break;
        }
        s++;
    }
    player->where.x += d.x;
    player->where.y += d.y;
    player->anglesin = sinf(player->angle);
    player->anglecos = cosf(player->angle);
}


void hor_collision_detection(move_events *me, player *player, sectors *sectors){
    xy p;
    xy d;
    xy xyd;
    float hole_low;
    float hole_high;

    unsigned int s;
    if(me->moving)
    {
        p = new_xy(player->where.x, player->where.y);
        d = new_xy(player->velocity.x, player->velocity.y);
        // struct sector* sect = &sectors[player->sector];
        // struct xy* vert = sect->vertex;
        /* Check if the player is about to cross one of the sector's edges */
        s = 0;
        while (s < SECT->npoints){
            if(intersect_box_handle(p, d, VERT, s)
                && point_side_handle(p, d, VERT, s) < 0)
            {
                /* Check where the hole is. */
                hole_low  = SECT->neighbors[s] < 0 ?  9e9 : MAX(SECT->floor, sectors[SECT->neighbors[s]].floor);
                hole_high = SECT->neighbors[s] < 0 ? -9e9 : MIN(SECT->ceil,  sectors[SECT->neighbors[s]].ceil);
                /* Check whether we're bumping into a wall. */
                if(hole_high < player->where.z + HEAD_MARGIN
                || hole_low  > player->where.z - me->eyeheight + KNEE_HEIGHT)
                {
                    /* Bumps into a wall! Slide along the wall. */
                    /* This formula is from Wikipedia article "vector projection". */
                    xyd.x = VERT[s + 1].x - VERT[s + 0].x;
                    xyd.y = VERT[s + 1].y - VERT[s + 0].y;
                    d.x = xyd.x * (d.x * xyd.x + d.y * xyd.y) / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
                    d.y = xyd.y * (d.x * xyd.x + d.y * xyd.y) / (pow(xyd.x, 2.0) + pow(xyd.y, 2.0));
                    me->moving = 0;
                }
            }
            s++;
        }
        MovePlayer(d, player, sectors);
        me->falling = 1;
    }
}

void vert_collision_detection(move_events *me, player *player, sectors *sectors){
    float nextz;

    me->ground = !me->falling;
    if(me->falling)
    {
        player->velocity.z -= 0.05f; /* Add gravity */
        nextz = player->where.z + player->velocity.z;
        if(player->velocity.z < 0 && nextz  < sectors[player->sector].floor + me->eyeheight) // When going down
        {
            /* Fix to ground */
            player->where.z = sectors[player->sector].floor + me->eyeheight;
            player->velocity.z = 0;
            me->falling = 0;
            me->ground  = 1;
        }
        else if(player->velocity.z > 0 && nextz > sectors[player->sector].ceil) // When going up
        {
            /* Prevent jumping above ceiling */
            player->velocity.z = 0;
            me->falling = 1;
        }
        if(me->falling)
        {
            player->where.z += player->velocity.z;
            me->moving = 1;
        }
    }
}










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
    if(ve.pushing) me->moving = 1;
    return (ve);
}

void view_event(move_events *me, view_events *ve, player *player, sectors *sectors){
    player->angle += ve->x * 0.03f;
    me->yaw = CLAMP(me->yaw + ve->y * 0.05f, -5, 5);// +/- ve->y = inverse mouse
    player->yaw = me->yaw - player->velocity.z * 0.5f;
    MovePlayer(new_xy(0.0, 0.0), player, sectors);

    if(me->wsad[0]) {
        ve->move_vec[0] += player->anglecos * 0.2f;
        ve->move_vec[1] += player->anglesin * 0.2f;
    }
    if(me->wsad[1]) {
        ve->move_vec[0] -= player->anglecos * 0.2f;
        ve->move_vec[1] -= player->anglesin * 0.2f;
    }
    if(me->wsad[2]) {
        ve->move_vec[0] += player->anglesin * 0.2f;
        ve->move_vec[1] -= player->anglecos * 0.2f;
    }
    if(me->wsad[3]) {
        ve->move_vec[0] -= player->anglesin * 0.2f;
        ve->move_vec[1] += player->anglecos * 0.2f;
    }

    player->velocity.x = player->velocity.x * (1 - ve->acceleration) + ve->move_vec[0] * ve->acceleration;
    player->velocity.y = player->velocity.y * (1 - ve->acceleration) + ve->move_vec[1] * ve->acceleration;    
}








//////////////////////////////////////////////////////////////////
///////        
//////////////////////////////////////////////////////////////////

int main()
{
    move_events     me;
    view_events     ve;
    SDL_Window      *win;
    SDL_Surface     *surface;
    player          player;
    sectors         *sectors;

    sectors = NULL;
    me = move_events_init();
    LoadData(&player, &sectors);
    win = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED, 
                                    SDL_WINDOWPOS_CENTERED, 
                                    W, H, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(win);
    SDL_ShowCursor(SDL_DISABLE);
    while(1)
    {
        DrawScreen(surface, &player, sectors);
        SDL_UpdateWindowSurface(win);
        me.eyeheight = (me.ducking) ? DUCK_HEIGHT : EYE_HEIGHT;
        /* Vertical collision detection */
        vert_collision_detection(&me, &player, sectors);        
        /* Horizontal collision detection */
        hor_collision_detection(&me, &player, sectors);
        key_events(&me, &player);
        /* mouse aiMINg */
        ve = view_events_init(&me);
        view_event(&me, &ve, &player, sectors);       
        SDL_Delay(10);
    }
    quit();
    return 0;
}













































































