#ifndef _EMITTER_YMKANG
#define _EMITTER_YMKANG

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class emitter : public material {
public:
	vec3 lightColor;

	emitter(const vec3& light) : lightColor(light) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target, r_in.time());
		attenuation = lightColor;
		return false;
	}
};
#endif