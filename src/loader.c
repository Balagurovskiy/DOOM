#include "utils.h"
#include "doom.h"
#include "defines.h"
#include "render.h"

void sector_init(sectors* s, int sx[], int sy[], int n[])
{
    int i = 0;

    s->neighbors = (char *)malloc((s->npoints + 1) * sizeof(*s->neighbors));
    s->vertex = (xy *)malloc((s->npoints + 1) * sizeof(*s->vertex));
    while (i < (s->npoints + 1)){
        s->vertex[i].x = sx[i];
        s->vertex[i].y = sy[i];
        s->neighbors[i] = n[i];
        i++;
    }
}


sectors* init_map(int num_sectors)
{
    sectors* sector;
    sectors* sect;

    sector = malloc(num_sectors * sizeof(*sector));

    sect = &sector[0];
    sect->npoints = 4;
    sect->floor = 0;
    sect->ceil = 13;
    int sector0x[] =    {0.0,    0.0,    6.0,    5.0,    0.0};
    int sector0y[] =    {15.0,   0.0,    5.0,    10.0,   15.0};
    int neighbors0[] =  {-1,     1,      3,      4,     0};
    sector_init(sect, sector0x, sector0y, neighbors0);

    sect = &sector[1];
    sect->npoints = 5;
    sect->floor = 9;
    sect->ceil = 29;
    int sector2x[] =    {0.0,    15.0,    15.0,    10.0,    6.0,   0.0};
    int sector2y[] =    {0.0,    0.0,     5.0,     5.0,     5.0,   0.0};
    int neighbors2[] =  {-1,     -1,      2,       3,      0,     0};
    sector_init(sect, sector2x, sector2y, neighbors2);

    sect = &sector[2];
    sect->npoints = 6;
    sect->floor = 6;
    sect->ceil = 26;
    int sector1x[] =    {5.0,    5.0,    10.0,   15.0,    15.0,    10.0,    5.0};
    int sector1y[] =    {10.0,   10.0,   5.0,    5.0,     15.0,    10.0,    10.0};
    int neighbors1[] =  {3,      3,      1,     -1,       4,       4,       0};
    sector_init(sect, sector1x, sector1y, neighbors1);

    sect = &sector[3];
    sect->npoints = 3;
    sect->floor = 13;
    sect->ceil = 18;
    int sector3x[] =    {6.0,    10.0,    5.0,    6.0};
    int sector3y[] =    {5.0,    5.0,     10.0,   5.0};
    int neighbors3[] =  {1,      2,       0,      0};
    sector_init(sect, sector3x, sector3y, neighbors3);

    sect = &sector[4];
    sect->npoints = 4;
    sect->floor = 3;
    sect->ceil = 23;
    int sector4x[] =    {0.0,   5.0,     10.0,    15.0,   0.0};
    int sector4y[] =    {15.0,  10.0,    10.0,    15.0,   15.0};
    int neighbors4[] =  {0,     2,       2,       -1,     0};
    sector_init(sect, sector4x, sector4y, neighbors4);

    return (sector);
}

player init_player(xy x_y, float a, sectors *s, unsigned int s_in, int num_s)
{
    player player;

    player.sector = s_in;
    player.where.x = x_y.x;
    player.where.y = x_y.y;
    player.where.z = s[player.sector].floor + EYE_HEIGHT;
    player.velocity.x = 0;
    player.velocity.y = 0;
    player.velocity.z = 0;
    player.angle = a;
    player.anglesin = sinf(player.angle);
    player.anglecos = cosf(player.angle);
    player.yaw = 0;
    player.num_sectors = num_s;
    return (player);
}

SDL_Surface	*load_image(char *filepath)
{
    SDL_Surface	*surf;

    surf = NULL;
    surf = IMG_Load(filepath);
    if (surf == NULL)
    {
        //ft_putendl(IMG_GetError());
        exit(0);
    }
    return (surf);
}

texture_set_s   texture_init()
{
    texture_set_s txt_set;

    txt_set.floortexture = load_image("txt/floor.ppm");
    txt_set.ceiltexture = load_image("txt/wall2.ppm");
    txt_set.uppertextures = load_image("txt/wall3.ppm");
    txt_set.lowertextures = load_image("txt/wall.ppm");
    //TODO --NULL CHECK

    int i = 0;
    while(i < 1024)
    {
        txt_set.f[i] = (int *)malloc(1024 * sizeof(int*));
        txt_set.u[i] = (int *)malloc(1024 * sizeof(int*));
        txt_set.c[i] = (int *)malloc(1024 * sizeof(int*));
        txt_set.l[i] = (int *)malloc(1024 * sizeof(int*));
        int j = 0;
        while(j < 1024)
        {
            txt_set.f[i][j] = 11571537;
            txt_set.u[i][j] = 9261883;
            txt_set.c[i][j] = 12030530;
            txt_set.l[i][j] = 7815191;
            j++;
        }
        i++;
    }

    return (txt_set);
}