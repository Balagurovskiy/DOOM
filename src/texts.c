#include "defines.h"
#include "doom.h"
#include "libft.h"

void text_pattern_0(char *file, player *p, SDL_Surface *surface)
{
	if (!ft_strequ((char const *)file, "level/0000.story"))
		return ;
    if(p->sector == 0 || p->sector <= 5)
        render_massage("You are lost and need to find a way out...", surface);
    if(p->sector == 12)
		render_massage("Wow secret place", surface);
    if(p->sector == 8 && !p->key)
        render_massage("Damn! Need a key !", surface);
    if(p->sector == 8 && p->key)
        render_massage("Lets try out this key", surface);
    if(p->sector == 9)
        render_massage("Yeee here we go !", surface);
    if(p->sector == 16)
        render_massage("Just a window to nowhere...", surface);
    if(p->sector >= 20 && p->sector <= 22)
        render_massage("Looks familiar...", surface);
}
void text_pattern_01(char *file, player *p, SDL_Surface *surface)
{
    if (!ft_strequ((char const *)file, "level/0001.story"))
        return ;
    if(p->sector >= 1 && p->sector <= 3 && !p->key)
        render_massage("Great - more dungeon ...", surface);
    if(p->sector == 4 && !p->key)
        render_massage("Up or down ? Hmmmm", surface);
    if(p->sector == 10 && !p->key)
        render_massage("Looks like nothing", surface);
    if((p->sector == 8 || p->sector == 9) && !p->key)
        render_massage("Whats that ?", surface);
    if((p->sector == 15 || p->sector == 16) && !p->key)
        render_massage("Wow a key !!!", surface);
    if((p->sector == 15 || p->sector == 16 || p->sector == 17) && p->key)
        render_massage("EEEEeeee booooyyyyy he he he", surface);
}

void text_pattern_1(char *file, player *p, SDL_Surface *surface)
{
	if (ft_strequ((char const *)file, "level/0100.story"))
	{
        if(p->sector == 0 || p->sector == 1)
    		render_massage("Oh another weird place ...", surface);
        if(p->sector == 11 && !p->key)
            render_massage("Ofcourse ... locked", surface);
        if(p->sector == 11 && p->key)
            render_massage("Come on", surface);
    }
    if (ft_strequ((char const *)file, "level/0101.story"))
    {
        if((p->sector == 12 || p->sector == 13 || p->sector == 16) && !p->key)
            render_massage("Hey there have to be a key !", surface);
        if(p->sector == 19)
            render_massage("There you go", surface);
    }
}

void text_pattern_2(char *file, player *p, SDL_Surface *surface)
{
    if (!ft_strequ((char const *)file, "level/0200.story"))
        return ;
    if(p->sector == 0 || p->sector == 1 || p->sector == 2)
        render_massage("Great. What next ? More doors ?", surface);
    if(p->sector >= 14 && p->sector <= 23)
        render_massage("Arrrhh what a nice place ...", surface);
    if((p->sector == 3 || p->sector == 7 ||
            p->sector == 13 || p->sector == 13) && !p->key)
        render_massage("Surprise !!! ANOTHER DOOR !!!", surface);
    if(p->sector >= 4 && p->sector <= 5 )
    {
        if (p->key)
            render_massage("Open up!", surface);
        else
            render_massage("Pf closed", surface);
    }
    if(p->sector >= 24 && p->sector <= 32 && p->key)
        render_massage("YEAH YOU WON SOMETHING!!!", surface);
}