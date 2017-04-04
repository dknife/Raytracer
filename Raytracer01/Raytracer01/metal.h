#ifndef _METAL_YMKANG
#define _METAL_YMKANG

#include "texture.h"
#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class metal : public material {
public:

	texture* albedo;

	
	float fuzz;

	metal(texture *a, float fuzziness) : albedo(a), fuzz(fuzziness) {}
	metal(vec3& a, float fuzziness) : albedo(new constantTexture(a)), fuzz(fuzziness) {}
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(r_in.direction().getNormalized(), rec.normal);
		scattered = ray(rec.p, rec.p + reflected + fuzz*random_in_unit_sphere(), r_in.time());
		attenuation = albedo->value(0,0,rec.p);
		return (dot(scattered.direction(), rec.normal) > -0.01);		
	}
};
#endif