#ifndef _BOUNDINGVOLUMEHIERARCHY_YMKANG
#define _BOUNDINGVOLUMEHIERARCHY_YMKANG

#include "hitable.h"
#include "hitable_list.h"
#include "aabb.h"

int box_x_compare(const void *a, const void *b) {
	
	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);
	
	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().x > aabb2.min().x) ? 1 : -1;
}

int box_y_compare(const void *a, const void *b) {
	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);

	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().y > aabb2.min().y) ? 1 : -1;
}

int box_z_compare(const void *a, const void *b) {
	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);

	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().z > aabb2.min().z) ? 1 : -1;
}

class boundingHierarchy : public hitable {
public:

	hitable *left;
	hitable *right;
	aabb box;

	boundingHierarchy() {}
	boundingHierarchy(hitable **list, int n, float time0, float time1) {
		std::cout << "creating bounding volume hierarcy" << std::endl;
		
		
		int axis = int(3 * rand(0, 1));
		if (axis == 0) 
			qsort(list, n, sizeof(hitable *), box_x_compare);
		else if (axis == 1) 
			qsort(list, n, sizeof(hitable *), box_y_compare);
		else 
			qsort(list, n, sizeof(hitable *), box_z_compare);
			
		
		
		if (n == 1) {
			left = right = list[0];
		}
		else if (n == 2) {
			left = list[0];
			right = list[1];
		}
		else {
			left = new boundingHierarchy(list, n / 2, time0, time1);
			right = new boundingHierarchy(list + n / 2, n - n / 2, time0, time1);
		}
		aabb box_left, box_right;
		if (!left->boundingBox(time0, time1, box_left) || !right->boundingBox(time0, time1, box_right)) std::cerr << "no bounding box in the hierarchy\n";
		box = surroundingBox(box_left, box_right);	
	}


	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
		if (box.hit(r, t_min, t_max)) {
			hit_record left_rec, right_rec;
			bool hit_left  =  left->hit(r, t_min, t_max,  left_rec);
			bool hit_right = right->hit(r, t_min, t_max, right_rec);
			if (hit_left && hit_right) {
				rec = (left_rec.t < right_rec.t) ? left_rec : right_rec;
				return true;
			}
			else if (hit_left) {
				rec = left_rec; return true;
			}
			else if (hit_right) {
				rec = right_rec; return true;
			}
			return false;
		}
		return false;
	}

	virtual bool boundingBox(float t0, float t1, aabb& b) const {
		b = box;
		return true;
	}

};

#endif