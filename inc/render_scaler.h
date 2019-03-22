

#ifndef RENDER_SCALER_H
# define RENDER_SCALER_H

typedef struct scaler
{
    int result;
    int bop;
    int fd;
    int ca;
    int cache;
}              scaler_s;

scaler_s scaler_init(int a, int b, int c, int d, int f);
int scaler_next(scaler_s *s);

#endif