
# include "defines.h"
# include "doom.h"
# include "render.h"
# include "render_wall.h"


edge_s edge_init(player *player, sectors *sect, int s)
{
    edge_s edge;
    /* Acquire the x,y coordinates of the two vertexes forming the edge of the sector */
    /* Transform the vertices into the player's view */
    edge.v1.x = sect->vertex[s+0].x - player->where.x;
    edge.v1.y = sect->vertex[s+0].y - player->where.y;
    edge.v2.x = sect->vertex[s+1].x - player->where.x;
    edge.v2.y = sect->vertex[s+1].y - player->where.y;
    /* Rotate them around the player's view */
    edge.pcos = player->anglecos;
    edge.psin = player->anglesin;
    edge.t1.x = edge.v1.x * edge.psin - edge.v1.y * edge.pcos;
    edge.t1.z = edge.v1.x * edge.pcos + edge.v1.y * edge.psin;
    edge.t2.x = edge.v2.x * edge.psin - edge.v2.y * edge.pcos;
    edge.t2.z = edge.v2.x * edge.pcos + edge.v2.y * edge.psin;
    return (edge);
}

void schedule(screen *scrn, heights_s heights, int s)
{
    if (HAS_NGHBR_NOW(s) && NOT_END && HAS_NEXT_QUE)
    {
        scrn->head->sectorno = NGHBR_NOW(s);
        scrn->head->sx1 = heights.beginx;
        scrn->head->sx2 = heights.endx;
        if (++scrn->head == scrn->queue + MAX_QUE)
            scrn->head = scrn->queue;
    }
}

void render_towards(screen *scrn)
{
    heights_s heights;
    perspective_s perspect;
    int s;

    /* Render each wall of this sector that is facing towards player-> */
    s = 0;
    while(s < SECT_NOW->npoints)
    {
        scrn->edge = edge_init(scrn->player, SECT_NOW, s);
        /* Is the wall at least partially in front of the player? */
        scrn->txt_data.u0 = 0;
        scrn->txt_data.u1 = (scrn->txt->size - 1);
        if (IS_FRONT(scrn->edge))
        {
            /* If it's partially behind the player, clip it against player's view frustrum */
            view_intersection_with_wall(scrn);
            /* Do perspect transformation */
            perspect = perspective_init(scrn->edge);
            if (perspect.x1 < perspect.x2)
            {
                if (perspect.x2 > scrn->now.sx1 && perspect.x1 < scrn->now.sx2)
                {
                    /* Acquire and transform the floor and ceiling heights */
                    heights = heights_init(scrn, perspect, s);
                    /* Render the wall. */
                    render_the_wall(scrn, perspect, heights, s);
                    /* Schedule the other sector for rendering within the window formed by this wall. */
                    schedule(scrn, heights, s);
                }
            }
        }
        s++;
    }
}
