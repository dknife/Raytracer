#ifndef _LAMBERTIAN_YMKANG
#define _LAMBERTIAN_YMKANG

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class lambertian : public material {
public:
	vec3 albedo;

	lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target, r_in.time());
		attenuation = albedo;
		return true;
	}
};
#endif