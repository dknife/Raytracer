#ifndef VEC3_YMKANG
#define VEC3_YMKANG

#include <iostream>
#include <math.h>

//! 3 dimensional vector class
//!
/*!
\brief Class for 3-D vectors

- vector operations: + (add) , - (sub), * (cross), ^ (dot)
- Copyright(c) Young-Min Kang */

class vec3 {
public:
	/*! vector elements */
	float x, y, z;

	//! Constructors
	vec3() { x = 0; y = 0; z = 0; }
	vec3(float a, float b, float c) { x = a; y = b; z = c; }


	//! Set Elements
	void set(float a, float b, float c);

	//! Get Elements
	void get(float &a, float &b, float &c);

	//! Bracket Operators for indexing the vector elements
	float operator[](int idx) const;

	//! Negate Operator
	vec3 operator-() const;

	//! Vector Addition
	/*! vectorA + vectorB returns the addition result*/
	vec3 operator+(const vec3& v) const;

	//! Vector Subtraction
	/*! vectorA - vectorB returns the subtraction result*/
	vec3 operator-(const vec3& v) const;

	//! Vector - Element-wise Multiplication
	/*! vectorA * vectorB returns (A.x*B.x, A.y*B.y, A.z*B.z) */
	vec3 operator*(const vec3& v) const;  


	//! Vector Length
	float	len(void) const;
	float   lenSquare(void) const;

	//! Vector Normalization
	/*! The vector itself is normalized, and there is no return values */
	void	normalize(void);

	//! Returns the normalized version of the vector
	/*! The vector itself is not normalized, and the length is preserved */
	vec3	getNormalized(void) const;

	void	show(void);
};


/*! cross and dot product functions
- usage: cross|dot product = cross|dot(vector1, vector2) */

vec3 cross(vec3 v1, vec3 v2);
float dot(vec3 v1, vec3 v2);

/*! * operators */
vec3 operator*(float s, vec3 v);
vec3 operator*(vec3 v, float s);
vec3 operator/(vec3 v, float s);


/*! stream in/out */
inline std::istream& operator>>(std::istream &is, vec3 &v);
inline std::ostream& operator<<(std::ostream &os, const vec3 &v);



#endif