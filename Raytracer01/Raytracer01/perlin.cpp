#include "perlin.h"

vec3* perlin::ranvec = perlin_generate();
float *perlin::ranfloat = perlin_generateF();
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();