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
 * Vector equality
 *
 * Note: in glm, equality is component-wise, but I needed a way to easily test equality in tests.
 */

bool
equalsv2(vec2 a, vec2 b) {
	return a.x == b.x && a.y == b.y;
}

bool
equalsv3(vec3 a, vec3 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool
equalsv4(vec4 a, vec4 b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

/*
 * Single argument matrix constructors
 */

mat2
mat2f1(float x) {
	return (mat2) {{
		vec2(x, 0.0),
		vec2(0.0, x),
	}};
}

mat3
mat3f1(float x) {
	return (mat3) {{
		vec3(x, 0.0, 0.0),
		vec3(0.0, x, 0.0),
		vec3(0.0, 0.0, x),
	}};
}

mat4
mat4f1(float x) {
	return (mat4) {{
		vec4(x, 0.0, 0.0, 0.0),
		vec4(0.0, x, 0.0, 0.0),
		vec4(0.0, 0.0, x, 0.0),
		vec4(0.0, 0.0, 0.0, x),
	}};
}

/*
 * From other matrices
 */

mat3
mat3m2(mat2 m) {
	return (mat3) {{
		vec3(m.cols[0], 0),
		vec3(m.cols[1], 0),
		vec3(0.0, 0.0, 1.0),
	}};
}

mat4
mat4m2(mat2 m) {
	return (mat4) {{
		vec4(m.cols[0], 0.0, 0.0),
		vec4(m.cols[1], 0.0, 0.0),
		vec4(0.0, 0.0, 1.0, 0.0),
		vec4(0.0, 0.0, 0.0, 1.0),
	}};
}

mat4
mat4m3(mat3 m) {
	return (mat4) {{
		vec4(m.cols[0], 0),
		vec4(m.cols[1], 0),
		vec4(m.cols[2], 0),
		vec4(0.0, 0.0, 0.0, 1.0),
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
};

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
};

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
};

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
