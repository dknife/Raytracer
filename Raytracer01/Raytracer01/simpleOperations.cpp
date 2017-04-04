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

float trilinear_interp(float c[2][2][2], float u, float v, float w) {
	float accum = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				accum +=
					(i*u + (1 - i)*(1 - u)) *
					(j*v + (1 - j)*(1 - v)) *
					(k*w + (1 - k)*(1 - w)) * c[i][j][k];
					
			}
		}
	}
	return accum;
}


float perlin_interp(vec3 c[2][2][2], float u, float v, float w) {


	float uu=u*u*(3 - 2 * u);
	float vv=v*v*(3 - 2 * v);
	float ww=w*w*(3 - 2 * w);
	float accum = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				vec3 weight_v(u - i, v - j, w - k);

				accum +=
					(i*uu + (1 - i)*(1 - uu)) *
					(j*vv + (1 - j)*(1 - vv)) *
					(k*ww + (1 - k)*(1 - ww)) * dot(c[i][j][k], weight_v);
			}
		}
	}
	return accum;
}