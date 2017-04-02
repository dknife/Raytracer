#ifndef CHECKERTEXTURE_YMKANG
#define CHECKERTEXTURE_YMKANG
#include "texture.h"

class checkerTexture : public texture {
public:
	texture *odd;
	texture *even;
	float freq;

	checkerTexture() {}
	checkerTexture(texture *t0, texture *t1, float f=10.0) : even(t0), odd(t1), freq(f) {}

	virtual vec3 value(float u, float v, const vec3& p) const {
		
		float sines = sin(freq * p.x)*sin(freq * p.y)*sin(freq*p.z);
		if (sines < 0) return odd->value(u, v, p);
		else return even->value(u, v, p);
	}

};
#endif