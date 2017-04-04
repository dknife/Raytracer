#include "rect.h"
#include "hitable.h"

bool xy_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.source().z) / r.direction().z;
	if (t<t0 || t>t1) return false;

	float x = r.source().x + t*r.direction().x;
	float y = r.source().y + t*r.direction().y;

	if (x<x0 || x>x1 || y<y0 || y>y1) return false;

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(rec.t);
	rec.normal = vec3(0, 0, 1);
	return true;
}