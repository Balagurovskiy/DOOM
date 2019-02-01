
# include <stdio.h>

typedef struct	move_events
{
	int wsad[4];
	int ground;
	int falling;
	int moving;
	int ducking;
}				move_events;

move_events move_events_init(){
	move_events me;

	me.wsad[0] = 0;
	me.wsad[1] = 0;
	me.wsad[2] = 0;
	me.wsad[3] = 0;
	me.ground = 0;
	me.falling = 1;
	me.moving = 0;
	return (me);
}

void move(move_events *me){
	me->falling = 5;
}

int main(void)
{
	move_events me;
	me = move_events_init();
	printf("falling:%d \n", me.falling);
	move(&me);
	printf("2falling:%d \n", me.falling);
	return 0;
}