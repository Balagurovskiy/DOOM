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
    unsigned int num_sectors;
}           player;

typedef struct  item
{
    int sectno;
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

    player *player;
    sectors *sector;
    SDL_Surface *surface;
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

typedef struct  line
{
    int x;
    int y1;
    int y2;
    int top;
    int middle;
    int bottom;
}               line;



// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define MIN(a,b)             (((a) < (b)) ? (a) : (b)) // MIN: Choose smaller of two scalars.
#define MAX(a,b)             (((a) > (b)) ? (a) : (b)) // MAX: Choose greater of two scalars.
#define CLAMP(a, mi, ma)      MIN(MAX(a, mi), ma)         // CLAMP: CLAMP value into set range.
#define VXS(x0, y0, x1, y1)    ((x0 * y1) - (x1 * y0))   // VXS: Vector cross product
// OVERLAP:  DeterMINe whether the two number ranges OVERLAP.

#define MVM(a0, a1, b0, b1) (MIN(a0, a1) <= MAX(b0, b1))
#define MAM(a0, a1, b0, b1) (MIN(b0, b1) <= MAX(a0, a1))
#define OVERLAP(a0, a1, b0, b1) (MVM(a0, a1, b0, b1) && MAM(a0, a1, b0, b1))

#define YAW(y, z, pyaw) (y + z * pyaw)

#define PROJECTION(t, y, yaw, scl) (H / 2) - (int)(YAW(t, y, yaw) * scl);

#define SECT (&sectors[player->sector])
#define SECTNOW (&sectors[scrn.now.sectno])
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

static sectors *LoadData(player *player)
{

///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    sectors *sectors;

    FILE* fp = fopen("map.txt", "rt");//map-clear
    if(!fp) { perror("map.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int n, m, NumVertices = 0;
    unsigned int num_sectors = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                    { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++num_sectors * sizeof(*sectors));
                struct sectors* sect = &sectors[num_sectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; ){ 
                    num = realloc(num, ++m * sizeof(*num)); 
                    num[m-1] = word[0]=='x' ? -1 : atoi(word); 
                }
                sect->npoints   = m /= 2;
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
        player->num_sectors = num_sectors;
    fclose(fp);
    free(vert);
    return (sectors);
}
static void UnloadData(sectors *sectors, player *player)
{
    for(unsigned a=0; a<player->num_sectors; ++a) free(sectors[a].vertex);
    for(unsigned a=0; a<player->num_sectors; ++a) free(sectors[a].neighbors);
    player->num_sectors = 0;
    free(sectors);
    sectors    = NULL;
   
}










//////////////////////////////////////////////////////////////////
///////         DRAW
//////////////////////////////////////////////////////////////////

void line_set_area(line *l, int x, int y1, int y2){
    l->x = x;
    l->y1 = y1;
    l->y2 = y2;
}

void line_set_color(line *l, int top, int middle, int bottom){
    l->top = top;
    l->middle = middle;
    l->bottom = bottom;
}

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(line l, SDL_Surface *surface)
{
    int *pix;
    int cy1;
    int cy2;
    unsigned int y;

    pix = (int *) surface->pixels;
    cy1 = CLAMP(l.y1, 0, H - 1);
    cy2 = CLAMP(l.y2, 0, H - 1);
    if(cy2 == cy1)
        pix[cy1 * W + l.x] = l.middle;
    else if(cy2 > cy1)
    {
        pix[cy1 * W + l.x] = l.top;
        y = cy1 + 1;
        while (y < cy2){
            pix[y * W + l.x] = l.middle;
            y++;
        }
        pix[cy2 * W + l.x] = l.bottom;
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


screen screen_init(SDL_Surface *surface, player *player, sectors *sector){
    screen scrn;
    unsigned int i;

    scrn.player = player;
    scrn.surface = surface;
    scrn.sector = sector;
    scrn.head = scrn.queue;
    scrn.tail = scrn.queue;
    i = 0;
    while (i < W){
        scrn.ytop[i] = 0;
        scrn.ybottom[i] = H - 1;
        i++;
    }
    /* Begin whole-screen rendering from where the player is. */
    scrn.head->sectno = player->sector;
    scrn.head->sx1 = 0;
    scrn.head->sx2 = W - 1;
    if(++scrn.head == (scrn.queue + MAX_QUE))
        scrn.head = scrn.queue;
    return (scrn);
}

xy get_endpoints(xy vertex, player *player){
    xy v;
    float endx;
    float endy;

    v.x = vertex.x - player->where.x;
    v.y = vertex.y - player->where.y;
    /* Rotate them around the player's view */
    endx = (v.x * player->anglesin - v.y * player->anglecos);
    endy = (v.x * player->anglecos + v.y * player->anglesin);
    return (new_xy(endx, endy));
}

int get_perspective(xy *scale, xy t){
    scale->x = H_FOV / t.y;
    scale->y = V_FOV / t.y;    
    return (W / 2 - (int)(t.x * scale->x));
}

typedef struct  floor_ceiling_heights
{
    float yceil;
    float yfloor;
    int neighbor;
    float nyceil;
    float nyfloor;
}               floor_ceiling_heights;

floor_ceiling_heights get_relative_heights(screen scrn, int s, int sect_no){
    floor_ceiling_heights fch;

    fch.yceil  = scrn.sector[sect_no].ceil  - scrn.player->where.z;
    fch.yfloor = scrn.sector[sect_no].floor - scrn.player->where.z;
    /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
    fch.neighbor = scrn.sector[sect_no].neighbors[s];
    fch.nyceil = 0;
    fch.nyfloor = 0;
    ////////   ATTENTION !!! NO NEIGHBORS !!!
    if(fch.neighbor >= 0) // Is another sector showing through this portal?
    {
        fch.nyceil  = scrn.sector[fch.neighbor].ceil  - scrn.player->where.z;
        fch.nyfloor = scrn.sector[fch.neighbor].floor - scrn.player->where.z;
    }
    return (fch);
}

typedef struct  floor_ceiling_coordinates
{
    int y1a;
    int y1b;

    int y2a;
    int y2b;

    int ny1a;
    int ny1b;

    int ny2a;
    int ny2b;
}               floor_ceiling_coordinates;

floor_ceiling_coordinates project_heights(screen scrn, floor_ceiling_heights fch, xy scale1, xy scale2, xy t1, xy t2){
    floor_ceiling_coordinates fcc;

    fcc.y1a = PROJECTION(fch.yceil, t1.y, scrn.player->yaw, scale1.y);
    fcc.y1b = PROJECTION(fch.yfloor, t1.y, scrn.player->yaw, scale1.y);

    fcc.y2a = PROJECTION(fch.yceil, t2.y, scrn.player->yaw,scale2.y);
    fcc.y2b = PROJECTION(fch.yfloor, t2.y, scrn.player->yaw, scale2.y);
    /* The same for the neighboring sector */
    fcc.ny1a = PROJECTION(fch.nyceil, t1.y, scrn.player->yaw, scale1.y);
    fcc.ny1b = PROJECTION(fch.nyfloor, t1.y, scrn.player->yaw,scale1.y);

    fcc.ny2a = PROJECTION(fch.nyceil, t2.y, scrn.player->yaw, scale2.y);
    fcc.ny2b = PROJECTION(fch.nyfloor, t2.y, scrn.player->yaw, scale2.y);
    return (fcc);
}

typedef struct  wall_x
{
    int z;

    int ya;
    int cya;

    int yb;
    int cyb;

    int nya;
    int cnya;

    int nyb;
    int cnyb;

}               wall_x;

void set_x_coordinate(screen scrn, int x, wall_x *wx, floor_ceiling_coordinates fcc, xy t1, xy t2, int x1, int x2){
    /* Calculate the Z coordinate for this point. (Only used for lighting.) */
    wx->z = ((x - x1) * (t2.y - t1.y) / (x2 - x1) + t1.y) * 8;
    /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. CLAMP them. */
    wx->ya = (x - x1) * (fcc.y2a - fcc.y1a) / (x2-x1) + fcc.y1a;
    wx->cya = CLAMP(wx->ya, scrn.ytop[x],scrn.ybottom[x]); // top
    wx->yb = (x - x1) * (fcc.y2b - fcc.y1b) / (x2-x1) + fcc.y1b;
    wx->cyb = CLAMP(wx->yb, scrn.ytop[x],scrn.ybottom[x]); // bottom
}

wall_x render_floor_ceiling(screen scrn, int x, floor_ceiling_coordinates fcc, xy t1, xy t2, int x1, int x2){
    line l;
    wall_x wx;

    set_x_coordinate(scrn, x, &wx, fcc, t1, t2, x1, x2);
    /* Render ceiling: everything above this sector's ceiling height. */
    line_set_area(&l, x, scrn.ytop[x], (wx.cya - 1));
    line_set_color(&l, 0x111111, 0x222222, 0x111111);
    vline(l, scrn.surface);
    /* Render floor: everything below this sector's floor height. */
    line_set_area(&l, x, (wx.cyb + 1), scrn.ybottom[x]);
    line_set_color(&l, 0x0000FF, 0x0000AA, 0x0000FF);
    vline(l, scrn.surface);
    return (wx);
}

void set_neighbor_x_coordinate(screen scrn, int x, wall_x *wx, floor_ceiling_coordinates fcc, int x1, int x2){
    /* Same for _their_ floor and ceiling */
    wx->nya = (x - x1) * (fcc.ny2a - fcc.ny1a) / (x2 - x1) + fcc.ny1a;
    wx->cnya = CLAMP(wx->nya, scrn.ytop[x], scrn.ybottom[x]);
    wx->nyb = (x - x1) * (fcc.ny2b - fcc.ny1b) / (x2 - x1) + fcc.ny1b;
    wx->cnyb = CLAMP(wx->nyb, scrn.ytop[x], scrn.ybottom[x]);
}

void render_neighbor_wall(screen scrn, int x, wall_x *wx, floor_ceiling_coordinates fcc, int x1, int x2){
    line l;

    set_neighbor_x_coordinate(scrn, x, wx, fcc, x1, x2);
    /* If our ceiling is higher than their ceiling, render upper wall */
    unsigned r1 = 0x010101 * (255 - wx->z);
    unsigned r2 = 0x040007 * (31 - (wx->z / 8));
    line_set_area(&l, x, wx->cya, (wx->cya - 1));
    line_set_color(&l, 0, ((x == x1||x == x2) ? 0 : r1), 0);
    vline(l, scrn.surface); // Between our and their ceiling
    scrn.ytop[x] = CLAMP(MAX(wx->cya, wx->cnya), scrn.ytop[x], H-1);   // Shrink the remaining window below these ceilings
    /* If our floor is lower than their floor, render bottom wall */   
    line_set_area(&l, x, (wx->cyb + 1), wx->cyb);
    line_set_color(&l, 0, ((x == x1||x == x2) ? 0 : r2), 0);
    vline(l, scrn.surface); // Between their and our floor    
    scrn.ybottom[x] = CLAMP(MIN(wx->cyb, wx->cnyb), 0, scrn.ybottom[x]); // Shrink the remaining window above these floors
}

void render_wall(screen scrn, int x, int neighbor, floor_ceiling_coordinates fcc, xy t1, xy t2, int x1, int x2){
    wall_x wx;
    line l;

    wx = render_floor_ceiling(scrn, x, fcc, t1, t2, x1, x2);
    /* Is there another sector behind this edge? */
    if(neighbor >= 0)//if(fch.neighbor >= 0)
        render_neighbor_wall(scrn, x, &wx, fcc, x1, x2);
    else
    {
        /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
        unsigned r = 0x010101 * (255 - wx.z);
        line_set_area(&l, x, wx.cya, wx.cyb);
        line_set_color(&l, 0, ((x == x1||x == x2) ? 0 : r), 0);
        vline(l, scrn.surface);
    }
}

void render_visible(screen scrn, int s, int sect_no, xy t1, xy t2, xy scale1, xy scale2, int x1, int x2){
    int beginx;
    int endx;
    int x;

    // Only render if it's visible
    if(!(x1 >= x2 || x2 < scrn.now.sx1 || x1 > scrn.now.sx2)) {
    /* Acquire the floor and ceiling heights, relative to where the player's view is */
        floor_ceiling_heights fch;
        fch = get_relative_heights(scrn, s, sect_no);
        /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
        floor_ceiling_coordinates fcc;
        fcc = project_heights(scrn, fch, scale1, scale2, t1, t2);
        /* Render the wall. */
        beginx = MAX(x1, scrn.now.sx1);
        endx = MIN(x2, scrn.now.sx2);
        x = beginx;
        while(x <= endx)
        {
            render_wall(scrn, x, fch.neighbor, fcc, t1, t2, x1, x2);
            x++;
        }
        /* Schedule the neighboring sector for rendering within the window formed by this wall. */
        if((fch.neighbor >= 0) && (endx >= beginx) && ((scrn.head + MAX_QUE + 1 - scrn.tail) % MAX_QUE))
        {
            scrn.head->sectno = fch.neighbor;
            scrn.head->sx1 = beginx;
            scrn.head->sx2 = endx;
            if(++scrn.head == (scrn.queue + MAX_QUE)) 
                scrn.head = scrn.queue;
        }
    }
}

void render(screen scrn){    
    int s;
    int sect_no;

    s = 0;
    sect_no = scrn.now.sectno;
    /* Render each wall of this sector that is facing towards player-> */// for s in sector's edges
    while(s < scrn.sector[sect_no].npoints)
    {
        /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
        xy t1 = get_endpoints(scrn.sector[sect_no].vertex[s + 0], scrn.player);
        xy t2 = get_endpoints(scrn.sector[sect_no].vertex[s + 1], scrn.player);
        /* Is the wall at least partially in front of the player? */
        if(!(t1.y <= 0 && t2.y <= 0)) {
        /* If it's partially behind the player, clip it against player's view frustrum */
            frustrum(&t1, &t2);
            /* Do perspective transformation */
            xy scale1;
            int x1 = get_perspective(&scale1, t1);
            xy scale2;
            int x2 = get_perspective(&scale2, t2);
            render_visible(scrn, s, sect_no, t1, t2, scale1, scale2, x1, x2);
        }
        s++;
    } 
}

void draw_screen(SDL_Surface *surface, player *player, sectors *sector)
{
    screen scrn;
    unsigned int s;
    int renderedsectors[player->num_sectors];

    scrn = screen_init(surface, player, sector);
    s = 0;
    while (s < player->num_sectors)
        renderedsectors[s++] = 0;
    while(scrn.head != scrn.tail) // render any other scrn.queued sectors
    {
        /* Pick a sector & slice from the scrn.queue to draw */
        scrn.now = *scrn.tail;
        if(++scrn.tail == scrn.queue+MAX_QUE)
            scrn.tail = scrn.queue;

        if(!(renderedsectors[scrn.now.sectno] & 0x21)) { // Odd = still rendering, 0x20 = give up
            ++renderedsectors[scrn.now.sectno];
            render(scrn);            
        }
    ++renderedsectors[scrn.now.sectno];
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
    sectors = LoadData(&player);
    win = SDL_CreateWindow("doom", SDL_WINDOWPOS_CENTERED, 
                                    SDL_WINDOWPOS_CENTERED, 
                                    W, H, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(win);
    SDL_ShowCursor(SDL_DISABLE);
    while(1)
    {
        draw_screen(surface, &player, sectors);
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













































































