#include <tgmath.h>

#include "matrix.h"

// FIXME: should use SSE/instrinsics for vector calculations


/*
 * Single-argument vector constructors
 */

vec2_t
vec2f1(float x) {
	return (vec2_t) {{ x, x }};
}

vec3_t
vec3f1(float x) {
	return (vec3_t) {{ x, x, x }};
}

vec4_t
vec4f1(float x) {
	return (vec4_t) {{ x, x, x, x }};
}

/*
 * Complete vector constructors
 */

vec2_t
vec2f2(float x, float y) {
	return (vec2_t) {{ x, y }};
}

vec3_t
vec3f3(float x, float y, float z) {
	return (vec3_t) {{ x, y, z }};
}

vec4_t
vec4f4(float x, float y, float z, float w) {
	return (vec4_t) {{ x, y, z, w }};
}

/*
 * Constructor from other vectors
 */

vec2_t
vec2v3(vec3_t v) {
	return (vec2_t) {{ v.x, v.y }};
}

vec2_t
vec2v4(vec4_t v) {
	return (vec2_t) {{ v.x, v.y }};
}


vec3_t
vec3v2f1(vec2_t v, float z) {
	return (vec3_t) {{ v.x, v.y, z }};
}

vec3_t
vec3f1v2(float x, vec2_t v) {
	return (vec3_t) {{ x, v.x, v.y }};
}

vec3_t
vec3v4(vec4_t v) {
	return (vec3_t) {{ v.x, v.y, v.z }};
}


vec4_t
vec4v3f1(vec3_t v, float w) {
	return (vec4_t) {{ v.x, v.y, v.z, w }};
}

vec4_t
vec4f1v3(float x, vec3_t v) {
	return (vec4_t) {{ x, v.x, v.y, v.z }};
}

vec4_t
vec4v2v2(vec2_t a, vec2_t b) {
	return (vec4_t) {{ a.x, a.y, b.x, b.y }};
}

vec4_t
vec4v2f2(vec2_t v, float z, float w) {
	return (vec4_t) {{ v.x, v.y, z, w }};
}

vec4_t
vec4f2v2(float x, float y, vec2_t v) {
	return (vec4_t) {{ x, y, v.x, v.y }};
}


/*
 * Vector equality
 *
 * Note: in glm, equality is component-wise, but I needed a way to easily test equality in tests.
 */

bool
equalsv2(vec2_t a, vec2_t b) {
#include <assert.h>
	assert(false);
	return a.x == b.x && a.y == b.y;
}

bool
equalsv3(vec3_t a, vec3_t b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool
equalsv4(vec4_t a, vec4_t b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

/*
 * Single argument matrix constructors
 */

mat2_t
mat2f1(float x) {
	return (mat2_t) {{
		vec2(x, 0.0),
		vec2(0.0, x),
	}};
}

mat3_t
mat3f1(float x) {
	return (mat3_t) {{
		vec3(x, 0.0, 0.0),
		vec3(0.0, x, 0.0),
		vec3(0.0, 0.0, x),
	}};
}

mat4_t
mat4f1(float x) {
	return (mat4_t) {{
		vec4(x, 0.0, 0.0, 0.0),
		vec4(0.0, x, 0.0, 0.0),
		vec4(0.0, 0.0, x, 0.0),
		vec4(0.0, 0.0, 0.0, x),
	}};
}

/*
 * From other matrices
 */

mat3_t
mat3m2(mat2_t m) {
	return (mat3_t) {{
		vec3(m.cols[0], 0),
		vec3(m.cols[1], 0),
		vec3(0.0, 0.0, 1.0),
	}};
}

mat4_t
mat4m2(mat2_t m) {
	return (mat4_t) {{
		vec4(m.cols[0], 0.0, 0.0),
		vec4(m.cols[1], 0.0, 0.0),
		vec4(0.0, 0.0, 1.0, 0.0),
		vec4(0.0, 0.0, 0.0, 1.0),
	}};
}

mat4_t
mat4m3(mat3_t m) {
	return (mat4_t) {{
		vec4(m.cols[0], 0),
		vec4(m.cols[1], 0),
		vec4(m.cols[2], 0),
		vec4(0.0, 0.0, 0.0, 1.0),
	}};
}

/*
 * Fill matrix directly
 */

mat2_t
mat2f4(
		float x1, float y1,
		float x2, float y2
	) {
	return (mat2_t) {{
		vec2(x1, y1),
		vec2(x2, y2),
	}};
};

mat3_t
mat3f9(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3
	) {
	return (mat3_t) {{
		vec3(x1, y1, z1),
		vec3(x2, y2, z2),
		vec3(x3, y3, z3),
	}};
};

mat4_t
mat4f16(
		float x1, float y1, float z1, float w1,
		float x2, float y2, float z2, float w2,
		float x3, float y3, float z3, float w3,
		float x4, float y4, float z4, float w4
	) {
	return (mat4_t) {{
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
dotv2(vec2_t a, vec2_t b) {
	return (a.x * b.x) + (a.y * b.y);
}

float
dotv3(vec3_t a, vec3_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float
dotv4(vec4_t a, vec4_t b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/*
 * Lengths
 */

float
lengthv2(vec2_t a) {
	return sqrt(dot(a, a));
}

float
lengthv3(vec3_t a) {
	return sqrt(dot(a, a));
}

float
lengthv4(vec4_t a) {
	return sqrt(dot(a, a));
}

/*
 * Normalize
 */

vec2_t
normalizev2(vec2_t a) {
	return (vec2_t) { a._v / length(a) };
}

vec3_t
normalizev3(vec3_t a) {
	return (vec3_t) { a._v / length(a) };
}

vec4_t
normalizev4(vec4_t a) {
	return (vec4_t) { a._v / length(a) };
}
