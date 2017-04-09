#ifndef CHECKERTEXTUREUV_YMKANG
#define CHECKERTEXTUREUV_YMKANG
#include "checkerTexture.h"

class checkerTextureUV : public checkerTexture {
public:
	

	checkerTextureUV() {}
	checkerTextureUV(texture *t0, texture *t1, float f = 10.0)  {
		even = t0;
		odd = t1;
		freq = f;
	}

	virtual vec3 value(float u, float v, const vec3& p) const {

		float sines = sin(freq * u)*sin(freq * v);
		if (sines < 0) return odd->value(u, v, p);
		else return even->value(u, v, p);
	}

};
#endif