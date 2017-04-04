#ifndef _SIMPLEOPERATIONS_YMKANG
#define _SIMPLEOPERATIONS_YMKANG

#include "vec3.h"

double rand(double minV, double maxV);
vec3 random_in_unit_sphere();
vec3 random_in_unit_disk();

vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);
float schlick(float cosine, float ref_idx);

float trilinear_interp(float c[2][2][2], float u, float v, float w);
float perlin_interp   (vec3  c[2][2][2], float u, float v, float w);

#endif