#ifndef IMAGETEXTURE_YMKANG
#define IMAGETEXTURE_YMKANG
#include "texture.h"

class imageTexture : public texture {
public:
	unsigned char *data;
	int nx;
	int ny;

	imageTexture() {}
	imageTexture(unsigned char *pixels, int w, int h) : data(pixels), nx(w), ny(h) {}
	virtual vec3 value(float u, float v, const vec3& p) const {
		int i = u*nx;
		int j = (1 - v)*ny - 0.001;
		if (i < 0) i = 0;
		if (j < 0) j = 0;
		if (i > nx - 1) i = nx - 1;
		if (j > ny - 1) j = ny - 1;
		float r = int(data[3 * i + 3 * nx*j    ]) / 255.0;
		float g = int(data[3 * i + 3 * nx*j + 1]) / 255.0;
		float b = int(data[3 * i + 3 * nx*j + 2]) / 255.0;		
		return vec3(r, g, b);
	}

};
#endif
