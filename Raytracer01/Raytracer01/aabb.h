#ifndef _AABB_YMKANG
#define _AABB_YMKANG

#include "vec3.h"
#include "ray.h"

class aabb {
public:
	vec3 _min;
	vec3 _max;

	aabb() {}
	aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }
	vec3 min() const { return _min; }
	vec3 max() const { return _max; }
	bool hit(const ray& r, float tmin, float tmax) const {
		for (int dim = 0; dim < 3; dim++) {
			float invD = 1.0 / r.direction()[dim];
			float t0 = (min()[dim] - r.source()[dim])*invD;
			float t1 = (max()[dim] - r.source()[dim])*invD;
			if (invD < 0.0) std::swap(t0, t1);
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;

			if (tmax <= tmin) return false;
		}
		return true;
	}
};

aabb surroundingBox(aabb box0, aabb box1) {
	vec3 small(fmin(box0.min().x, box1.min().x), fmin(box0.min().y, box1.min().y), fmin(box0.min().z, box1.min().z));
	vec3 big(fmax(box0.max().x, box1.max().x), fmax(box0.max().y, box1.max().y), fmax(box0.max().z, box1.max().z));
	return aabb(small, big);
}
#endif