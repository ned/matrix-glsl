/*
 * Copyright (c) 2017 Ned Hoy
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

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

#include <assert.h>
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
static_assert(sizeof(union vec2) == 8, "wrong size for vec2");

union vec3 {
	v3f_t _v;

	struct {
		float x, y, z;
	};

	struct {
		float r, g, b;
	};
};
static_assert(sizeof(union vec3) == 16, "wrong size for vec3");

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
static_assert(sizeof(union vec4) == 16, "wrong size for vec4");

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
static_assert(sizeof(union mat2) == 8 * 2, "wrong size for mat2");

union mat3 {
	vec3 cols[3];
};
static_assert(sizeof(union mat3) == 16 * 3, "wrong size for mat3");

union mat4 {
	vec4 cols[4];
};
static_assert(sizeof(union mat4) == 16 * 4, "wrong size for mat4");

typedef union mat2 mat2;
typedef union mat3 mat3;
typedef union mat4 mat4;

// Uses a funky trick to overload the function based on the number of arguments
#define COUNT_ARGS_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, X, ...) X
#define COUNT_ARGS(...) COUNT_ARGS_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

// Have to add some extra levels to concatenate properly
#define CONCAT_(A, B) A ## B
#define CONCAT(A, B) CONCAT_(A, B)
#define GET_OVERLOADED(F, ...) CONCAT(F, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define OVERLOAD_ARGS(F, ...) GET_OVERLOADED(F, __VA_ARGS__)(__VA_ARGS__)

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

#define VEC2_ARGS_1(A) _Generic((A)                            \
    , float: vec2f1                                            \
    , vec3:  vec2v3                                            \
    , vec4:  vec2v4                                            \
    )
#define VEC2_ARGS_2(A, B) vec2f2

#define VEC3_ARGS_1(A) _Generic((A)                            \
    , float: vec3f1                                            \
    , vec4:  vec3v4                                            \
    )
#define VEC3_ARGS_2(A, B) _Generic((A)                         \
    , vec2:  vec3v2f1                                          \
    , float: vec3f1v2                                          \
    )
#define VEC3_ARGS_3(A, B, C) vec3f3

#define VEC4_ARGS_1(A) vec4f1
#define VEC4_ARGS_2(A, B) _Generic((A)                         \
    , vec2:  vec4v2v2                                          \
    , vec3:  vec4v3f1                                          \
    , float: vec4f1v3                                          \
    )
#define VEC4_ARGS_3(A, B, C) _Generic((A)                      \
    , vec2:  vec4v2f2                                          \
    , float: vec4f2v2                                          \
    )
#define VEC4_ARGS_4(A, B, C, D) vec4f4

#define vec2(...) OVERLOAD_ARGS(VEC2_ARGS_, __VA_ARGS__)
#define vec3(...) OVERLOAD_ARGS(VEC3_ARGS_, __VA_ARGS__)
#define vec4(...) OVERLOAD_ARGS(VEC4_ARGS_, __VA_ARGS__)

#define GENERIC_VEC(FN, A) _Generic((A)                        \
    , vec2: FN ## v2                                           \
    , vec3: FN ## v3                                           \
    , vec4: FN ## v4                                           \
    )

pure float dotv2(vec2, vec2);
pure float dotv3(vec3, vec3);
pure float dotv4(vec4, vec4);
#define dot(A, B) GENERIC_VEC(dot, A)(A, B)

pure vec3 cross(vec3, vec3);

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

#define MAT2_ARGS_1(A) _Generic((A)                            \
    , float: mat2f1                                            \
    )

#define MAT2_ARGS_2(A, B) _Generic((A)                         \
    , vec2: mat2v2                                             \
    )

#define MAT2_ARGS_4(A, ...) _Generic((A)                       \
    , float: mat2f4                                            \
    )


#define MAT3_ARGS_1(A) _Generic((A)                            \
    , float: mat3f1                                            \
    , mat2:  mat3m2                                            \
    )

#define MAT3_ARGS_3(A, B, C) _Generic((A)                      \
    , vec3: mat3v3                                             \
    )

#define MAT3_ARGS_9(A, ...) _Generic((A)                       \
    , float: mat3f9                                            \
    )


#define MAT4_ARGS_1(A) _Generic((A)                            \
    , float: mat4f1                                            \
    , mat2:  mat4m2                                            \
    , mat3:  mat4m3                                            \
    )

#define MAT4_ARGS_4(A, B, C, D) _Generic((A)                   \
    , vec4: mat4v4                                             \
    )

#define MAT4_ARGS_16(A, ...) _Generic((A)                      \
    , float: mat4f16                                           \
    )

#define mat2(...) OVERLOAD_ARGS(MAT2_ARGS_, __VA_ARGS__)
#define mat3(...) OVERLOAD_ARGS(MAT3_ARGS_, __VA_ARGS__)
#define mat4(...) OVERLOAD_ARGS(MAT4_ARGS_, __VA_ARGS__)


#define GENERIC_MAT(FN, A) _Generic((A)                        \
    , mat2: FN ## m2                                           \
    , mat3: FN ## m3                                           \
    , mat4: FN ## m4                                           \
    )

pure mat2 transposem2(mat2);
pure mat3 transposem3(mat3);
pure mat4 transposem4(mat4);
#define transpose(M) GENERIC_MAT(transpose, M)(M)

pure mat2 multm2(mat2, mat2);
pure mat3 multm3(mat3, mat3);
pure mat4 multm4(mat4, mat4);
#define mult(M, N) GENERIC_MAT(mult, M)(M, N)

pure float determinantm2(mat2);
pure float determinantm3(mat3);
pure float determinantm4(mat4);
#define determinant(M) GENERIC_MAT(determinant, M)(M)

// We only support the inverse of a 4x4 matrix
pure mat4 inversem4(mat4);
#define inverse(M) inversem4(M)
