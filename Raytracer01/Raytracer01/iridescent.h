#ifndef _IRIDESCENTMETAL_YMKANG
#define _IRIDESCENTMETAL_YMKANG

#include "texture.h"
#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class iridescent : public material {
public:
	
	texture* albedo;

	
	float fuzz;

	iridescent(texture *a, float fuzziness) : albedo(a), fuzz(fuzziness) {}
	iridescent(vec3& a, float fuzziness) : albedo(new constantTexture(a)), fuzz(fuzziness) {}
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		
		vec3 rayOriginal = r_in.direction().getNormalized();
		vec3 ray_normal = dot(rayOriginal, rec.normal)*rec.normal;
		vec3 ray_tangent = rayOriginal - ray_normal;
		vec3 normal;
		float alpha = 0.1;
		float rValue = rand(0, 1);
		if (rValue<0.33) { // r path
			attenuation = vec3(2.0, 0.5, 0.5)*albedo->value(rec.u, rec.v, rec.p);
			normal = rec.normal + alpha*ray_tangent;		
			normal.normalize();
		}
		else if (rValue<0.66) { // g path
			attenuation = vec3(0.5, 2.0, 0.5)*albedo->value(rec.u, rec.v, rec.p);;
			normal = rec.normal;
		}
		else { // b path
			attenuation = vec3(0.5, 0.5, 2.0)*albedo->value(rec.u, rec.v, rec.p);
			normal = rec.normal - alpha*ray_tangent;
			normal.normalize();
		}

		vec3 reflected = reflect(r_in.direction().getNormalized(), normal);
		scattered = ray(rec.p, rec.p + reflected + fuzz*random_in_unit_sphere(), r_in.time());	


		if (dot(scattered.direction(),normal) > -0.01) {
			return true;			
		}
		else {
			attenuation = vec3(0, 0, 0);
			return false;
		}

	}
};
#endif