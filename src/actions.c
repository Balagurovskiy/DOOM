
#include "doom.h"
#include "libft.h"

void door0000(player *p, level_s *lvl, char *file)
{
    if (ft_strequ((char const *)file, "level/0000.story"))
    {
        lvl->sector[8].neighbors[2] = 9;
        lvl->sector[9].neighbors[0] = 8;
    }
    if (ft_strequ((char const *)file, "level/0100.story"))
    {
        lvl->sector[11].neighbors[3] = 15;
        lvl->sector[15].neighbors[0] = 11;
    }
    if (ft_strequ((char const *)file, "level/0200.story"))
    {
        lvl->sector[5].neighbors[2] = 24;
    }
}