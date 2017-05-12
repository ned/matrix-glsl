#include <tgmath.h>

#include "matrix.h"

// FIXME: should use SSE/instrinsics for vector calculations


/*
 * Single-argument vector constructors
 */

vec2
vec2f1(float x) {
	return (vec2) {{ x, x }};
}

vec3
vec3f1(float x) {
	return (vec3) {{ x, x, x }};
}

vec4
vec4f1(float x) {
	return (vec4) {{ x, x, x, x }};
}

/*
 * Complete vector constructors
 */

vec2
vec2f2(float x, float y) {
	return (vec2) {{ x, y }};
}

vec3
vec3f3(float x, float y, float z) {
	return (vec3) {{ x, y, z }};
}

vec4
vec4f4(float x, float y, float z, float w) {
	return (vec4) {{ x, y, z, w }};
}

/*
 * Constructor from other vectors
 */

vec2
vec2v3(vec3 v) {
	return (vec2) {{ v.x, v.y }};
}

vec2
vec2v4(vec4 v) {
	return (vec2) {{ v.x, v.y }};
}


vec3
vec3v2f1(vec2 v, float z) {
	return (vec3) {{ v.x, v.y, z }};
}

vec3
vec3f1v2(float x, vec2 v) {
	return (vec3) {{ x, v.x, v.y }};
}

vec3
vec3v4(vec4 v) {
	return (vec3) {{ v.x, v.y, v.z }};
}


vec4
vec4v3f1(vec3 v, float w) {
	return (vec4) {{ v.x, v.y, v.z, w }};
}

vec4
vec4f1v3(float x, vec3 v) {
	return (vec4) {{ x, v.x, v.y, v.z }};
}

vec4
vec4v2v2(vec2 a, vec2 b) {
	return (vec4) {{ a.x, a.y, b.x, b.y }};
}

vec4
vec4v2f2(vec2 v, float z, float w) {
	return (vec4) {{ v.x, v.y, z, w }};
}

vec4
vec4f2v2(float x, float y, vec2 v) {
	return (vec4) {{ x, y, v.x, v.y }};
}

/*
 * Single argument matrix constructors
 */

mat2
mat2f1(float x) {
	return (mat2) {{
		vec2(x, 0.0f),
		vec2(0.0f, x),
	}};
}

mat3
mat3f1(float x) {
	return (mat3) {{
		vec3(x, 0.0f, 0.0f),
		vec3(0.0f, x, 0.0f),
		vec3(0.0f, 0.0f, x),
	}};
}

mat4
mat4f1(float x) {
	return (mat4) {{
		vec4(x, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, x, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, x, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, x),
	}};
}

/*
 * From vectors
 */

mat2
mat2v2(vec2 a, vec2 b) {
	return (mat2) {{ a, b }};
}

mat3
mat3v3(vec3 a, vec3 b, vec3 c) {
	return (mat3) {{ a, b, c }};
}

mat4
mat4v4(vec4 a, vec4 b, vec4 c, vec4 d) {
	return (mat4) {{ a, b, c, d }};
}

/*
 * From other matrices
 */

mat3
mat3m2(mat2 m) {
	return (mat3) {{
		vec3(m.cols[0], 0.0f),
		vec3(m.cols[1], 0.0f),
		vec3(0.0f, 0.0f, 1.0f),
	}};
}

mat4
mat4m2(mat2 m) {
	return (mat4) {{
		vec4(m.cols[0], 0.0f, 0.0f),
		vec4(m.cols[1], 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
	}};
}

mat4
mat4m3(mat3 m) {
	return (mat4) {{
		vec4(m.cols[0], 0.0f),
		vec4(m.cols[1], 0.0f),
		vec4(m.cols[2], 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f),
	}};
}

/*
 * Fill matrix directly
 */

mat2
mat2f4(
		float x1, float y1,
		float x2, float y2
	) {
	return (mat2) {{
		vec2(x1, y1),
		vec2(x2, y2),
	}};
}

mat3
mat3f9(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3
	) {
	return (mat3) {{
		vec3(x1, y1, z1),
		vec3(x2, y2, z2),
		vec3(x3, y3, z3),
	}};
}

mat4
mat4f16(
		float x1, float y1, float z1, float w1,
		float x2, float y2, float z2, float w2,
		float x3, float y3, float z3, float w3,
		float x4, float y4, float z4, float w4
	) {
	return (mat4) {{
		vec4(x1, y1, z1, w1),
		vec4(x2, y2, z2, w2),
		vec4(x3, y3, z3, w3),
		vec4(x4, y4, z4, w4),
	}};
}

/*
 * Dot product
 */

float
dotv2(vec2 a, vec2 b) {
	return (a.x * b.x) + (a.y * b.y);
}

float
dotv3(vec3 a, vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float
dotv4(vec4 a, vec4 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/*
 * Cross product
 */
vec3
cross(vec3 a, vec3 b) {
	return vec3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
	);
}

/*
 * Lengths
 */

float
lengthv2(vec2 a) {
	return sqrt(dot(a, a));
}

float
lengthv3(vec3 a) {
	return sqrt(dot(a, a));
}

float
lengthv4(vec4 a) {
	return sqrt(dot(a, a));
}

/*
 * Normalize
 */

vec2
normalizev2(vec2 a) {
	return (vec2) { a._v / length(a) };
}

vec3
normalizev3(vec3 a) {
	return (vec3) { a._v / length(a) };
}

vec4
normalizev4(vec4 a) {
	return (vec4) { a._v / length(a) };
}


/*
 * Matrix transpose
 */

mat2
transposem2(mat2 m) {
	return (mat2) {{
		vec2(m.cols[0].x, m.cols[1].x),
		vec2(m.cols[0].y, m.cols[1].y),
	}};
}

mat3
transposem3(mat3 m) {
	return (mat3) {{
		vec3(m.cols[0].x, m.cols[1].x, m.cols[2].x),
		vec3(m.cols[0].y, m.cols[1].y, m.cols[2].y),
		vec3(m.cols[0].z, m.cols[1].z, m.cols[2].z),
	}};
}

mat4
transposem4(mat4 m) {
	return (mat4) {{
		vec4(m.cols[0].x, m.cols[1].x, m.cols[2].x, m.cols[3].x),
		vec4(m.cols[0].y, m.cols[1].y, m.cols[2].y, m.cols[3].y),
		vec4(m.cols[0].z, m.cols[1].z, m.cols[2].z, m.cols[3].z),
		vec4(m.cols[0].w, m.cols[1].w, m.cols[2].w, m.cols[3].w),
	}};
}

/*
 * Matrix multiplication
 */

mat2
multm2(mat2 m, mat2 n) {
	const mat2 mt = transpose(m);

	return (mat2) {{
		vec2(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0])),
		vec2(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1])),
	}};
}

mat3
multm3(mat3 m, mat3 n) {
	const mat3 mt = transpose(m);

	return (mat3) {{
		vec3(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0]), dot(mt.cols[2], n.cols[0])),
		vec3(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1]), dot(mt.cols[2], n.cols[1])),
		vec3(dot(mt.cols[0], n.cols[2]), dot(mt.cols[1], n.cols[2]), dot(mt.cols[2], n.cols[2])),
	}};
}

mat4
multm4(mat4 m, mat4 n) {
	const mat4 mt = transpose(m);

	return (mat4) {{
		vec4(dot(mt.cols[0], n.cols[0]), dot(mt.cols[1], n.cols[0]), dot(mt.cols[2], n.cols[0]), dot(mt.cols[3], n.cols[0])),
		vec4(dot(mt.cols[0], n.cols[1]), dot(mt.cols[1], n.cols[1]), dot(mt.cols[2], n.cols[1]), dot(mt.cols[3], n.cols[1])),
		vec4(dot(mt.cols[0], n.cols[2]), dot(mt.cols[1], n.cols[2]), dot(mt.cols[2], n.cols[2]), dot(mt.cols[3], n.cols[2])),
		vec4(dot(mt.cols[0], n.cols[3]), dot(mt.cols[1], n.cols[3]), dot(mt.cols[2], n.cols[3]), dot(mt.cols[3], n.cols[3])),
	}};
}

/*
 * Matrix determinant
 */

float
determinantm2(const mat2 m) {
	const float a = m.cols[0].x;
	const float d = m.cols[1].y;
	const float c = m.cols[0].y;
	const float b = m.cols[1].x;

	return a * d - b * c;
}

float
determinantm3(const mat3 m) {
	const float det =
		m.cols[0].x * determinant(mat2(
			m.cols[1].y, m.cols[1].z,
			m.cols[2].y, m.cols[2].z
		))
		- m.cols[1].x * determinant(mat2(
			m.cols[0].y, m.cols[0].z,
			m.cols[2].y, m.cols[2].z
		))
		+ m.cols[2].x * determinant(mat2(
			m.cols[0].y, m.cols[0].z,
			m.cols[1].y, m.cols[1].z
		));

	return det;
}

float
determinantm4(const mat4 m) {
	const float det =
		m.cols[0].x * determinant(mat3(
			m.cols[1].y, m.cols[1].z, m.cols[1].w,
			m.cols[2].y, m.cols[2].z, m.cols[2].w,
			m.cols[3].y, m.cols[3].z, m.cols[3].w
		))
		- m.cols[1].x * determinant(mat3(
			m.cols[0].y, m.cols[0].z, m.cols[0].w,
			m.cols[2].y, m.cols[2].z, m.cols[2].w,
			m.cols[3].y, m.cols[3].z, m.cols[3].w
		))
		+ m.cols[2].x * determinant(mat3(
			m.cols[0].y, m.cols[0].z, m.cols[0].w,
			m.cols[1].y, m.cols[1].z, m.cols[1].w,
			m.cols[3].y, m.cols[3].z, m.cols[3].w
		))
		- m.cols[3].x * determinant(mat3(
			m.cols[0].y, m.cols[0].z, m.cols[0].w,
			m.cols[1].y, m.cols[1].z, m.cols[1].w,
			m.cols[2].y, m.cols[2].z, m.cols[2].w
		));

	return det;
}

/*
 * Calculate the inverse matrix.
 *
 * The algorithm used is based on the classical adjoint, as recommended by
 * "3D Math Primer for Graphics and Game Development" (2nd ed) by Dunn and
 * Parberry, section 6.2. The text argues that for small 2x2, 3x3 or 4x4
 * matrices, the fact that this algorithm is branchless makes it superior
 * to Gaussian elimination.
 *
 * The result is undefined if the matrix is non-invertible or is poorly
 * conditioned (nearly non-invertible).
 */
mat4
inversem4(const mat4 m) {
	/* mutable */ mat4 inv = mat4(0.0f);

	const float det = determinant(m);

	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			const float sign = (row + col) % 2 == 0 ? 1.0f : -1.0f;
			/* const float sign = powf(-1, row + col); */

			const int j0 = 0 + (col <= 0);
			const int j1 = 1 + (col <= 1);
			const int j2 = 2 + (col <= 2);

			const int i0 = 0 + (row <= 0);
			const int i1 = 1 + (row <= 1);
			const int i2 = 2 + (row <= 2);

			inv.cols[col]._v[row] = sign * determinant(mat3(
				m.cols[j0]._v[i0], m.cols[j0]._v[i1], m.cols[j0]._v[i2],
				m.cols[j1]._v[i0], m.cols[j1]._v[i1], m.cols[j1]._v[i2],
				m.cols[j2]._v[i0], m.cols[j2]._v[i1], m.cols[j2]._v[i2]
			)) / det;
		}
	}

	return transpose(inv);
}
