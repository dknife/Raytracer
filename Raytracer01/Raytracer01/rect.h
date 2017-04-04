#ifndef RECTANGLES_YMKANG
#define RECTANGLES_YMKANG

#include "hitable.h"
#include "material.h"

class xy_rect : public hitable {
public:
	material *mp;
	float x0, x1, y0, y1, k;

	xy_rect() {}
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) :
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {}

	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;

};
#endif