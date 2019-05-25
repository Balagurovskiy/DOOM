#include "defines.h"
#include "doom.h"
#include "libft.h"

void text_pattern_0(char *file, player *p, SDL_Surface *surface)
{
	if (!ft_strequ((char const *)file, "level/map.doom"))
		return ;
    if(p->sector == 0)
    		render_massage("find some teleport :)", surface);
    if(p->sector == 2)
    		render_massage("u almoust there!!!", surface);
}

void text_pattern_1(char *file, player *p, SDL_Surface *surface)
{
	if (!ft_strequ((char const *)file, "level/map2.doom"))
		return ;
    if(p->sector == 0)
    		render_massage("its stagw 2 !!!wow \
    						so much lvl!!!", surface);
    if(p->sector == 4)
	render_massage("pff looks the same (((", surface);
}