
#include "movingSphere.h"
#include "aabb.h"


bool movingSphere::hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
	vec3 oc = r.source() - loc(r.time());
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b - a*c)) / a;
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - loc(r.time())) / radius;			
			rec.mat_ptr = this->mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp<tmax && temp>tmin) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - loc(r.time())) / radius;
			rec.mat_ptr = this->mat_ptr;
			return true;
		}
	}
	return false;
}

vec3 movingSphere::loc(float time) const {
	
	float t = (time - time0) / (time1 - time0);
	return (1.0 - t) * center + t * target;

};

bool movingSphere::boundingBox(float t0, float t1, aabb& box) const {
	aabb aabb1 = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
	aabb aabb2 = aabb(target - vec3(radius, radius, radius), target + vec3(radius, radius, radius));
	box = surroundingBox(aabb1, aabb2);
	return true;
}
