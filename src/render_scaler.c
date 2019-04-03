
#include "defines.h"
#include "doom.h"
#include "render_scaler.h"

scaler_set_s set_scaler(int a, int b, int c)
{
    scaler_set_s ss;

    ss.a = a;
    ss.b = b;
    ss.c = c;
    return (ss);
}

scaler_s scaler_init(scaler_set_s ss, int d, int f)
{
    scaler_s s;

    s.result = d + (ss.b - 1 - ss.a) * (f - d) / (ss.c - ss.a);
    s.bop = ((f < d) ^ (ss.c < ss.a)) ? -1 : 1;
    s.fd = ABS(f - d);
    s.ca = ABS(ss.c - ss.a);
    s.cache = (int)((ss.b - 1 - ss.a) * ABS(f - d)) % ABS(ss.c - ss.a);
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