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
#include "checkerTextureUV.h"
#include "noiseTexture.h"
#include "marbleTexture.h"
#include "rect.h"
#include "imageTexture.h"
#include "dielectricSpectral.h"
#include "dielectric.h"
#include "iridescent.h"
#include "box.h"
#include "boundingHierarchy.h"

#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

#define ScatterDepthLImit 50
float startTime = 0.0;
float endTime = 1.0;


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

	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new metal(vec3(1, 1, 0), 0.1));
	list[i++] = new sphere(vec3(3, 0.5, 0), 0.5, new emitter(vec3(1, 1, 1)));

	return new hitable_list(list, i);
}

hitable *cornell_box() {
	hitable **list = new hitable*[20];

	int i = 0;

	material *red = new lambertian(vec3(0.65, 0.05, 0.05));
	material *redChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.65, 0.05, 0.05)), 50.0));
	material *white = new lambertian(vec3(0.73, 0.73, 0.73));
	material *checker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0, 0, 0)), 50.0));
	material *green = new lambertian(vec3(0.12, 0.45, 0.15));
	material *greenChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.12, 0.45, 0.15)), 50.0));

	material *light = new emitter(vec3(15, 15, 15));

	list[i++] = new yz_rect(0, 555, 0, 555, 555, greenChecker); ((yz_rect*)list[i - 1])->flip();
	list[i++] = new yz_rect(0, 555, 0, 555, 0, redChecker);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light); // original light
	list[i++] = new xz_rect(50, 100, 227, 332, 554, light);
	list[i++] = new xz_rect(450, 505, 227, 332, 554, light);
	list[i++] = new xz_rect(0, 555, 0, 555, 555, white); ((xz_rect*)list[i - 1])->flip();
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new xy_rect(0, 555, 0, 555, 555, checker); ((xy_rect*)list[i - 1])->flip();
	list[i++] = new sphere(vec3(300, 250, 150), 80, new dielectricSpectral(1.5));
	list[i++] = new sphere(vec3(400, 80, 150), 80, new dielectricSpectral(1.5));
	list[i++] = new sphere(vec3(200, 80, 150), 80, new lambertian(vec3(1.0, 1.0, 1.0)));
	//list[i++] = new sphere(vec3(6, 2, 3), 4, new lambertian(new marbleTexture(vec3(1.0, 1.0, 1.0), 2.0)));

	return new hitable_list(list, i);
}

hitable *iridescent_scene() {
	hitable **list = new hitable*[20];

	int i = 0;

	material *red = new lambertian(vec3(0.65, 0.05, 0.05));
	material *redChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.65, 0.05, 0.05)), 50.0));
	material *white = new lambertian(vec3(0.73, 0.73, 0.73));
	material *checker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0, 0, 0)), 50.0));
	material *green = new lambertian(vec3(0.12, 0.45, 0.15));
	material *greenChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.12, 0.45, 0.15)), 50.0));
	material *iri = new iridescent(vec3(0.8, 0.8, 1.0), 0.2);
	material *dielecSpect = new dielectricSpectral(1.5);
	material *dielec = new dielectric(1.5);
	material *light = new emitter(vec3(15, 15, 15));

	list[i++] = new yz_rect(0, 555, 0, 555, 555, white); ((yz_rect*)list[i - 1])->flip();
	list[i++] = new yz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light); // original light
	list[i++] = new xz_rect(50, 100, 227, 332, 554, light);
	list[i++] = new xz_rect(450, 505, 227, 332, 554, light);
	list[i++] = new xz_rect(0, 555, 0, 555, 555, white); ((xz_rect*)list[i - 1])->flip();
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new xy_rect(0, 555, 0, 555, 555, white); ((xy_rect*)list[i - 1])->flip();
	//list[i++] = new xy_rect(0, 555, 0, 555, 0, white);
	list[i++] = new sphere(vec3(150, 112, 150), 115, dielecSpect);
	list[i++] = new sphere(vec3(150, 112, 150), 110, iri);
	list[i++] = new sphere(vec3(406, 112, 150), 115, dielec);
	list[i++] = new sphere(vec3(405, 112, 150), 110, iri);
	// 

	return new hitable_list(list, i);
}

hitable *simple_light() {

	hitable **list = new hitable*[100];
	int nx, ny, nn;
	unsigned char *image = stbi_load("jtbc.jpg", &nx, &ny, &nn, 0);
	int i = 0;

	list[i++] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(new checkerTexture(new constantTexture(vec3(1, 1, 1)), new marbleTexture(), 10.0)));
	list[i++] = new sphere(vec3(0, 2, 0), 2, new lambertian(new marbleTexture(vec3(1.0, 0.5, 1.0), 2.0)));
	list[i++] = new xy_rect(-3, 3, 0.5, 4.5, -4, new emitter(new imageTexture(image, nx, ny), 15.0));
	list[i++] = new xy_rect(-4, 4, 0, 5, -4.05, new lambertian(new noiseTexture(vec3(0.4, 0.4, 0.4), 2.0)));
	list[i++] = new sphere(vec3(6, 2, 3), 4, new lambertian(new marbleTexture(vec3(1.0, 1.0, 1.0), 2.0)));
	list[i++] = new sphere(vec3(-5, 2.5, 5), 2.5, new dielectric(1.25));
	int NLIGHTS = 10;
	for (int j = 0; j < NLIGHTS; j++) {
		float angle = j*3.14159*2.0 / float(NLIGHTS);
		float x = 10.0* cos(angle);
		float y = 10.0*sin(angle);
		list[i++] = new sphere(vec3(x, 0.5, y), 0.5, new emitter(vec3(rand(0.7, 1.0), rand(0.7, 1.0), rand(0.2, 0.4)), 20.0));
	}

	return new hitable_list(list, i);
}


hitable *final() {
	int nb = 20;
	hitable **list = new hitable*[30];
	hitable **boxlist  = new hitable*[10000];
	hitable **boxlist2 = new hitable*[10000];

	material *white = new lambertian(new constantTexture(vec3(0.73, 0.73, 0.73)));
	material *ground = new lambertian(new constantTexture(vec3(0.48, 0.83, 0.53)));
	material *red = new lambertian(vec3(0.65, 0.05, 0.05));
	material *redChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.65, 0.05, 0.05)), 50.0));
	material *checker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0, 0, 0)), 50.0));
	material *green = new lambertian(vec3(0.12, 0.45, 0.15));
	material *greenChecker = new lambertian(new checkerTextureUV(new constantTexture(vec3(1, 1, 1)), new constantTexture(vec3(0.12, 0.45, 0.15)), 50.0));
	material *iri = new iridescent(vec3(0.8, 0.8, 1.0), 0.5);
	material *dielecSpect = new dielectricSpectral(1.5);
	material *dielec = new dielectric(1.5);
	material *gold = new metal(vec3(1, 1, 0.6), 0.3);
	
	int b = 0;
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < nb; j++) {
			float w = 2000 / nb;;
			float x0 = -1000 + i*w;
			float z0 = -1000 + j*w;
			float y0 = 0;
			float x1 = x0 + w;
			float z1 = z0 + w;
			float y1 = 100*rand(0.01, 1.0);
			boxlist[b++] = new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
		}
	}

	int l = 0;
	list[l++] = new boundingHierarchy(boxlist, b, 0, 1);
	material *light = new emitter(vec3(17, 17, 17));

	list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
	list[l++] = new xz_rect(-300, 0, 147, 412, 554, light);
	list[l++] = new xz_rect(123, 423, -412, -147, 554, light);
	list[l++] = new xz_rect(-300, 0, -412, -147, 554, light);
	vec3 center(400, 300, 200);
	list[l++] = new movingSphere(center, center + vec3(30, 0, 0), 0, 1, 150, new lambertian(vec3(0.7, 0.3, 0.1)));

	list[l++] = new sphere(vec3(600, 200, -500), 124, dielec);
	list[l++] = new sphere(vec3(600, 200, -500), 120, green);
	list[l++] = new sphere(vec3(350, 200, -505), 120, gold);

	list[l++] = new sphere(vec3(0, 200, -1000), 110, dielecSpect);
	list[l++] = new sphere(vec3(0, 200, -1000), 100, iri);
	
	list[l++] = new sphere(vec3(150, 200, -605), 124, dielecSpect);

	list[l++] = new sphere(vec3(-400, 200, -300), 124, dielec);

	list[l++] = new sphere(vec3(-423, 300, 100), 250, new lambertian(new noiseTexture(vec3(1.0, 1.0, 1.0), 1/50.0)));
	
	

	return new hitable_list(list, l);
}

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	vec3 ambientColor(0.2,0.2,0.2);
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
	int nsample = 15000;
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-3.0, -2.0, -1.0);
	vec3 horizontal(6.0, 0.0, 0.0);
	vec3 vertical(0.0, 4.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hitable *world = final();


	//vec3 eye(-13.5, 11.3, 13.5);
	//vec3 at(0, 0, 0);
	//vec3 up(0, 1, 0);

	//for Cornell box
	// vec3 eye(278, 278, -800);
	//vec3 at(278, 278, 0);
	//vec3 up(0, 1, 0);

	vec3 eye(500, 500, -1500);
	vec3 at(0, 0, 0);
	vec3 up(0, 1, 0);
	float aperture = 0.0;
	float focus_distance = 10; // (at - eye).len();
	float gamma = 1.5;
	camera cam(eye, at, up, 40, float(nx) / float(ny), aperture, focus_distance, startTime, endTime);
	int percentage = 1;

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {


			vec3 col(0, 0, 0);
			for (int s = 0; s < nsample; s++) {
				float u = float(i + rand(0.0, 1.0)) / float(nx);
				float v = float(j + rand(0.0, 1.0)) / float(ny);
				ray r = cam.get_ray(u, v);
				r.fromEye = true;
				col = col + color(r, world, 0);
			}
			col = col / nsample;
			col.x = col.x>1.0 ? 1.0 : col.x;
			col.y = col.y>1.0 ? 1.0 : col.y;
			col.z = col.z>1.0 ? 1.0 : col.z;

			float r = pow(col[0], 1.0f / gamma);
			float g = pow(col[1], 1.0f / gamma);
			float b = pow(col[2], 1.0f / gamma);

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