#ifndef SPHERE_YMKANG_2017
#define SPHERE_YMKANG_2017

#include "hitable.h"
#include "material.h"

class sphere : public hitable {
public:
	vec3 center;
	float radius;
	material *mat_ptr;

	sphere() {}
	sphere(vec3 c, float r, material* mPtr) : center(c), radius(r), mat_ptr(mPtr) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	
};
#endif