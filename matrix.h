/*
 * Matrix library for OpenGL games.
 *
 * The functions, as much as possible in C, mimic the GLM C++ library and GLSL.
 *
 * However, some conventions differ, namely
 *   - The types use a _t suffix to avoid clashing with the constructor functions.
 *   - Constructors have the same name as the type, as in GLSL.
 *
 * For example, in GLM you might do
 *     GLM::mat4 m(1.0)
 * but in this library, instead use
 *     mat4_t m = mat4(1.0)
 *
 * As in GLM and GLSL, matrices are column-major. Therefore, m[i] would be the ith column-vector.
 *
 * The functions are overloaded, using macros around type-dependent _Generic selection, so that
 * the same function name can be used regardless of the size of the vector or matrix. For example,
 *     c = dot(a, b)
 * will work on two-, three- or four-dimensional vectors so long as they are the all the same size.
 *
 */

#include <stdbool.h>

#define M_SWIZZLE

typedef float v4f_t __attribute__((vector_size (sizeof(float) * 4)));
/*
 * Vector types must be a power of two in GCC, so we just make vec3 the same
 * size as vec4. Unfortunately, this means we can't use vec3 to swizzle a vec4,
 * because it extends the whole width of the vec4.
 */
//typedef float v3f_t __attribute__((vector_size (sizeof(float) * 3)));
typedef v4f_t v3f_t;
typedef float v2f_t __attribute__((vector_size (sizeof(float) * 2)));

union vec2 {
	v2f_t _v;

	struct {
		float x, y;
	};

	/* no rgba for vec2 */
};

union vec3 {
	v3f_t _v;

	struct {
		float x, y, z;
	};

	struct {
		float r, g, b;
	};
};

union vec4 {
	v4f_t _v;

	struct {
		float x, y, z, w;
	};

	struct {
		float r, g, b, a;
	};

	// not sure if these work, haven't tested yet
	/* I don't think we can mess with the order, but we can do at
	 * least do some of the swizzles.
	 *
	 * Unfortunately, since sizeof(v3f_t) == sizeof(v4f_t), we can't
	 * do swizzles like .xyz or .yzw.
	 *
	 */
#ifdef M_SWIZZLE
	struct {
		v2f_t xy;
		v2f_t zw;
	};
#endif
};

typedef union vec2 vec2_t;
typedef union vec3 vec3_t;
typedef union vec4 vec4_t;

/* Using a union or struct means the matrix will be passed by value, however
 * it also means we don't get to use arrays subscripting directly, which is
 * a bit sad.
 */

union mat2 {
	vec2_t cols[2];
};

union mat3 {
	vec3_t cols[3];
};

union mat4 {
	vec4_t cols[4];
};

typedef union mat2 mat2_t;
typedef union mat3 mat3_t;
typedef union mat4 mat4_t;

/* Set all components to the same value */
vec2_t vec2f1(float);
vec3_t vec3f1(float);
vec4_t vec4f1(float);

/* Set each component to the given value */
vec2_t vec2f2(float, float);
vec3_t vec3f3(float, float, float);
vec4_t vec4f4(float, float, float, float);

/*
 * Fill from other vectors
 */

vec2_t vec2v3(vec3_t);
vec2_t vec2v4(vec4_t);

vec3_t vec3v2f1(vec2_t, float);
vec3_t vec3f1v2(float, vec2_t);
vec3_t vec3v4(vec4_t);

vec4_t vec4v3f1(vec3_t, float);
vec4_t vec4f1v3(float, vec3_t);
vec4_t vec4v2v2(vec2_t, vec2_t);
vec4_t vec4v2f2(vec2_t, float, float);
vec4_t vec4f2v2(float, float, vec2_t);

/*
 * Using default (rather than float) so that number literals are
 * converted to floats.
 */

#define VEC2_NARGS_1(A) _Generic((A)    \
    , default: vec2f1                   \
    , vec3_t:  vec2v3                   \
    , vec4_t:  vec2v4                   \
    )(A)
#define VEC2_NARGS_2(A, B) vec2f2(A, B)

#define VEC3_NARGS_1(A) _Generic((A)    \
    , default: vec3f1                   \
    , vec4_t:  vec3v4                   \
    )(A)
#define VEC3_NARGS_2(A, B) _Generic((A) \
    , vec2_t: vec3v2f1                  \
    , float:  vec3f1v2                  \
    )(A, B)
#define VEC3_NARGS_3(A, B, C) vec3f3(A, B, C)

#define VEC4_NARGS_1(A) vec4f1(A)
#define VEC4_NARGS_2(A, B) _Generic((A) \
    , vec2_t: vec4v2v2                  \
    , vec3_t: vec4v3f1                  \
    , float:  vec4f1v3                  \
    )(A, B)
#define VEC4_NARGS_3(A, B, C) _Generic((A) \
    , vec2_t: vec4v2f2                     \
    , float:  vec4f2v2                     \
    )(A, B, C)
#define VEC4_NARGS_4(A, B, C, D) vec4f4(A, B, C, D)

// Uses a funky trick to overload the function based on the number of arguments
#define OVERLOAD_ARGS_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, X, ...) X
#define OVERLOAD_ARGS_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, X, ...) X
#define OVERLOAD_ARGS_4(_1, _2, _3, _4, X, ...) X
#define OVERLOAD_ARGS_3(_1, _2, _3, X, ...) X
#define OVERLOAD_ARGS_2(_1, _2, X, ...) X

#define vec2(...) OVERLOAD_ARGS_2(__VA_ARGS__, VEC2_NARGS_2, VEC2_NARGS_1)(__VA_ARGS__)
#define vec3(...) OVERLOAD_ARGS_3(__VA_ARGS__, VEC3_NARGS_3, VEC3_NARGS_2, VEC3_NARGS_1)(__VA_ARGS__)
#define vec4(...) OVERLOAD_ARGS_4(__VA_ARGS__, VEC4_NARGS_4, VEC4_NARGS_3, VEC4_NARGS_2, VEC4_NARGS_1)(__VA_ARGS__)

#define GENERIC_VEC(FN, A) _Generic((A) \
    , vec2_t: FN ## v2                  \
    , vec3_t: FN ## v3                  \
    , vec4_t: FN ## v4                  \
    )

bool equalsv2(vec2_t, vec2_t);
bool equalsv3(vec3_t, vec3_t);
bool equalsv4(vec4_t, vec4_t);
#define equals(A, B) GENERIC_VEC(dot, A)(A, B)

float dotv2(vec2_t, vec2_t);
float dotv3(vec3_t, vec3_t);
float dotv4(vec4_t, vec4_t);
#define dot(A, B) GENERIC_VEC(dot, A)(A, B)

float lengthv2(vec2_t);
float lengthv3(vec3_t);
float lengthv4(vec4_t);
#define length(A) GENERIC_VEC(length, A)(A)

vec2_t normalizev2(vec2_t);
vec3_t normalizev3(vec3_t);
vec4_t normalizev4(vec4_t);
#define normalize(A) GENERIC_VEC(normalize, A)(A)

/* Diagonal matrix with the diagonal elements all of the given value */
mat2_t mat2f1(float);
mat3_t mat3f1(float);
mat4_t mat4f1(float);

/* Fills matrix with the values from the smaller matrix, starting in the upper left */
mat3_t mat3m2(mat2_t);
mat4_t mat4m2(mat2_t);
mat4_t mat4m3(mat3_t);

/* Fills matrix directly - column major */
mat2_t mat2f4(float, float, float, float);
mat3_t mat3f9(float, float, float, float, float, float, float, float, float);
mat4_t mat4f16(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

#define MAT2_NARGS_1(A) _Generic((A) \
    , float:   mat2f1                \
    )(A)

#define MAT2_NARGS_4(A, ...) _Generic((A) \
    , float:   mat2f4                     \
    )(A, __VA_ARGS__)


#define MAT3_NARGS_1(A) _Generic((A) \
    , float:   mat3f1                \
    , mat2_t:  mat3m2                \
    )(A)

#define MAT3_NARGS_9(A, ...) _Generic((A) \
    , float:   mat3f9                     \
    )(A, __VA_ARGS__)


#define MAT4_NARGS_1(A) _Generic((A) \
    , float:   mat4f1                \
    , mat2_t:  mat4m2                \
    , mat3_t:  mat4m3                \
    )(A)

#define MAT4_NARGS_16(A, ...) _Generic((A) \
    , float:   mat4f16                     \
    )(A, __VA_ARGS__)

#define mat2(...) OVERLOAD_ARGS_4(__VA_ARGS__, MAT2_NARGS_4, MAT2_NARGS_3, MAT2_NARGS_2, MAT2_NARGS_1)(__VA_ARGS__)
#define mat3(...) OVERLOAD_ARGS_9(__VA_ARGS__, MAT3_NARGS_9, MAT3_NARGS_8, MAT3_NARGS_7, MAT3_NARGS_6, MAT3_NARGS_5, MAT3_NARGS_4, MAT3_NARGS_3, MAT3_NARGS_2, MAT3_NARGS_1)(__VA_ARGS__)
#define mat4(...) OVERLOAD_ARGS_16(__VA_ARGS__, MAT4_NARGS_16, MAT4_NARGS_15, MAT4_NARGS_14, MAT4_NARGS_13, MAT4_NARGS_12, MAT4_NARGS_11, MAT4_NARGS_10, MAT4_NARGS_9, MAT4_NARGS_8, MAT4_NARGS_7, MAT4_NARGS_6, MAT4_NARGS_5, MAT4_NARGS_4, MAT4_NARGS_3, MAT4_NARGS_2, MAT4_NARGS_1)(__VA_ARGS__)


/*
#define GENERIC_MAT(FN, A) _Generic((A) \
    , mat2_t: FN ## m2                  \
    , mat3_t: FN ## m3                  \
    , mat4_t: FN ## m4                  \
    )
*/
