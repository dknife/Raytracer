#ifndef CAMERA_YMKANG_2017
#define CAMERA_YMKANG_2017

#include "ray.h"
#include "vec3.h"

class camera {
public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
	vec3 u, v, w;
	float time0;
	float time1;

	camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float aperture, float focus_distance, float t0, float t1);
	ray get_ray(float s, float t);
};

#endif