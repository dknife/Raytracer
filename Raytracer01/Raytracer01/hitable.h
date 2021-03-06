#ifndef HITABLE_YMKANG_2017
#define HITABLE_YMKANG_2017

#include "ray.h"
#include "aabb.h"

class material;

struct hit_record {
	float t;
	float u, v;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool boundingBox(float t0, float t1, aabb& box) const = 0;
};

#endif

