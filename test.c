#include <stdio.h>
#include <assert.h>

#include "matrix.h"

void
test_vector_constructors(void) {
	const float a = 1.0;
	const float b = 2.0;
	const float c = 3.0;
	const float d = 4.0;

	/*
	 * Single value
	 */

	{
		vec2 v = vec2(a);
		assert(v.x == a && v.y == a);
	}

	{
		vec3 v = vec3(a);
		assert(v.x == a && v.y == a && v.z == a);
	}

	{
		vec4 v = vec4(a);
		assert(v.x == a && v.y == a && v.z == a && v.w == a);
	}

	/*
	 * All values
	 */

	{
		vec2 v = vec2(a, b);
		assert(v.x == a && v.y == b);
	}

	{
		vec3 v = vec3(a, b, c);
		assert(v.x == a && v.y == b && v.z == c);
	}

	{
		vec4 v = vec4(a, b, c, d);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}

	/*
	 * From other vectors
	 */


	// vec2 from vec3
	{
		vec3 u = vec3(a, b, c);
		vec2 v = vec2(u);
		assert(v.x == a && v.y == b);
	}

	// vec2 from vec4
	{
		vec4 u = vec4(a, b, c, d);
		vec2 v = vec2(u);
		assert(v.x == a && v.y == b);
	}


	// vec3 from vec2, float
	{
		vec2 u = vec2(a, b);
		vec3 v = vec3(u, c);
		assert(v.x == a && v.y == b && v.z == c);
	}

	// vec3 from float, vec2
	{
		vec2 u = vec2(b, c);
		vec3 v = vec3(a, u);
		assert(v.x == a && v.y == b && v.z == c);
	}

	// vec3 from vec4
	{
		vec4 u = vec4(a, b, c, d);
		vec3 v = vec3(u);
		assert(v.x == a && v.y == b && v.z == c);
	}


	// vec4 from vec3, float
	{
		vec3 u = vec3(a, b, c);
		vec4 v = vec4(u, d);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}

	// vec4 from float, vec3
	{
		vec3 u = vec3(b, c, d);
		vec4 v = vec4(a, u);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}

	// vec4 from vec2, vec2
	{
		vec2 u = vec2(a, b);
		vec2 w = vec2(c, d);
		vec4 v = vec4(u, w);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}

	// vec4 from vec2, float, float
	{
		vec2 u = vec2(a, b);
		vec4 v = vec4(u, c, d);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}

	// vec4 from float, float, vec2
	{
		vec2 u = vec2(c, d);
		vec4 v = vec4(a, b, u);
		assert(v.x == a && v.y == b && v.z == c && v.w == d);
	}
}

void
test_matrix_constructors(void) {
	const float _a = 2.0;
	const float _b = 3.0;
	const float _c = 5.0;
	const float _d = 7.0;
	const float _e = 11.0;
	const float _f = 13.0;
	const float _g = 17.0;
	const float _h = 19.0;
	const float _i = 23.0;
	const float _j = 29.0;
	const float _k = 31.0;
	const float _l = 37.0;
	const float _m = 41.0;
	const float _n = 43.0;
	const float _o = 47.0;
	const float _p = 53.0;

	/*
	 * Single value: diagonal constructor
	 */

	{
		mat2 m = mat2(_a);

		mat2 expected = mat2(
			vec2(_a, 0.0),
			vec2(0.0, _a)
		);

		assert(equals(expected, m));
	}

	{
		mat3 m = mat3(_a);

		mat3 expected = mat3(
			vec3(_a, 0.0, 0.0),
			vec3(0.0, _a, 0.0),
			vec3(0.0, 0.0, _a)
		);

		assert(equals(expected, m));
	}

	{
		mat4 m = mat4(_a);

		mat4 expected = mat4(
			vec4(_a, 0.0, 0.0, 0.0),
			vec4(0.0, _a, 0.0, 0.0),
			vec4(0.0, 0.0, _a, 0.0),
			vec4(0.0, 0.0, 0.0, _a)
		);

		assert(equals(expected, m));
	}

	/*
	 * From vectors
	 */

	{
		vec2 v1 = vec2(_a, _b);
		vec2 v2 = vec2(_c, _d);
		mat2 m = mat2(v1, v2);

		mat2 expected = mat2(
			_a, _b,
			_c, _d
		);

		assert(equals(expected, m));
	}

	{
		vec3 v1 = vec3(_a, _b, _c);
		vec3 v2 = vec3(_d, _e, _f);
		vec3 v3 = vec3(_g, _h, _i);
		mat3 m = mat3(v1, v2, v3);

		mat3 expected = mat3(
			_a, _b, _c,
			_d, _e, _f,
			_g, _h, _i
		);

		assert(equals(expected, m));
	}

	{
		vec4 v1 = vec4(_a, _b, _c, _d);
		vec4 v2 = vec4(_e, _f, _g, _h);
		vec4 v3 = vec4(_i, _j, _k, _l);
		vec4 v4 = vec4(_m, _n, _o, _p);
		mat4 m = mat4(v1, v2, v3, v4);

		mat4 expected = mat4(
			_a, _b, _c, _d,
			_e, _f, _g, _h,
			_i, _j, _k, _l,
			_m, _n, _o, _p
		);

		assert(equals(expected, m));
	}

	/*
	 * From other matrices
	 *
	 * Note: When a larger matrix is constructed from a smaller matrix, the cells should
	 *       be filled from the identity matrix.
	 */

	// mat3 from mat2
	{
		mat2 n = mat2(
			_a, _b,
			_c, _d
		);

		mat3 m = mat3(n);

		mat3 expected = mat3(
			_a, _b, 0,
			_c, _d, 0,
			0, 0, 1.0
		);

		assert(equals(expected, m));
	}

	// mat4 from mat2
	{
		mat2 n = mat2(
			_a, _b,
			_c, _d
		);

		mat4 m = mat4(n);

		mat4 expected = mat4(
			_a, _b, 0, 0,
			_c, _d, 0, 0,
			0, 0, 1.0, 0,
			0, 0, 0, 1.0
		);

		assert(equals(expected, m));
	}

	// mat4 from mat3
	{
		mat3 n = mat3(
			_a, _b, _c,
			_d, _e, _f,
			_g, _h, _i
		);

		mat4 m = mat4(n);

		mat4 expected = mat4(
			_a, _b, _c, 0,
			_d, _e, _f, 0,
			_g, _h, _i, 0,
			0, 0, 0, 1.0
		);

		assert(equals(expected, m));
	}

	/*
	 * Directly
	 */

	{
		mat2 m = mat2(
			_a, _b,
			_c, _d
		);

		assert(equals(m.cols[0], vec2(_a, _b)));
		assert(equals(m.cols[1], vec2(_c, _d)));
	}

	{
		mat3 m = mat3(
			_a, _b, _c,
			_d, _e, _f,
			_g, _h, _i
		);

		assert(equals(m.cols[0], vec3(_a, _b, _c)));
		assert(equals(m.cols[1], vec3(_d, _e, _f)));
		assert(equals(m.cols[2], vec3(_g, _h, _i)));
	}

	{
		mat4 m = mat4(
			_a, _b, _c, _d,
			_e, _f, _g, _h,
			_i, _j, _k, _l,
			_m, _n, _o, _p
		);

		assert(equals(m.cols[0], vec4(_a, _b, _c, _d)));
		assert(equals(m.cols[1], vec4(_e, _f, _g, _h)));
		assert(equals(m.cols[2], vec4(_i, _j, _k, _l)));
		assert(equals(m.cols[3], vec4(_m, _n, _o, _p)));
	}
}

void
test_matrix_mult(void) {
	const float _a = 2.0;
	const float _b = 3.0;
	const float _c = 5.0;
	const float _d = 7.0;
	const float _e = 11.0;
	const float _f = 13.0;
	const float _g = 17.0;
	const float _h = 19.0;
	const float _i = 23.0;
	const float _j = 29.0;
	const float _k = 31.0;
	const float _l = 37.0;
	const float _m = 41.0;
	const float _n = 43.0;
	const float _o = 47.0;
	const float _p = 53.0;
	const float _q = 59.0;
	const float _r = 61.0;

	{
		mat2 m = mat2(
			_a, _b,
			_c, _d
		);
		mat2 n = mat2(
			_e, _f,
			_g, _h
		);

		mat2 mt = transpose(m);
		mat2 r = mult(m, n);

		mat2 expected = mat2(
			vec2(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0])),
			vec2(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1]))
		);

		assert(equals(expected, r));
	}

	{
		mat3 m = mat3(
			_a, _b, _c,
			_d, _e, _f,
			_g, _h, _i
		);
		mat3 n = mat3(
			_j, _k, _l,
			_m, _n, _o,
			_p, _q, _r
		);

		mat3 mt = transpose(m);
		mat3 r = mult(m, n);

		mat3 expected = mat3(
			vec3(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0]), dot(mt.cols[2], n.cols[0])),
			vec3(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1]), dot(mt.cols[2], n.cols[1])),
			vec3(dot(mt.cols[0], n.cols[2]), dot(mt.cols[1], n.cols[2]), dot(mt.cols[2], n.cols[2]))
		);

		assert(equals(expected, r));
	}

	{
		mat4 m = mat4(
			_a, _b, _c, _d,
			_e, _f, _g, _h,
			_i, _j, _k, _l,
			_m, _n, _o, _p
		);
		mat4 n = mat4(
			_c, _d, _b, _a,
			_o, _p, _n, _m,
			_k, _l, _j, _i,
			_g, _h, _f, _e
		);

		mat4 mt = transpose(m);
		mat4 r = mult(m, n);

		mat4 expected = mat4(
			vec4(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0]), dot(mt.cols[2], n.cols[0]), dot(mt.cols[3], n.cols[0])),
			vec4(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1]), dot(mt.cols[2], n.cols[1]), dot(mt.cols[3], n.cols[1])),
			vec4(dot(mt.cols[0], n.cols[2]), dot(mt.cols[1], n.cols[2]), dot(mt.cols[2], n.cols[2]), dot(mt.cols[3], n.cols[2])),
			vec4(dot(mt.cols[0], n.cols[3]), dot(mt.cols[1], n.cols[3]), dot(mt.cols[2], n.cols[3]), dot(mt.cols[3], n.cols[3]))
		);

		assert(equals(expected, r));
	}

	/*
	 * Test identity works
	 */

	{
		mat2 m = mat2(
			_a, _b,
			_c, _d
		);

		assert(equals(mult(m, mat2(1.0)), m));
		assert(equals(mult(mat2(1.0), m), m));
	}

	{
		mat3 m = mat3(
			_a, _b, _c,
			_d, _e, _f,
			_g, _h, _i
		);

		assert(equals(mult(m, mat3(1.0)), m));
		assert(equals(mult(mat3(1.0), m), m));
	}

	{
		mat4 m = mat4(
			_a, _b, _c, _d,
			_e, _f, _g, _h,
			_i, _j, _k, _l,
			_m, _n, _o, _p
		);

		assert(equals(mult(m, mat4(1.0)), m));
		assert(equals(mult(mat4(1.0), m), m));
	}
}

void
test_dot_product(void) {
	const float a = 2.0;
	const float b = 3.0;
	const float c = 5.0;
	const float d = 7.0;
	const float e = 11.0;
	const float f = 13.0;
	const float g = 17.0;
	const float h = 23.0;

	{
		vec2 v1 = vec2(a, b);
		vec2 v2 = vec2(c, d);

		float result1 = dot(v1, v2);
		float result2 = dot(v2, v1);

		assert(result1 == result2);
		assert(result1 == a * c + b * d);
	}

	{
		vec3 v1 = vec3(a, b, c);
		vec3 v2 = vec3(d, e, f);

		float result1 = dot(v1, v2);
		float result2 = dot(v2, v1);

		assert(result1 == result2);
		assert(result1 == a * d + b * e + c * f);
	}

	{
		vec4 v1 = vec4(a, b, c, d);
		vec4 v2 = vec4(e, f, g, h);

		float result1 = dot(v1, v2);
		float result2 = dot(v2, v1);

		assert(result1 == result2);
		assert(result1 == a * e + b * f + c * g + d * h);
	}
}

int
main(int argc, char **argv) {
	test_vector_constructors();
	test_matrix_constructors();
	test_matrix_mult();
	test_dot_product();
}

