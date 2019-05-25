
#include "doom.h"
#include "libft.h"

void door1(player *p, level_s *lvl, char *file)
{
    if (ft_strequ((char const *)file, "level/sprite.doom"))
    {
        lvl->sector[2].floor = 2;
        lvl->sector[1].neighbors[1] = 2;
        lvl->sector[2].neighbors[3] = 1;
    }
}