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
	rec.normal = flipNormal ? vec3(0, 0, -1) : vec3(0, 0, 1);
	return true;
}

bool xz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.source().y) / r.direction().y;
	if (t<t0 || t>t1) return false;

	float x = r.source().x + t*r.direction().x;
	float z = r.source().z + t*r.direction().z;

	if (x<x0 || x>x1 || z<z0 || z>z1) return false;

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(rec.t);
	rec.normal = flipNormal ? vec3(0, -1, 0) : vec3(0, 1, 0);
	return true;
}

bool yz_rect::hit(const ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.source().x) / r.direction().x;
	if (t<t0 || t>t1) return false;

	float y = r.source().y + t*r.direction().y;
	float z = r.source().z + t*r.direction().z;

	if (y<y0 || y>y1 || z<z0 || z>z1) return false;

	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(rec.t);
	rec.normal = flipNormal?vec3(-1,0,0):vec3(1, 0, 0);
	return true;
}

