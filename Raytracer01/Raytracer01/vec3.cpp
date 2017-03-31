#include "vec3.h"

/*! Sets the vector elements */
void vec3::set(float a, float b, float c)		{ x = a; y = b; z = c; }

/*! Stores the vector elements into the given parameters */
void vec3::get(float &a, float &b, float &c)	{ a = x; b = y; c = z; }

/*! Negate Operator
*/
vec3 vec3::operator-() const {
	return vec3(-x,-y,-z);
}

/*! Vector Addition
- Return: vec3 */
vec3 vec3::operator+(const vec3& v) const {
	return vec3(x + v[0], y + v[1], z + v[2]);
}

/*! Vector Subtraction
- Return: vec3 */
vec3 vec3::operator-(const vec3& v) const {
	return vec3(x - v[0], y - v[1], z - v[2]);
}


/*! Element-wise Multiplication
 Return: vec3 */
vec3 vec3::operator*(const vec3& v) const { 
	return vec3(x*v[0], y*v[1], z*v[2]);
}



/*! [] Operator for indexing x, y, and z */
float vec3::operator[](int idx) const {
	switch (idx) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: return 0;
	}
}

/*! Length: returns the length of the vector */
float	vec3::len(void) const { return sqrt(x*x + y*y + z*z); }

float	vec3::lenSquare(void) const { return x*x + y*y + z*z; }

void	vec3::normalize(void) {
	float l = len();
	if (l == 0.0f) { x = y = z = 0.0f; return; }
	x /= l; y /= l; z /= l;
}

/*! Returns a new normalized vector with the same direction */
vec3	vec3::getNormalized(void) const {
	float l = len();	if (len() == 0) return vec3(0, 0, 0);
	return vec3(x / l, y / l, z / l);
}


void	vec3::show(void) {
	std::cout << x << " " << y << " " << z << std::endl;
}
///////////////////////////////////////////////

/*! functions and operators for vec3 */

vec3 cross(vec3 v1, vec3 v) {
	return vec3(v1.y*v[2] - v1.z*v[1], -v1.x*v[2] + v1.z*v[0], v1.x*v[1] - v1.y*v[0]);
}

float dot(vec3 v1, vec3 v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


//vec3 operator+(vec3 v1, vec3 v2) {
//	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
//}

//vec3 operator-(vec3 v1, vec3 v2) {
//	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
//}

vec3 operator*(float s, vec3 v) {
	return vec3(s*v[0], s*v[1], s*v[2]);
}

vec3 operator*(vec3 v, float s) {
	return vec3(s*v[0], s*v[1], s*v[2]);
}

vec3 operator/(vec3 v, float s) {
	return vec3(v[0]/s, v[1]/s, v[2]/s);
}


inline std::istream& operator>>(std::istream &is, vec3 &v) {
	is >> v.x >> v.y >> v.z;
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &v) {
	os << v.x << " " << v.y << " " << v.z;
	return os;
}
