#ifndef RAYH_YMKANG2017
#define RAYH_YMKANG2017

#include "vec3.h"

class ray {	
	vec3 A;
	vec3 B;
	float _time;
public:
	bool fromEye;

	ray();
	ray(const vec3& a, const vec3& b, float timeValue=0.0 );
	vec3 source() const;
	vec3 target() const;
	vec3 direction() const;
	vec3 point_at_parameter(float t) const;

	float time() const;
};
#endif