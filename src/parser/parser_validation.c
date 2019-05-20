# include "parser.h"

static int vertex_validation(level_s lvl, int nsctr, int sctr, int vrtxs)
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

static void neighbor_validation(level_s lvl, int sctr, int vrtxs)
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

static void data_validation(level_s lvl, int sctr, int vrtxs)
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
        printf("%d<<<\n",excptn);
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
