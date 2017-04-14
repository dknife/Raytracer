#ifndef RECTANGLES_YMKANG
#define RECTANGLES_YMKANG

#include "hitable.h"
#include "material.h"

class xy_rect : public hitable {
public:
	material *mp;
	float x0, x1, y0, y1, k;
	bool flipNormal;

	xy_rect() : flipNormal(false) {}
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) : flipNormal(false),
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {}

	void flip(void) { flipNormal = flipNormal ? false : true; }
	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool boundingBox(float t0, float t1, aabb& box) const;

};

class xz_rect : public hitable {
public:
	material *mp;
	float x0, x1, z0, z1, k;
	bool flipNormal;

	xz_rect() : flipNormal(false) {}
	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat) : flipNormal(false),
		x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

	void flip(void) { flipNormal = flipNormal ? false : true; }
	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool boundingBox(float t0, float t1, aabb& box) const;

};

class yz_rect : public hitable {
public:
	material *mp;
	float y0, y1, z0, z1, k;
	bool flipNormal;

	yz_rect() : flipNormal(false) {}
	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat) : flipNormal(false),
		y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

	void flip(void) { flipNormal = flipNormal ? false : true; }
	virtual bool hit(const ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool boundingBox(float t0, float t1, aabb& box) const;

};

#endif