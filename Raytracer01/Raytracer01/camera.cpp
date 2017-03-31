#include "camera.h"
#include <math.h>
#include "simpleOperations.h"
#define M_PI       3.14159265358979323846

camera::camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float aperture, float focus_d, float t0, float t1) {
	
	time0 = t0;
	time1 = t1;

	lens_radius = aperture / 2.0;
	float theta = fov*M_PI / 180.0;
	float half_height = tan(theta / 2.0);
	float half_width = aspect * half_height;
	origin = eye;
	w = (eye - at).getNormalized();
	u = cross(up, w).getNormalized();
	v = cross(w, u);
	lower_left_corner = vec3(-half_width, -half_height, -1.0);
	lower_left_corner = origin - half_width*focus_d*u - half_height*focus_d*v - focus_d*w;
	horizontal = 2.0*half_width*focus_d*u;
	vertical = 2.0*half_height*focus_d*v;
}

ray camera::get_ray(float s, float t) {
	vec3 rd = (lens_radius>0.0)?lens_radius*random_in_unit_disk():vec3(0,0,0);
	vec3 offset = u * rd.x + v*rd.y;
	float time = rand(time0, time1);
	return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical, time);
}
