# include "parser.h"
# include "doom.h"

//level_s *get_level()
//{
//
//}

t_map *get_map(char *file_name)
{
	return((t_map *)for_each_gnl(file_name, (void *)&parser));
}

sectors *connect_sectors(t_map *map)
{
	int i;
    sectors *s;
    t_map_sector *ms;
    t_map_vertex *msv;

	i = 0;
    ms = map->sector;
	s = (sectors *)malloc((map->sector_size) * sizeof(s));
	while (i < map->sector_size)
	{
		
        s[i].npoints = ms->vertex_size;
        s[i].floor = TO_FLOAT(ms->floor);
        s[i].ceil = TO_FLOAT(ms->ceil);

        s[i].neighbors = (int *)malloc((s[i].npoints + 1) * sizeof(*s->neighbors));
        s[i].vertex = (xy *)malloc((s[i].npoints + 1) * sizeof(*s->vertex));

        // s[i].vertex[s[i].npoints].x = TO_FLOAT(ms->vertex->x);
        // s[i].vertex[s[i].npoints].y = TO_FLOAT(ms->vertex->y);
        // s[i].neighbors[s[i].npoints] = -1;

        int ii = 0;
        msv = ms->vertex;
		while (ii < ms->vertex_size)
		{            
            // s[i].vertex[ii].x = TO_FLOAT(msv->x);
            // s[i].vertex[ii].y = TO_FLOAT(msv->y);
            // s[i].neighbors[ii] = msv->neighbor;

            printf("%p || %f  %f  %d\n", msv, TO_FLOAT(msv->x), TO_FLOAT(msv->y), msv->neighbor);
            // printf("%f  %f  %d\n\n", s[i].vertex[ii].x,s[i].vertex[ii].y, s[i].neighbors[ii]);
            msv = msv->next;
			ii++;
		}
        printf("-------\n");
        ms = ms->next;
		i++;
	}
    exit(0);
	return (s);
}