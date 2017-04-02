#ifndef _METAL_YMKANG
#define _METAL_YMKANG

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class metal : public material {
public:
	vec3 albedo;
	float fuzz;

	metal(const vec3& a, float fuzziness) : albedo(a), fuzz(fuzziness) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(r_in.direction().getNormalized(), rec.normal);
		scattered = ray(rec.p, rec.p + reflected + fuzz*random_in_unit_sphere(), r_in.time());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > -0.01);		
	}
};
#endif