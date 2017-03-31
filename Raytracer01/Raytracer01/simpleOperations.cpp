#include "simpleOperations.h"
#include <stdlib.h>

double rand(double minV, double maxV) {
	double interval = maxV - minV;
	return minV + interval * ((rand() % RAND_MAX) / double(RAND_MAX));
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(rand(0.0, 1.0), rand(0.0, 1.0), rand(0.0, 1.0)) - vec3(1.0, 1.0, 1.0);
	} while (p.lenSquare() >= 1.0);

	return p;
}

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0 * vec3(rand(0.0, 1.0), rand(0.0, 1.0), 0.0) - vec3(1.0, 1.0, 0.0);
	} while ( dot(p,p) >= 1.0);

	return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2.0*dot(v, n)*n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = v.getNormalized();
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if (discriminant > 0) {
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	else
		return false;
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0*r0;
	return r0 + (1.0 - r0)*pow((1.0 - cosine), 5);
}