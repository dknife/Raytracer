#include "boundingHierarchy.h"

int compBoxX(const void *a, const void *b) {

	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);

	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().x > aabb2.min().x) ? 1 : -1;
}

int compBoxY(const void *a, const void *b) {
	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);

	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().y > aabb2.min().y) ? 1 : -1;
}

int compBoxZ(const void *a, const void *b) {
	aabb aabb1, aabb2;
	hitable * box1 = *((hitable **)a);
	hitable * box2 = *((hitable **)b);

	if (!box1->boundingBox(0, 0, aabb1) || !box2->boundingBox(0, 0, aabb2)) {
		std::cerr << "no bounding box in bvh nodes";
	}

	return (aabb1.min().z > aabb2.min().z) ? 1 : -1;
}

