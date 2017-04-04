#ifndef NOISETEXTURE_YMKANG
#define NOISETEXTURE_YMKANG
#include "texture.h"
#include "perlin.h"

class noiseTexture : public texture {
public:
	perlin noise;
	vec3 baseColor;
	float scale;

	noiseTexture() : baseColor(vec3(1,1,1)), scale(1.0) {}
	noiseTexture(vec3 c, float scaleValue=1.0) : baseColor(c), scale(scaleValue) {}
	virtual vec3 value(float u, float v, const vec3& p) const {
		return baseColor*noise.turbulence(scale*p);
	}

};
#endif
