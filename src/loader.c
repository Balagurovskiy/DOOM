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

//////          COLLISION TEST
//sectors* init_map(int total_sectors)
//{
//    sectors* sector;
//    sectors* sect;
//
//    sector = malloc(total_sectors * sizeof(*sector));
//
//    sect = &sector[0];
//    sect->npoints = 8;
//    sect->floor = 0;
//    sect->ceil = 20;
//    int sector0x[] =    {0.0,    5.0,    5.0,    5.0,   5.0,   5.0,  5,     0,  0.0};
//    int sector0y[] =    {0.0,   0.0,    1.0,    5.0,   8.0,    9.0,  10,    10, 0.0};
//    int neighbors0[] =  {-1,     -1,      1,      -1,   2,      -1,  -1,   -1,   0};
//    sector_init(sect, sector0x, sector0y, neighbors0);
//
//    sect = &sector[1];
//    sect->npoints = 4;
//    sect->floor = 3;
//    sect->ceil = 8;
//    int sector1x[] =    {5.0,    7.0,    7.0,    5.0,  5.0};
//    int sector1y[] =    {1.0,   1.0,    5.0,    5.0,   1.0};
//    int neighbors1[] =  {-1,     3,      -1,     0,   0};
//    sector_init(sect, sector1x, sector1y, neighbors1);
//
//    sect = &sector[2];
//    sect->npoints = 4;
//    sect->floor = 0;
//    sect->ceil = 10;
//    int sector2x[] =    {5.0,    7.0,    7.0,    5.0,  5.0};
//    int sector2y[] =    {8.0,   8.0,    9.0,    9.0,   8.0};
//    int neighbors2[] =  {-1,     3,      -1,     0,   0};
//    sector_init(sect, sector2x, sector2y, neighbors2);
//
//    sect = &sector[3];
//    sect->npoints = 8;
//    sect->floor = 0;
//    sect->ceil = 20;
//    int sector3x[] =    {7.0,   12.0,   12.0,    7.0,  7,   7,   7,     7,  7.0};
//    int sector3y[] =    {0.0,   0.0,    10.0,    10.0, 9,   8,   5,     1,   0.0};
//    int neighbors3[] =  {-1,    -1,     -1,     -1,    2,   -1,  1,     -1,  0};
//    sector_init(sect, sector3x, sector3y, neighbors3);
//
//    return (sector);
//}
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
    sect->floor = 8;
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
    player.total_sectors = num_s;
    player.exit_doom = 0;
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
        printf("NO TEXTURE FILE");
        exit(0);
    }
    return (surf);
}

texture_set_s   texture_init()
{
    texture_set_s txt_set;

    txt_set.floortexture = load_image("txt/floor.bmp");//floor2.ppm
    txt_set.ceiltexture = load_image("txt/ceil2.ppm");
    txt_set.uppertextures = load_image("txt/pw.bmp");//floor.ppm
    txt_set.lowertextures = load_image("txt/cs.bmp");//wall2.ppm
    txt_set.size = 64;//1024
    //TODO --NULL CHECK


    return (txt_set);
}

texture_set_s   t1()
{
    texture_set_s txt_set;

    txt_set.floortexture = load_image("txt/floor2.ppm");
    txt_set.ceiltexture = load_image("txt/ceil2.ppm");
    txt_set.uppertextures = load_image("txt/floor.ppm");
    txt_set.lowertextures = load_image("txt/wall2.ppm");
    txt_set.size = 1024;//
    //TODO --NULL CHECK
    return (txt_set);
}

sectors* m1() {
    sectors *sector;
    sectors *sect;

    sector = malloc(3 * sizeof(*sector));

    sect = &sector[0];
    sect->npoints = 6;
    sect->floor = 0;
    sect->ceil = 15;
    int sector0x[] = {0, 10, 10, 7, 3, 0, 0};
    int sector0y[] = {0, 0, 10, 10, 10, 10, 0};
    int neighbors0[] = {-1, -1, -1, 1, -1, -1, 0};
    sector_init(sect, sector0x, sector0y, neighbors0);

    sect = &sector[1];
    sect->npoints = 4;
    sect->floor = 2;
    sect->ceil = 17;
    int sector1x[] =    {3,     7,  7, 3, 3};
    int sector1y[] =    {10,    10, 12, 12, 10};
    int neighbors1[] =  {0,     -1, 2, -1, 0};
    sector_init(sect, sector1x, sector1y, neighbors1);

    sect = &sector[2];
    sect->npoints = 4;
    sect->floor = 4;
    sect->ceil = 19;
    int sector2x[] =    {3,    7,      7,      3,      3};
    int sector2y[] =    {12,   12,     14,     14,     12};
    int neighbors2[] =  {1,     -1,    -1,     -1,     0};
    sector_init(sect, sector2x, sector2y, neighbors2);

    return (sector);
}
texture_set_s   t2()
{
    texture_set_s txt_set;

    txt_set.floortexture = load_image("txt/floor.ppm");
    txt_set.ceiltexture = load_image("txt/ceil2.ppm");
    txt_set.uppertextures = load_image("txt/floor2.ppm");
    txt_set.lowertextures = load_image("txt/wall2.ppm");
    txt_set.size = 1024;//
    //TODO --NULL CHECK
    return (txt_set);
}
sectors* m2() {
    sectors *sector;
    sectors *sect;

    sector = malloc(4 * sizeof(*sector));

    sect = &sector[0];
    sect->npoints = 6;
    sect->floor = 0;
    sect->ceil = 15;
    int sector0x[] =    {0, 5, 5,   5, 5,   0,  0};
    int sector0y[] =    {2, 2, 3,   7, 10,  10, 2};
    int neighbors0[] =  {2, -1, 3, -1, 1,   -1, 0};
    sector_init(sect, sector0x, sector0y, neighbors0);

    sect = &sector[1];
    sect->npoints = 4;
    sect->floor = 2;
    sect->ceil = 17;
    int sector1x[] = {0, 5,     5,      0,  0};
    int sector1y[] = {10, 10,   12,     12, 10};
    int neighbors1[] = {0, -1,   -1,    -1, 0};
    sector_init(sect, sector1x, sector1y, neighbors1);

    sect = &sector[2];
    sect->npoints = 4;
    sect->floor = 2;
    sect->ceil = 17;
    int sector2x[] =    {0,     5,     5,    0,  0};
    int sector2y[] =    {0,    0,       2,     2, 0};
    int neighbors2[] = {-1,     -1,   0,    -1, 0};
    sector_init(sect, sector2x, sector2y, neighbors2);

    sect = &sector[3];
    sect->npoints = 4;
    sect->floor = -2;
    sect->ceil = 12;
    int sector3x[] =    {5,      7,     7,     5,    5};
    int sector3y[] =    {3,     3,     7,     7,    3};
    int neighbors3[] = {-1,     -1,     -1,     0,    0};
    sector_init(sect, sector3x, sector3y, neighbors3);

    return (sector);
}
texture_set_s   t3()
{
    texture_set_s txt_set;

    txt_set.floortexture = load_image("txt/floor.ppm");
    txt_set.ceiltexture = load_image("txt/wall.ppm");
    txt_set.uppertextures = load_image("txt/ceil2.ppm");
    txt_set.lowertextures = load_image("txt/ceil2.ppm");
    txt_set.size = 1024;//
    //TODO --NULL CHECK
    return (txt_set);
}
sectors* m3() {
    sectors *sector;
    sectors *sect;

    sector = malloc(2 * sizeof(*sector));

    sect = &sector[0];
    sect->npoints = 5;
    sect->floor = 0;
    sect->ceil = 15;
    int sector0x[] =    {0,     3, 7,   10, 5,   0};
    int sector0y[] =    {2,     2, 2,   2, 10,   2};
    int neighbors0[] =  {-1,    1, -1, -1, -1,   0};
    sector_init(sect, sector0x, sector0y, neighbors0);

    sect = &sector[1];
    sect->npoints = 4;
    sect->floor = 2;
    sect->ceil = 17;
    int sector1x[] = {3,        7,     7,      3,  3};
    int sector1y[] = {0,        0,   2,     2,  0};
    int neighbors1[] = {-1,     -1,   0,    -1, 0};
    sector_init(sect, sector1x, sector1y, neighbors1);


    return (sector);
}