#ifndef MARBLETEXTURE_YMKANG
#define MARBLETEXTURE_YMKANG
#include "texture.h"
#include "perlin.h"

class marbleTexture : public texture {
public:
	perlin noise;
	vec3 baseColor;
	float scale;

	marbleTexture() : baseColor(vec3(1, 1, 1)), scale(1.0) {}
	marbleTexture(vec3 c, float scaleValue = 1.0) : baseColor(c), scale(scaleValue) {}
	virtual vec3 value(float u, float v, const vec3& p) const {
		return baseColor*0.5*(1+sin(scale*p.z+10*noise.turbulence(scale*p)));
	}

};
#endif
