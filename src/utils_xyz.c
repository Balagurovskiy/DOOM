#include "defines.h"
#include "doom.h"
#include "utils.h"
//////////////////////////////////////////////////////////////////
///////         UTIL
//////////////////////////////////////////////////////////////////

xy new_xy(float x, float y){
    xy xy;

    xy.x = x;
    xy.y = y;
    return (xy);
}

xyz new_xyz(float x, float y, float z){
    xyz xyz;

    xyz.x = x;
    xyz.y = y;
    xyz.z = z;
    return (xyz);
}