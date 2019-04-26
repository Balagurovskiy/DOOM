

#ifndef RENDER_SCALER_H
# define RENDER_SCALER_H

typedef struct scaler_set
{
    int a;
    int b;
    int c;
}              scaler_set_s;

typedef struct scaler
{
    int result;
    int bop;
    int fd;
    int ca;
    int cache;
}              scaler_s;

scaler_set_s set_scaler(int a, int b, int c);
scaler_s scaler_init(scaler_set_s ss, int d, int f);
int scaler_next(scaler_s *s);

#endif