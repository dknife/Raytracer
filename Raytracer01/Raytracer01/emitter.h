#ifndef _EMITTER_YMKANG
#define _EMITTER_YMKANG

#include "material.h"
#include "vec3.h"
#include "simpleOperations.h"

class emitter : public material {
public:
	texture* lightColor;
	float amplification;

	
	emitter(texture* t, float amp=1.0) : lightColor(t), amplification(amp) {}
	emitter(const vec3& light, float amp=1.0) : lightColor(new constantTexture(light)), amplification(amp) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target, r_in.time());
		if (r_in.fromEye) attenuation = lightColor->value(rec.u, rec.v, rec.p);
		else attenuation = amplification*lightColor->value(rec.u, rec.v, rec.p);
		return false;
	}
};
#endif