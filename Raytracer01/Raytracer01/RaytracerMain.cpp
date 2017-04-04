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
#include "emitter.h"
#include "constantTexture.h"
#include "checkerTexture.h"
#include "noiseTexture.h"
#include "marbleTexture.h"
#include "rect.h"
#include "imageTexture.h"
#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

#define ScatterDepthLImit 50
float startTime = 0.0;
float endTime = 1.0;

/*
hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];

	texture *checker = new checkerTexture(new constantTexture(vec3(0.2, 0.3, 0.1)), new constantTexture(vec3(0.9, 0.9, 0.9)), 10.0);
	list[0] = new sphere(vec3(0, -500.0, 0), 500, new lambertian(checker));
	int i = 1;
	for (int a = -5; a < 5; a++) {
		for (int b = -5; b < 5; b++) {
			float choose_mat = rand(0, 1);
			vec3 center(a + 0.9*rand(0, 1), 0.2, b + 0.9*rand(0, 1));
			if ((center - vec3(4.0, 0.2, 0.0)).len() > 0.9) {
				if (choose_mat < 0.05) {
					list[i++] = new sphere(center, 0.2,
						new lambertian(vec3(rand(0, 1), rand(0, 1), rand(0, 1)))
						);
				}
				else if (choose_mat < 0.5) {
					list[i++] = new sphere(center, 0.2, new metal(vec3(rand(0, 1), rand(0, 1), rand(0, 1)), 0.05));
				}
				else {
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(2.5));
	list[i++] = new sphere(vec3(0, 1, 0), -0.98, new dielectric(2.5));

	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new metal(vec3(1, 1, 0),0.1));	
	list[i++] = new sphere(vec3(3, 0.5, 0), 0.5, new emitter(vec3(1,1,1)));

	return new hitable_list(list, i);
}
*/

hitable *simple_light() {
	
	hitable **list = new hitable*[4];
	int nx, ny, nn;
	unsigned char *image = stbi_load("texture.jpg", &nx, &ny, &nn, 0);
	
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(new marbleTexture(vec3(1.0,0.0,0.0), 2.0)));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(new noiseTexture(vec3(1.0, 1.0, 0.5), 2.0)));
	list[2] = new xy_rect(-3, 3, 0, 6, -4, new lambertian(new imageTexture(image, nx, ny)));
	list[3] = new sphere(vec3(6, 2, 3), 4, new lambertian(new marbleTexture(vec3(1.0, 0.0, 0.0), 2.0)));
		
	return new hitable_list(list, 4);
}

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	vec3 ambientColor(0.7, 0.7, 1.0);
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation(0, 0, 0);
		if (depth < ScatterDepthLImit && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return attenuation;
		}		
	}
	else {
		return ambientColor;
		/*
		vec3 unit_direction = r.direction().getNormalized();
		float t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t)*vec3(1.0,1.0,1.0) + t*ambientColor;
		*/
	}
}

int main() {

	ofstream imageFile;
	imageFile.open("image.ppm");
	int nx = 600;
	int ny = 400;
	int nsample = 500;
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-3.0, -2.0, -1.0);
	vec3 horizontal(6.0, 0.0, 0.0);
	vec3 vertical(0.0, 4.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	
	hitable *world = simple_light();


	vec3 eye(-8.5, 6.3, 8.5);
	vec3 at(0, 0, 0);
	vec3 up(0, 1, 0);
	float aperture = 0.0;
	float focus_distance = (at-eye).len();
	float gamma=1.5;
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
			float lenSqr = col.lenSquare();
			if (lenSqr>1.0) {
				float total = 1.0 + lenSqr;
				float t = lenSqr / total;
				col = col.getNormalized()*(1-t) + vec3(1, 1, 1)*t;
			}

			float r = pow(col[0], 1.0/gamma);
			float g = pow(col[1], 1.0 / gamma);
			float b = pow(col[2], 1.0 / gamma);
			//r = r > 1.0 ? 1.0 : r;
			//g = g > 1.0 ? 1.0 : g;
			//b = b > 1.0 ? 1.0 : b;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);

			imageFile << ir << " " << ig << " " << ib << "\n";			
			percentage++;
		}
		int progress = 100.0*(percentage / float(nx*ny));
		cout << progress << "% done" << endl;
	}

	imageFile.close();


	return 1;
}