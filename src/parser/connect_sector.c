# include "parser.h"

static SDL_Surface	*load_surface(char *filepath)
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

txt_set.passive_object = load_surface("txt/q.png");

//    SDL_FillRect(txt_set.passive_object, NULL, SDL_MapRGB(txt_set.passive_object->format, 0, 0, 0));
//    SDL_SetColorKey(txt_set.passive_object, 0x00001000, SDL_MapRGB(txt_set.passive_object->format, 0, 0, 0));


SDL_SetColorKey(txt_set.passive_object, SDL_TRUE,
        SDL_MapRGB(txt_set.passive_object->format, 0, 0, 0));

    printf("w:%d___h:%d\n",txt_set.passive_object->w,txt_set.passive_object->h );
txt_set.active_object = load_surface("txt/e.png");
SDL_SetColorKey(txt_set.active_object, SDL_TRUE,
    SDL_MapRGB(txt_set.active_object->format, 0, 0, 0));

txt_set.curr_object = txt_set.passive_object;

    txt_set.size = map->texture_size;
    //TODO --NULL CHECK
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