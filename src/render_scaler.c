
#include "defines.h"
#include "doom.h"
#include "render_scaler.h"

scaler_s scaler_init(int a, int b, int c, int d, int f)
{
    scaler_s s;

    s.result = d + (b - 1 - a) * (f - d) / (c - a);
    s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
    s.fd = ABS(f - d);
    s.ca = ABS(c - a);
    s.cache = (int)((b - 1 - a) * ABS(f - d)) % ABS(c - a);
    return (s);
}

int scaler_next(scaler_s *s)
{
    s->cache += s->fd;
    while (s->cache >= s->ca)
    {
        s->result += s->bop;
        s->cache -= s->ca;
    }
    return s->result;
}