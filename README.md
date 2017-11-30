# Matrix Library for OpenGL Games

The functions mimic the OpenGL Mathematics (GLM) C++ library and the OpenGL Shading Language (GLSL).

In order to support overloading, the functions are actually function-like macros that wrap around C11 type-dependent `_Generic` selection, so that the same function name can be used regardless of the size of the vector or matrix.
For example,

```c
c = dot(a, b)
```

will work on two-, three- or four-dimensional vectors so long as they are both the same size.

As in GLM and GLSL, matrices are column-major.

Warning: this uses some very horrible macro hacks to mimic functions that are overloaded on the number and type of parameters.
It'll produce error vomit if the wrong number of arguments or types are used.
Please don't actually use anything like this in the real world.
Thanks.

# Vector Constructors

Vectors can be constructed directly.

```c
vec2 a = vec2(1.0, 2.0);
vec3 b = vec3(1.0, 2.0, 3.0);
vec4 c = vec4(1.0, 2.0, 3.0, 4.0);
```

Or all the components of the vector can be set to the same number.

```c
vec2 a = vec2(1.0); // = vec2(1.0, 1.0);
vec3 b = vec3(1.0); // = vec3(1.0, 1.0, 1.0);
vec4 c = vec4(1.0); // = vec4(1.0, 1.0, 1.0, 1.0);
```

A higher-dimensional vector can be converted to a lower-dimensional vector, which discards the higher-dimensional components.


```c
vec4 a = vec4(1.0, 2.0, 3.0, 4.0);

vec3 b = vec3(a); // = vec3(1.0, 2.0, 3.0);

vec2 c = vec2(a); // = vec2(1.0, 2.0);
vec2 d = vec2(b); // = vec2(1.0, 2.0);
```

Or a lower-dimensional vector from a higher-dimensional one by supplying the remaining components.

```c
vec2 a = vec2(1.0, 2.0);

vec3 b = vec3(a, 3.0); // = vec3(1.0, 2.0, 3.0);

vec4 c = vec4(a, 3.0, 4.0); // = vec4(1.0, 2.0, 3.0, 4.0);
vec4 d = vec4(b, 4.0); // = vec4(1.0, 2.0, 3.0, 4.0);
```

# Matrix Constructors

Given a single number, a matrix constructor creates a diagonal matrix.

```c
mat2 id2x2 = mat2(1.0);
/*
  ┌          ┐
  │ 1.0  0.0 │
  │ 0.0  1.0 │
  └          ┘
 */

mat3 id3x3 = mat3(1.0);
/*
  ┌               ┐
  │ 1.0  0.0  0.0 │
  │ 0.0  1.0  0.0 │
  │ 0.0  0.0  1.0 │
  └               ┘
 */

mat4 id4x4 = mat4(1.0);
/*
  ┌                    ┐
  │ 1.0  0.0  0.0  0.0 │
  │ 0.0  1.0  0.0  0.0 │
  │ 0.0  0.0  1.0  0.0 │
  │ 0.0  0.0  0.0  1.0 │
  └                    ┘
 */
```

Or a matrix can be filled directly, filling each *column* (not row) first.

```c
mat2 m2x2 = mat2(
    1.0, 2.0, // first column
    3.0, 4.0  // second column
);
/*
  ┌          ┐
  │ 1.0  3.0 │
  │ 2.0  4.0 │
  └          ┘
 */

mat3 m3x3 = mat3(
    1.0, 2.0, 3.0, // first column
    4.0, 5.0, 6.0, // second column
    7.0, 8.0, 9.0  // third column
);
/*
  ┌               ┐
  │ 1.0  4.0  7.0 │
  │ 2.0  5.0  8.0 │
  │ 3.0  6.0  9.0 │
  └               ┘
 */

mat4 m4x4 = mat4(
     1.0,  2.0,  3.0,  4.0, // first column
     5.0,  6.0,  7.0,  8.0, // second column
     9.0, 10.0, 11.0, 12.0, // third column
    13.0, 14.0, 15.0, 16.0  // fourth column
);
/*
  ┌                      ┐
  │ 1.0  5.0   9.0  13.0 │
  │ 2.0  6.0  10.0  14.0 │
  │ 3.0  7.0  11.0  15.0 │
  │ 4.0  8.0  12.0  16.0 │
  └                      ┘
 */
```
