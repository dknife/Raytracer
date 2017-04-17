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


#include "scenes.h"

#include <float.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

#define ScatterDepthLImit 50
float startTime = 0.0;
float endTime = 1.0;




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
	int nsample = 150;
	imageFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-3.0, -2.0, -1.0);
	vec3 horizontal(6.0, 0.0, 0.0);
	vec3 vertical(0.0, 4.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);


	vec3 eye;
	vec3 at;
	vec3 up;
	hitable *world = cornell_box(eye, at, up);

	

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