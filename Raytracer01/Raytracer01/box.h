#ifndef BOX_YMKANG
#define BOX_YMKANG

#include "hitable.h"
#include "hitable_list.h"
#include "rect.h"
#include "flipNormal.h"

class box : public hitable {
public:
	hitable *planeList;
	vec3 pmin, pmax;

	box() : planeList(NULL) {}
	box(const vec3& minPoint, const vec3& maxPoint, material *mPtr) {
		pmin = minPoint;
		pmax = maxPoint;
		hitable **list = new hitable*[6];
		list[0] = new xy_rect(pmin.x, pmax.x, pmin.y, pmax.y, pmax.z, mPtr);
		list[1] = new flipNormal(new xy_rect(pmin.x, pmax.x, pmin.y, pmax.y, pmin.z, mPtr));
		list[2] = new xz_rect(pmin.x, pmax.x, pmin.z, pmax.z, pmax.y, mPtr);
		list[3] = new flipNormal(new xz_rect(pmin.x, pmax.x, pmin.z, pmax.z, pmin.y, mPtr));
		list[4] = new yz_rect(pmin.y, pmax.y, pmin.z, pmax.z, pmax.x, mPtr);
		list[5] = new flipNormal(new yz_rect(pmin.y, pmax.y, pmin.z, pmax.z, pmin.x, mPtr));
		planeList = new hitable_list(list, 6);
	}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
		return planeList ? planeList->hit(r, t_min, t_max, rec) : false;
	}
};

#endif