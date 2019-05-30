# include "parser.h"

static SDL_Surface	*load_surface(char *filepath)
{
    SDL_Surface	*surf;

    surf = NULL;
    surf = IMG_Load(filepath);
    if (surf == NULL)
    {
        ft_putstr("EXCEPTION > textures > invalid texture file(");
        ft_putstr(filepath);
        ft_putstr(")\n");
        catch_exception(1);
    }
    return (surf);
}

texture_set_s   connect_textures(t_map *map)
{
    texture_set_s txt_set;

    txt_set.floortexture = load_surface(map->floortexture);
    txt_set.ceiltexture = load_surface(map->ceiltexture);
    txt_set.uppertextures = load_surface(map->uppertextures);
    txt_set.lowertextures = load_surface(map->lowertextures);
    txt_set.door = load_surface("textures/object/door.png");
    txt_set.sky = load_surface("textures/walls/Sky.png");
    txt_set.dec[0] = load_surface("textures/object/decor_A.png");
    txt_set.dec[1] = load_surface("textures/object/decor_B.png");
    txt_set.dec[2] = load_surface("textures/object/decor_C.png");
    txt_set.dec[3] = load_surface("textures/object/decor_D.png");
    txt_set.dec[4] = load_surface("textures/object/decor1.png");
    txt_set.key[0] = load_surface("textures/key_anim/key1.png");
    txt_set.key[1] = load_surface("textures/key_anim/key2.png");
    txt_set.key[2] = load_surface("textures/key_anim/key3.png");
    txt_set.key[3] = load_surface("textures/key_anim/key4.png");
    txt_set.key[4] = load_surface("textures/key_anim/key5.png");
    txt_set.key[5] = load_surface("textures/key_anim/key6.png");
    txt_set.key[6] = load_surface("textures/key_anim/key0.png");
    return (txt_set);
}

static void set_sector(sectors *s,  t_map_sector *ms)
{
    s->npoints = ms->vertex_size;
    s->floor = TO_FLOAT(ms->floor);
    s->ceil = TO_FLOAT(ms->ceil);
    s->neighbors = (int *)malloc((2 + s->npoints + 1) * sizeof(*s->neighbors));
    s->vertex = (xy *)malloc((s->npoints + 1) * sizeof(*s->vertex));
    s->vertex[s->npoints].x = ms->vertex->x;
    s->vertex[s->npoints].y = ms->vertex->y;
    s->neighbors[s->npoints] = -1;
}
static void set_sector_vertexes(sectors *s,  t_map_sector *ms)
{
    t_map_vertex *msv;
    int ii;

    ii = 0;
    msv = ms->vertex;
    while (msv && ii < ms->vertex_size)
    {
        s->vertex[ii].x = msv->x;
        s->vertex[ii].y = msv->y;
        s->neighbors[ii] = msv->neighbor;
        msv = msv->next;
        ii++;
    }
    s->neighbors[ms->vertex_size + 1] = -1;
    s->neighbors[ms->vertex_size + 2] = -1;
}

sectors *connect_sectors(t_map *map)
{
	int i;
    sectors *s;
    t_map_sector *ms;


	i = 0;
    ms = map->sector;
	s = (sectors *)malloc((map->sector_size) * sizeof(sectors));
	while (i < map->sector_size)
	{
        set_sector(&(s[i]), ms);
        set_sector_vertexes(&(s[i]), ms);
        set_sector_object(&(s[i]), ms);
        ms = ms->next;
		i++;
	}    
	return (s);
}