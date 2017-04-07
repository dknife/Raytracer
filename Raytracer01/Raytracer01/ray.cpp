#include "ray.h"

ray::ray() : fromEye(false) {
	A.set(0, 0, 0);
	B.set(0, 0, -1);
}

ray::ray(const vec3& a, const vec3& b, float timeValue) : fromEye(false) {
	A = a;
	B = b;
	_time = timeValue;
}

vec3 ray::source() const {
	return A;
}

vec3 ray::target() const {
	return B;
}
vec3 ray::direction() const {
	return B-A;
}

vec3 ray::point_at_parameter(float t) const {
	return A + (t*(B-A));
};

float ray::time() const {
	return _time;
}