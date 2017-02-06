/*
 * Matrix library for OpenGL games.
 *
 * The functions, as much as possible in C, mimic the GLM C++ library and GLSL.
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
#define pure __attribute__((const))

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

typedef union vec2 vec2;
typedef union vec3 vec3;
typedef union vec4 vec4;

/* Using a union or struct means the matrix will be passed by value, however
 * it also means we don't get to use arrays subscripting directly, which is
 * a bit sad.
 */

union mat2 {
	vec2 cols[2];
};

union mat3 {
	vec3 cols[3];
};

union mat4 {
	vec4 cols[4];
};

typedef union mat2 mat2;
typedef union mat3 mat3;
typedef union mat4 mat4;

/* Set all components to the same value */
pure vec2 vec2f1(float);
pure vec3 vec3f1(float);
pure vec4 vec4f1(float);

/* Set each component to the given value */
pure vec2 vec2f2(float, float);
pure vec3 vec3f3(float, float, float);
pure vec4 vec4f4(float, float, float, float);

/*
 * Fill from other vectors
 */

pure vec2 vec2v3(vec3);
pure vec2 vec2v4(vec4);

pure vec3 vec3v2f1(vec2, float);
pure vec3 vec3f1v2(float, vec2);
pure vec3 vec3v4(vec4);

pure vec4 vec4v3f1(vec3, float);
pure vec4 vec4f1v3(float, vec3);
pure vec4 vec4v2v2(vec2, vec2);
pure vec4 vec4v2f2(vec2, float, float);
pure vec4 vec4f2v2(float, float, vec2);

/*
 * Using default (rather than float) so that number literals are
 * converted to floats.
 */

#define VEC2_ARGS_1(A) _Generic((A)    \
    , float: vec2f1                     \
    , vec3:  vec2v3                     \
    , vec4:  vec2v4                     \
    )(A)
#define VEC2_ARGS_2(A, B) vec2f2(A, B)

#define VEC3_ARGS_1(A) _Generic((A)    \
    , float: vec3f1                     \
    , vec4:  vec3v4                     \
    )(A)
#define VEC3_ARGS_2(A, B) _Generic((A) \
    , vec2: vec3v2f1                    \
    , float:  vec3f1v2                  \
    )(A, B)
#define VEC3_ARGS_3(A, B, C) vec3f3(A, B, C)

#define VEC4_ARGS_1(A) vec4f1(A)
#define VEC4_ARGS_2(A, B) _Generic((A) \
    , vec2: vec4v2v2                    \
    , vec3: vec4v3f1                    \
    , float:  vec4f1v3                  \
    )(A, B)
#define VEC4_ARGS_3(A, B, C) _Generic((A) \
    , vec2: vec4v2f2                       \
    , float:  vec4f2v2                     \
    )(A, B, C)
#define VEC4_ARGS_4(A, B, C, D) vec4f4(A, B, C, D)

// Uses a funky trick to overload the function based on the number of arguments
#define OVERLOAD_ARGS_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, X, ...) X
#define OVERLOAD_ARGS_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, X, ...) X
#define OVERLOAD_ARGS_4(_1, _2, _3, _4, X, ...) X
#define OVERLOAD_ARGS_3(_1, _2, _3, X, ...) X
#define OVERLOAD_ARGS_2(_1, _2, X, ...) X

#define vec2(...) OVERLOAD_ARGS_2(__VA_ARGS__, VEC2_ARGS_2, VEC2_ARGS_1)(__VA_ARGS__)
#define vec3(...) OVERLOAD_ARGS_3(__VA_ARGS__, VEC3_ARGS_3, VEC3_ARGS_2, VEC3_ARGS_1)(__VA_ARGS__)
#define vec4(...) OVERLOAD_ARGS_4(__VA_ARGS__, VEC4_ARGS_4, VEC4_ARGS_3, VEC4_ARGS_2, VEC4_ARGS_1)(__VA_ARGS__)

#define GENERIC_VEC(FN, A) _Generic((A) \
    , vec2: FN ## v2                    \
    , vec3: FN ## v3                    \
    , vec4: FN ## v4                    \
    )

pure float dotv2(vec2, vec2);
pure float dotv3(vec3, vec3);
pure float dotv4(vec4, vec4);
#define dot(A, B) GENERIC_VEC(dot, A)(A, B)

pure float lengthv2(vec2);
pure float lengthv3(vec3);
pure float lengthv4(vec4);
#define length(A) GENERIC_VEC(length, A)(A)

pure vec2 normalizev2(vec2);
pure vec3 normalizev3(vec3);
pure vec4 normalizev4(vec4);
#define normalize(A) GENERIC_VEC(normalize, A)(A)

/* Diagonal matrix with the diagonal elements all of the given value */
pure mat2 mat2f1(float);
pure mat3 mat3f1(float);
pure mat4 mat4f1(float);

/* Fills matrix with the values from the smaller matrix, starting in the upper left */
pure mat3 mat3m2(mat2);
pure mat4 mat4m2(mat2);
pure mat4 mat4m3(mat3);

/* Fills columns from vectors */
pure mat2 mat2v2(vec2, vec2);
pure mat3 mat3v3(vec3, vec3, vec3);
pure mat4 mat4v4(vec4, vec4, vec4, vec4);

/* Fills matrix directly - column major */
pure mat2 mat2f4(float, float, float, float);
pure mat3 mat3f9(float, float, float, float, float, float, float, float, float);
pure mat4 mat4f16(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

#define MAT2_ARGS_1(A) _Generic((A) \
    , float:   mat2f1                \
    )(A)

#define MAT2_ARGS_2(A, B) _Generic((A) \
    , vec2: mat2v2                      \
    )(A, B)

#define MAT2_ARGS_4(A, ...) _Generic((A) \
    , float:   mat2f4                     \
    )(A, __VA_ARGS__)


#define MAT3_ARGS_1(A) _Generic((A) \
    , float:   mat3f1                \
    , mat2:  mat3m2                  \
    )(A)

#define MAT3_ARGS_3(A, B, C) _Generic((A) \
    , vec3:  mat3v3                        \
    )(A, B, C)

#define MAT3_ARGS_9(A, ...) _Generic((A) \
    , float:   mat3f9                     \
    )(A, __VA_ARGS__)


#define MAT4_ARGS_1(A) _Generic((A) \
    , float:   mat4f1                \
    , mat2:  mat4m2                  \
    , mat3:  mat4m3                  \
    )(A)

#define MAT4_ARGS_4(A, B, C, D) _Generic((A) \
    , vec4: mat4v4                            \
    )(A, B, C, D)

#define MAT4_ARGS_16(A, ...) _Generic((A) \
    , float:   mat4f16                     \
    )(A, __VA_ARGS__)

#define mat2(...) OVERLOAD_ARGS_4(__VA_ARGS__, MAT2_ARGS_4, MAT2_ARGS_3, MAT2_ARGS_2, MAT2_ARGS_1)(__VA_ARGS__)
#define mat3(...) OVERLOAD_ARGS_9(__VA_ARGS__, MAT3_ARGS_9, MAT3_ARGS_8, MAT3_ARGS_7, MAT3_ARGS_6, MAT3_ARGS_5, MAT3_ARGS_4, MAT3_ARGS_3, MAT3_ARGS_2, MAT3_ARGS_1)(__VA_ARGS__)
#define mat4(...) OVERLOAD_ARGS_16(__VA_ARGS__, MAT4_ARGS_16, MAT4_ARGS_15, MAT4_ARGS_14, MAT4_ARGS_13, MAT4_ARGS_12, MAT4_ARGS_11, MAT4_ARGS_10, MAT4_ARGS_9, MAT4_ARGS_8, MAT4_ARGS_7, MAT4_ARGS_6, MAT4_ARGS_5, MAT4_ARGS_4, MAT4_ARGS_3, MAT4_ARGS_2, MAT4_ARGS_1)(__VA_ARGS__)


#define GENERIC_MAT(FN, A) _Generic((A) \
    , mat2: FN ## m2                    \
    , mat3: FN ## m3                    \
    , mat4: FN ## m4                    \
    )

pure mat2 transposem2(mat2);
pure mat3 transposem3(mat3);
pure mat4 transposem4(mat4);
#define transpose(M) GENERIC_MAT(transpose, M)(M)

pure mat2 multm2(mat2, mat2);
pure mat3 multm3(mat3, mat3);
pure mat4 multm4(mat4, mat4);
#define mult(M, N) GENERIC_MAT(mult, M)(M, N)
