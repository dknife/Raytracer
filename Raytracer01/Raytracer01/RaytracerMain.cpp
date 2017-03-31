#include <iostream>
#include <fstream>

#include "ray.h"
#include "vec3.h"
#include "hitable_list.h"
#include "sphere.h"
#include "simpleOperations.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "camera.h"
#include "movingSphere.h"

#include <float.h>


using namespace std;

#define ScatterDepthLImit 50
float startTime = 0.0;
float endTime = 1.0;

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000.0, 0), 1000, new metal(vec3(0.5, 0.5, 0.5), 0.15));
	int i = 1;
	for (int a = -5; a < 5; a++) {
		for (int b = -5; b < 5; b++) {
			float choose_mat = rand(0, 1);
			vec3 center(a + 0.9*rand(0, 1), 0.2, b + 0.9*rand(0, 1));
			if ((center - vec3(4.0, 0.2, 0.0)).len() > 0.9) {
				if (choose_mat < 0.33) {
					list[i++] = new movingSphere(center, center + vec3(rand(-0.1, 0.1), 0.0, rand(-0.1, 0.1)), startTime, endTime, 0.2, new lambertian(vec3(rand(0, 1), rand(0, 1), rand(0, 1))));
				}
				else if (choose_mat < 0.66) {
					list[i++] = new sphere(center, 0.2, new metal(vec3(rand(0, 1), rand(0, 1), rand(0, 1)), rand(0.15, 0.5)));				}
				else {
					list[i++] = new movingSphere(center, center + vec3(rand(-0.1, 0.1), 0.0, rand(-0.1, 0.1)), startTime, endTime, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(2.5));
	list[i++] = new sphere(vec3(0, 1, 0), -0.98, new dielectric(2.5));

	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(1, 1, 1)));	
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(1,1,0), 0.2));

	return new hitable_list(list, i);
}

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	vec3 ambientColor(0.5, 0.5, 1.0);
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < ScatterDepthLImit && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return ambientColor;
		}		
	}
	else {
		vec3 unit_direction = r.direction().getNormalized();
		float t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main() {

	ofstream imageFile;
	imageFile.open("image.ppm");
	int nx = 200;
	int ny = 200;
	int nsample = 100;
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-3.0, -2.0, -1.0);
	vec3 horizontal(6.0, 0.0, 0.0);
	vec3 vertical(0.0, 4.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hitable *world = random_scene();


	vec3 eye(5, 1.3, -2);
	vec3 at(0, 0, 0);
	vec3 up(0, 1, 0);
	float aperture = 0.0;
	float focus_distance = (at-eye).len();
	camera cam(eye,at,up, 45, float(nx) / float(ny), aperture, focus_distance, startTime, endTime);
	int percentage = 1;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			

			vec3 col(0, 0, 0);
			for (int s = 0; s < nsample; s++) {
				float u = float(i + rand(0.0,1.0)) / float(nx);
				float v = float(j + rand(0.0,1.0)) / float(ny);
				ray r = cam.get_ray(u, v);
				col = col + color(r, world, 0);
			}
			col = col / nsample;
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			imageFile << ir << " " << ig << " " << ib << "\n";			
			percentage++;
		}
		int progress = 100.0*(percentage / float(nx*ny));
		cout << progress << "% done" << endl;
	}

	imageFile.close();


	return 1;
}