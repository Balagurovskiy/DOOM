# include "parser.h"
# include "doom.h"


t_map *get_map(char *file_name)
{
    static t_map *map = NULL;

    if (ft_strequ(file_name, "#get"))
    {
        return (map);
    }
    else if (ft_strequ(file_name, "#del"))
    {
        map_del_sector(&(map->sector));
        ft_memdel((void **)&(map->floortexture));
        ft_memdel((void **)&(map->ceiltexture));
        ft_memdel((void **)&(map->uppertextures));
        ft_memdel((void **)&(map->lowertextures));
        ft_memdel((void **)&map);
    }
    else
    {
        map = (t_map *)for_each_gnl(file_name, (void *)&parser);
    }
    return (map);
}

SDL_Surface	*load_surface(char *filepath)
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

texture_set_s   connect_textures(t_map *map)
{
    texture_set_s txt_set;

    txt_set.floortexture = load_surface(map->floortexture);
    txt_set.ceiltexture = load_surface(map->ceiltexture);
    txt_set.uppertextures = load_surface(map->uppertextures);
    txt_set.lowertextures = load_surface(map->lowertextures);
    txt_set.size = map->texture_size;
    //TODO --NULL CHECK
    return (txt_set);
}


void set_sector(sectors *s,  t_map_sector *ms)
{
    s->npoints = ms->vertex_size;
    s->floor = TO_FLOAT(ms->floor);
    s->ceil = TO_FLOAT(ms->ceil);
    s->neighbors = (int *)malloc((s->npoints + 1) * sizeof(*s->neighbors));
    s->vertex = (xy *)malloc((s->npoints + 1) * sizeof(*s->vertex));
    s->vertex[s->npoints].x = TO_FLOAT(ms->vertex->x);
    s->vertex[s->npoints].y = TO_FLOAT(ms->vertex->y);
    s->neighbors[s->npoints] = -1;
}
void set_sector_vertexes(sectors *s,  t_map_sector *ms)
{
    t_map_vertex *msv;
    int ii;

    ii = 0;
    msv = ms->vertex;
    while (msv && ii < ms->vertex_size)
    {
        s->vertex[ii].x = TO_FLOAT(msv->x);
        s->vertex[ii].y = TO_FLOAT(msv->y);
        s->neighbors[ii] = msv->neighbor;
        msv = msv->next;
        ii++;
    }
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
        ms = ms->next;
		i++;
	}
	return (s);
}

level_s connect_level(t_map *map)
{
    t_map_sector *ms;
    level_s lvl;
    int i;
    int exits;

    lvl.sector = connect_sectors(map);
    lvl.texture = connect_textures(map);
    lvl.sectors_size = map->sector_size;
    i = 0;
    exits = 0;
    ms = map->sector;
    while (i < map->sector_size)
    {
        if (exits < 3 && ms->next_level_sector > -1)
        {
            lvl.end[exits] = i;
            lvl.next_level[exits] = ms->next_level;
            lvl.start[exits] = ms->next_level_sector;
            exits++;
        }
        ms = ms->next;
        i++;
    }
    return (lvl);
}