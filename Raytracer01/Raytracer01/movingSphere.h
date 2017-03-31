#ifndef MOVING_SPHERE_YMKANG_2017
#define MOVING_SPHERE_YMKANG_2017

#include "sphere.h"

class movingSphere : public sphere {
public:
	float time0, time1;
	vec3 target;

	movingSphere() {}
	movingSphere(vec3 cen0, vec3 cen1, float t0, float t1, float r, material *m) : sphere(cen0, r, m), target(cen1), time0(t0), time1(t1) { };

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 loc(float time) const;

};
#endif