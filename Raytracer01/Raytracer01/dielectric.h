#ifndef DIELECTRIC_YMKANG_2017
#define DIELECTRIC_YMKANG_2017

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class dielectric : public material {
public:
	float ref_idx;

	dielectric(float ri) : ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float cosine;
		float reflect_prob;

		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().len();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().len();
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
			//scattered = ray(rec.p, refracted + rec.p);
		}
		else {
			scattered = ray(rec.p, reflected, r_in.time());
			reflect_prob = 1.0;
		}

		if (rand(0.0, 1.0) < reflect_prob) {
			scattered = ray(rec.p, reflected + rec.p, r_in.time());
		}
		else {
			scattered = ray(rec.p, refracted + rec.p, r_in.time());
		}

		return true;
	}
};

#endif