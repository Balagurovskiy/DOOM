# include "parser.h"
# include "doom.h"


t_map *get_map(char *file_name)
{
    static t_map *map = NULL;

    if (ft_strequ(file_name, "#get"))
    {
        return (map);
    }
    else if (ft_strequ(file_name, "#del")) {
        map_del_sector(&(map->sector));
        ft_memdel((void **) &(map->floortexture));
        ft_memdel((void **) &(map->ceiltexture));
        ft_memdel((void **) &(map->uppertextures));
        ft_memdel((void **) &(map->lowertextures));
        ft_memdel((void **) &map);
        map = NULL;
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
	s = (sectors *)malloc((map->sector_size + 1) * sizeof(sectors));
	while (i < map->sector_size)
	{
        set_sector(&(s[i]), ms);
        set_sector_vertexes(&(s[i]), ms);
        ms = ms->next;
		i++;
	}
	return (s);
}

void connect_next_level(level_s *lvl, t_map *map)
{
    t_map_sector *ms;
    int i;
    int exits;

    i = 3;
    while(i--)
        lvl->next_level[i] = NULL;
    i = 0;
    exits = 0;
    ms = map->sector;
    while (i < map->sector_size)
    {
        if (exits < 3 && ms->next_level_sector > -1 && ms->next_level)
        {
            lvl->end[exits] = i;
            lvl->next_level[exits] = ft_strjoin(ms->next_level, NULL);
            lvl->start[exits] = ms->next_level_sector;
            exits++;
        }
        ms = ms->next;
        i++;
    }
}

xy find_midd_point(sectors sct)
{
    xy start;
    int i;

    i = 0;
    start = new_xy(0.0, 0.0);
    while (i < sct.npoints)
    {
        start.x += sct.vertex[i].x;
        start.y += sct.vertex[i].y;
        i++;
    }
    start.x /= i;
    start.y /= i;
    return (start);
}
player init_player(float a, sectors *s, unsigned int s_in, int num_s)
{
    player player;
    xy where;

    where = find_midd_point(s[s_in]);
    player.sector = s_in;
    player.where.x = where.x;
    player.where.y = where.y;
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

int vertex_validation(level_s lvl, int nsctr, int sctr, int vrtxs)
{
    int nvrtx;
    int next_vrtx;
    int eq1;
    int eq2;

    next_vrtx = vrtxs + 1;
    if (next_vrtx >= lvl.sector[sctr].npoints)
        next_vrtx = 0;
    eq1 = 0;
    eq2 = 0;
    nvrtx = lvl.sector[nsctr].npoints;
    while(nvrtx--)
    {
        if(equals_xy(VRTX(sctr, vrtxs), VRTX(nsctr, nvrtx)))
            eq1 = 1;
        if(equals_xy(VRTX(sctr, next_vrtx), VRTX(nsctr, nvrtx)))
            eq2 = 1;
    }
    if (eq1 && eq2)
        return (1);
    return (0);
}

void neighbor_validation(level_s lvl, int sctr, int vrtxs)
{
    int nsctr;

    nsctr = lvl.sector[sctr].neighbors[vrtxs];
    if (nsctr < 0)
        return ;
    if (nsctr > lvl.sectors_size)
    {
        ft_putstr("EXCEPTION > sector > neighbor sector out of range\n");
        catch_exception(1);
    } else{
        if(!vertex_validation(lvl, nsctr, sctr, vrtxs))
        {
            ft_putstr("EXCEPTION > vertex > neighbors not synhronized\n");
            catch_exception(1);
        }
    }
}
void data_validation(level_s lvl, int sctr, int vrtxs)
{
    int excptn;
    int i;

    excptn = 0;
    i = 3;
    if (lvl.sector[sctr].ceil < 0 || lvl.sector[sctr].ceil > 50)
        excptn = 1;
    if (lvl.sector[sctr].floor < 0 || lvl.sector[sctr].floor > 50)
        excptn = 2;
    if (VRTX(sctr, vrtxs).x < 0.0 || VRTX(sctr, vrtxs).x > 50.0)
        excptn = 3;
    if (VRTX(sctr, vrtxs).y < 0.0 || VRTX(sctr, vrtxs).y > 50.0)
        excptn = 4;
    if (lvl.texture.size < 0 || lvl.texture.size > 1050)
        excptn = 5;
    while(i--)
        if (lvl.start[i] < 0 || lvl.start[i] > 25)
            excptn = 6;
    if (excptn)
    {
        ft_putstr("EXCEPTION > sector > invalid data\n");
        catch_exception(1);
    }
}
void sector_validation(level_s lvl)
{
    int sctr;
    int vrtxs;


    sctr = lvl.sectors_size;
    if (sctr < 1 || sctr > 25)
    {
        ft_putstr("EXCEPTION > sector > invalid sector number\n");
        catch_exception(1);
    }
    while(sctr--)
    {
        vrtxs = lvl.sector[sctr].npoints;
        if (vrtxs < 3 || vrtxs > 10)
        {
            ft_putstr("EXCEPTION > sector > invalid vertex number\n");
            catch_exception(1);
        }
        while(vrtxs--)
        {
            data_validation(lvl, sctr, vrtxs);
            neighbor_validation(lvl, sctr, vrtxs);
            if (catch_exception(0))
                return ;
        }
    }
}

level_s connect_level(t_map *map)
{
    level_s lvl;

    if (catch_exception(0) || !map)
        return (lvl);
    lvl.sector = connect_sectors(map);
    lvl.sectors_size = map->sector_size;
    lvl.texture = connect_textures(map);
    connect_next_level(&lvl, map);
    sector_validation(lvl);
//    get_map("#del");
    return (lvl);
}