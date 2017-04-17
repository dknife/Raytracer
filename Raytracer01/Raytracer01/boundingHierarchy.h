#ifndef _BOUNDINGVOLUMEHIERARCHY_YMKANG
#define _BOUNDINGVOLUMEHIERARCHY_YMKANG

#include "simpleOperations.h"
#include "hitable.h"
#include "hitable_list.h"
#include "aabb.h"

int compBoxX(const void *a, const void *b);
int compBoxY(const void *a, const void *b);
int compBoxZ(const void *a, const void *b);

class boundingHierarchy : public hitable {
public:

	hitable *left;
	hitable *right;
	aabb box;

	boundingHierarchy() {}
	boundingHierarchy(hitable **list, int n, float time0, float time1) {
		std::cout << "creating bounding volume hierarcy" << std::endl;
		
		
		int axis = int(3 * rand(0.0, 1.0));
		if (axis == 0) 
			qsort(list, n, sizeof(hitable *), compBoxX);
		else if (axis == 1) 
			qsort(list, n, sizeof(hitable *), compBoxY);
		else 
			qsort(list, n, sizeof(hitable *), compBoxZ);
			
		
		
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