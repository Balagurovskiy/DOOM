# include "parser.h"

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