#ifndef SCENES_
#define SCENES_

#include "hitable.h"

hitable *random_scene(vec3& eye, vec3& at, vec3& up);
hitable *cornell_box(vec3& eye, vec3& at, vec3& up);
hitable *iridescent_scene(vec3& eye, vec3& at, vec3& up);
hitable *simple_light(vec3& eye, vec3& at, vec3& up);
hitable *final(vec3& eye, vec3& at, vec3& up);

#endif