#ifndef PERLIN_YMKANG_2017
#define PERLIN_YMKANG_2017

#include "simpleOperations.h"

class perlin {
public:

	// function pointers ------------------
	static vec3* ranvec;
	static float* ranfloat;
	static int*  perm_x;
	static int*  perm_y;
	static int*  perm_z;
	// ----------------------------------

	float noise(const vec3& p) const {

		int i = floor(p.x);
		int j = floor(p.y);
		int k = floor(p.z);

		float u = p.x - i;
		float v = p.y - j;
		float w = p.z - k;

		vec3 c[2][2][2];
		for (int di = 0; di < 2; di++) {
			for (int dj = 0; dj < 2; dj++) {
				for (int dk = 0; dk < 2; dk++) {
					c[di][dj][dk] = ranvec[	perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]	];

				}
			}
		}
		return perlin_interp(c, u, v, w);		

	}

	float turbulence(const vec3& p, int depth = 7) const {
		float accum = 0;
		vec3 temp_p = p;
		float weight = 1.0;
		for (int i = 0; i < depth; i++) {
			accum += weight * noise(temp_p);
			weight *= 0.5;
			temp_p = temp_p * 2;
		}
		return fabs(accum);
	}

	static float* perlin_generateF() {
		float *p = new float[256];
		for (int i = 0; i < 256; i++) {
			p[i] = rand(0, 1);
		}
		return p;		
	}

	static vec3* perlin_generate() {
		vec3 *p = new vec3[256];
		for (int i = 0; i < 256; i++) {
			p[i] = vec3(rand(-1, 1), rand(-1, 1), rand(-1, 1)).getNormalized();
		}
		return p;
	}

	static void permute(int *p, int n) {
		for (int i = n - 1; i>0; i--) {
			int target = int(rand(0, 1)*(i + 1));
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}
		return;
	}

	static int* perlin_generate_perm() {
		int *p = new int[256];
		for (int i = 0; i < 256; i++) {
			p[i] = i;
		}
		permute(p, 256);
		return p;
	}


};


#endif
