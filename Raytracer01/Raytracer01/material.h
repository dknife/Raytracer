#ifndef _MATERIAL_YMKANG
#define _MATERIAL_YMKANG

#include "ray.h"
#include "hitable.h"

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif