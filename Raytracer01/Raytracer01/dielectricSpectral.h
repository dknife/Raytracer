#ifndef DIELECTRICSPECTRAL_YMKANG_2017
#define DIELECTRICSPECTRAL_YMKANG_2017

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class dielectricSpectral : public material {
public:
	float ref_idx;

	dielectricSpectral(float ri) : ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		
		attenuation = vec3(1.0, 1.0, 1.0);
		float r_idx;

		vec3 refracted;
		float cosine;
		float reflect_prob;

		float rValue = rand(0, 1);
		if (rValue<0.33) { // r path
			r_idx = ref_idx*0.9;
			attenuation = vec3(2.0, 0.5, 0.5);
		}
		else if (rValue<0.66) { // g path
			r_idx = ref_idx;
			attenuation = vec3(0.5, 2.0, 0.5);
		}
		else { // b path
			r_idx = ref_idx*1.1;
			attenuation = vec3(0.5, 0.5, 2.0);
		}

		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = r_idx;
			cosine = r_idx * dot(r_in.direction(), rec.normal) / r_in.direction().len();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / r_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().len();
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, r_idx);
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