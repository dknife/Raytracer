#ifndef _AABB_YMKANG_
#define _AABB_YMKANG_

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


aabb surroundingBox(aabb box0, aabb box1);

#endif