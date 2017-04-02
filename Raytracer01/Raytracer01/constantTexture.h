#ifndef CONSTANTTEXTURE_YMKANG
#define CONSTANTTEXTURE_YMKANG
#include "texture.h"

class constantTexture : public texture {
public:
	vec3 color;

	constantTexture() {}
	constantTexture(vec3 c) : color(c) {}
	virtual vec3 value(float u, float v, const vec3& p) const {
		return color;
	}

};
#endif
