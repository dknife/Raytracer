#ifndef TEXTURE_YMKANG_2017
#define TEXTURE_YMKANG_2017

#include "vec3.h"

class texture {
public:
	virtual vec3 value(float u, float v, const vec3& p) const = 0;
};
#endif