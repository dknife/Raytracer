#ifndef HITABLELIST_YMKANG_2017
#define HITABLELIST_YMKANG_2017

#include "hitable.h"

class hitable_list : public hitable {
public:
	hitable **list;
	int list_size;

	hitable_list() {}
	hitable_list(hitable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool boundingBox(float t0, float t1, aabb& box) const;
};

#endif