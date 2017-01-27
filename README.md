# Vector Constructors

Vectors can be constructed directly.

```{.c}
vec2_t a = vec2(1.0, 2.0);
vec3_t b = vec3(1.0, 2.0, 3.0);
vec4_t c = vec4(1.0, 2.0, 3.0, 4.0);
```

Or all the components of the vector can be set to the same number.

```{.c}
vec2_t a = vec2(1.0); // = vec2(1.0, 1.0);
vec3_t b = vec3(1.0); // = vec3(1.0, 1.0, 1.0);
vec4_t c = vec4(1.0); // = vec4(1.0, 1.0, 1.0, 1.0);
```

A higher-dimensional vector can be converted to a lower-dimensional vector.


```{.c}
vec4_t a = vec4(1.0, 2.0, 3.0, 4.0);

vec3_t b = vec3(a); // = vec3(1.0, 2.0, 3.0);

vec2_t c = vec2(a); // = vec2(1.0, 2.0);
vec2_t d = vec2(b); // = vec2(1.0, 2.0);
```

Or a lower-dimensional vector from a higher-dimensional one by supplying the remaining components.

```{.c}
vec2_t a = vec2(1.0, 2.0);

vec3_t b = vec3(a, 3.0); // = vec3(1.0, 2.0, 3.0);

vec4_t c = vec4(a, 3.0, 4.0); // = vec4(1.0, 2.0, 3.0, 4.0);
vec4_t d = vec4(b, 4.0); // = vec4(1.0, 2.0, 3.0, 4.0);
```

# Matrix Constructors

Given a single number, a matrix constructor creates a diagonal matrix.

```{.c}
mat2_t id2x2 = mat2(1.0);
mat3_t id3x3 = mat3(1.0);
mat4_t id4x4 = mat4(1.0);
```

Or a matrix can be filled directly, filling each *column* (not row) first.

```{.c}
mat2_t m2x2 = mat2(
    1.0, 2.0, // first column
    3.0, 4.0  // second column
);
/*
  ┌          ┐
  │ 1.0  3.0 │
  │ 2.0  4.0 │
  └          ┘
 */

mat3_t m3x3 = mat3(
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
 
mat4_t m4x4 = mat4(
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
