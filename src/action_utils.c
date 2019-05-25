
#include "defines.h"
#include "doom.h"
#include "libft.h"
#include "parser.h"

void  change_level(level_s *lvl, player *p)
{
    int j;
    int next_start;
    float angle;
    char *next_lvl_temp;
    t_map *map_temp;

    j = 3;
    while(j--)
    {
        if(p->sector == lvl->end[j] && lvl->next_level[j])
        {
            next_start = lvl->start[j];
            angle = p->angle;
            next_lvl_temp = ft_strjoin(lvl->next_level[j], NULL);
            map_temp = get_map(next_lvl_temp);
            if (map_temp && next_start >= 0 && next_start < lvl->sectors_size)
            {
                free_level(lvl);
                *lvl = connect_level(map_temp);
                *p = init_player(angle, lvl->sector, next_start, lvl->sectors_size);
                save_file(next_lvl_temp);
            }
            ft_memdel((void**)&next_lvl_temp);
        }
    }
}

void  goto_level(level_s *lvl, player *p, char *level_name)
{
    t_map *map_temp;

    map_temp = get_map(level_name);
    free_level(lvl);
    *lvl = connect_level(map_temp);
    *p = init_player(0.0, lvl->sector, 0, lvl->sectors_size);
    save_file(level_name);
}

void action_got_key(player *p, level_s *lvl)
{
    if(lvl->sector[p->sector].object == 1 && p->action){
        lvl->texture.curr_object = lvl->texture.active_object;
        p->key = 1;
    }
}

void action_open_door(player *p, level_s *lvl, char *file,
                    void (*f)(player *p, level_s *l, char *f))
{
    if(lvl->sector[p->sector].object == 2 &&
        p->action && p->key)
    {
        p->key = 0;
        lvl->sector[p->sector].object = 0;
        (*f)(p, lvl, file);
    }
}

void action_controller(player *player, level_s *lvl, char *file)
{
    action_got_key(player, lvl);
    action_open_door(player, lvl, file, &door1);    
}