#include "hitable.h"
#include "hitable_list.h"

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;

	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

bool hitable_list::boundingBox(float t0, float t1, aabb& box) const {
	if (list_size < 1) return false;

	aabb tempbox;
	bool first_true = list[0]->boundingBox(t0, t1, tempbox);
	if (!first_true) return false;
	else box = tempbox;

	for (int i = 1; i < list_size; i++) {
		if (list[i]->boundingBox(t0, t1, tempbox)) {
			box = surroundingBox(box, tempbox);
		}
		else return false;
	}
	return true;
}
