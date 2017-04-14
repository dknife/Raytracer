#ifndef _FLIPNORMAL_YMKANG
#define _FLIPNORMAL_YMKANG
#include "hitable.h"

class flipNormal : public hitable {
public:
	hitable *hitableObj;

	flipNormal(hitable* p) : hitableObj(p) {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
		if (hitableObj->hit(r, t_min, t_max, rec)) {
			rec.normal = -rec.normal;
			return true;
		}
		else return false;
	}

	virtual bool boundingBox(float t0, float t1, aabb& box) const {
		return hitableObj->boundingBox(t0, t1, box);		
	}
};

#endif