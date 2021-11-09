#ifndef LALGBR_H
#define LALGBR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef struct { float x, y; } vec2f;
typedef struct { float x, y, z; } vec3f;
typedef struct { float x, y, z, w; } vec4f;
typedef struct { float m[2][2]; } mat2f;
typedef struct { float m[3][3]; } mat3f;
typedef struct { float m[4][4]; } mat4f;

float sqrf(float val);

// TODO:
// 1) mat4f

// ===== vec2f =====
vec2f vec2f_add(vec2f lhs, vec2f rhs);
vec2f vec2f_sub(vec2f lhs, vec2f rhs);
vec2f vec2f_mul(vec2f v, float val);
vec2f vec2f_div(vec2f v, float val);
vec2f vec2f_norm(vec2f v);
vec2f vec2f_neg(vec2f v);
float vec2f_dot(vec2f lhs, vec2f rhs);
float vec2f_sqrlen(vec2f v);
float vec2f_len(vec2f v);
void vec2f_print(const char* name, vec2f v);

// ===== vec3f =====
vec3f vec3f_add(vec3f lhs, vec3f rhs);
vec3f vec3f_sub(vec3f lhs, vec3f rhs);
vec3f vec3f_mul(vec3f v, float val);
vec3f vec3f_div(vec3f v, float val);
vec3f vec3f_norm(vec3f v);
vec3f vec3f_neg(vec3f v);
vec3f vec3f_cross(vec3f lhs, vec3f rhs);
float vec3f_dot(vec3f lhs, vec3f rhs);
float vec3f_sqrlen(vec3f v);
float vec3f_len(vec3f v);
void vec3f_print(const char* name, vec3f v);

// ===== vec4f =====
vec4f vec4f_add(vec4f lhs, vec4f rhs);
vec4f vec4f_sub(vec4f lhs, vec4f rhs);
vec4f vec4f_mul(vec4f v, float val);
vec4f vec4f_div(vec4f v, float val);
vec4f vec4f_norm(vec4f v);
vec4f vec4f_neg(vec4f v);
// TODO: Reimplenet cross product using mat4f_minor 
vec4f vec4f_cross(vec4f lhs, vec4f rhs);
float vec4f_dot(vec4f lhs, vec4f rhs);
float vec4f_sqrlen(vec4f v);
float vec4f_len(vec4f v);
void vec4f_print(const char* name, vec4f v);

// ===== mat2f =====
mat2f mat2f_identity(void);
mat2f mat2f_from_vec2fs(vec2f r0, vec2f r1);
mat2f mat2f_add(mat2f lhs, mat2f rhs);
mat2f mat2f_sub(mat2f lhs, mat2f rhs);
mat2f mat2f_mul_val(mat2f m, float val);
vec2f mat2f_mul_vec2f(mat2f m, vec2f v);
mat2f mat2f_mul_mat2f(mat2f lhs, mat2f rhs);
mat2f mat2f_transpose(mat2f m);
float mat2f_minor(mat2f m, int r, int c);
float mat2f_cof(mat2f m, int r, int c);
float mat2f_det(mat2f m);
mat2f mat2f_adj(mat2f m);
mat2f mat2f_inverse(mat2f m);
void mat2f_print(const char* name, mat2f m);

// ===== mat3f =====
mat3f mat3f_identity(void);
mat3f mat3f_from_vec3fs(vec3f r0, vec3f r1, vec3f r2);
mat3f mat3f_add(mat3f lhs, mat3f rhs);
mat3f mat3f_sub(mat3f lhs, mat3f rhs);
mat3f mat3f_mul_val(mat3f m, float val);
vec3f mat3f_mul_vec3f(mat3f m, vec3f v);
mat3f mat3f_mul_mat3f(mat3f lhs, mat3f rhs);
mat3f mat3f_transpose(mat3f m);
float mat3f_minor(mat3f m, int r, int c);
float mat3f_cof(mat3f m, int r, int c);
float mat3f_det(mat3f m);
mat3f mat3f_adj(mat3f m);
mat3f mat3f_inverse(mat3f m);
void mat3f_print(const char* name, mat3f m);

// ===== mat4f =====
mat4f mat4f_identity(void);
mat4f mat4f_from_vec4fs(vec4f r0, vec4f r1, vec4f r2, vec4f r3);
vec4f mat4f_mul_vec4f(mat4f m, vec4f v);
mat4f mat4f_mul_mat4f(mat4f lhs, mat4f rhs);
mat4f mat4f_transpose(mat4f m);
void mat4f_print(const char* name, mat4f m);

#define vec2f(...) (vec2f){__VA_ARGS__}
#define vec3f(...) (vec3f){__VA_ARGS__}
#define vec4f(...) (vec4f){__VA_ARGS__}

#ifdef LALGBR_IMPL

// ===== float numbers functions =====

float sqrf(float val)
{
    return val * val;
}

// ===== vec2f =====

vec2f vec2f_add(vec2f lhs, vec2f rhs)
{
    return vec2f(lhs.x + rhs.x, lhs.y + rhs.y);
}

vec2f vec2f_sub(vec2f lhs, vec2f rhs)
{
    return vec2f(lhs.x - rhs.x, lhs.y - rhs.y);
}

vec2f vec2f_mul(vec2f v, float val)
{
    return vec2f(v.x * val, v.y * val);
}

vec2f vec2f_div(vec2f v, float val)
{
    return vec2f_mul(v, 1 / val);
}

vec2f vec2f_norm(vec2f v)
{
    float len = vec2f_len(v);
    assert(len > 0);

    return vec2f(v.x / len, v.y / len);
}

vec2f vec2f_neg(vec2f v)
{
    return vec2f(-v.x, -v.y);
}

float vec2f_dot(vec2f lhs, vec2f rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float vec2f_sqrlen(vec2f v)
{
    return sqrf(v.x) + sqrf(v.y);
}

float vec2f_len(vec2f v)
{
    return sqrtf(vec2f_sqrlen(v));
}

void vec2f_print(const char* name, vec2f v)
{
    printf("%s = (%f, %f)\n", name, v.x, v.y);
}

// ===== vec3f =====

vec3f vec3f_add(vec3f lhs, vec3f rhs)
{
    return vec3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

vec3f vec3f_sub(vec3f lhs, vec3f rhs)
{
    return vec3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

vec3f vec3f_mul(vec3f v, float val)
{
    return vec3f(v.x * val, v.y * val, v.z * val);
}

vec3f vec3f_div(vec3f v, float val)
{
    return vec3f_mul(v, 1 / val);
}

vec3f vec3f_norm(vec3f v)
{
    float len = vec3f_len(v);
    assert(len > 0);

    return vec3f(v.x / len, v.y / len, v.z / len);
}

vec3f vec3f_neg(vec3f v)
{
    return vec3f(-v.x, -v.y, -v.z);
}

vec3f vec3f_cross(vec3f lhs, vec3f rhs)
{
    mat3f minor_mat = mat3f_from_vec3fs(vec3f(0, 0, 0), lhs, rhs);

    float x = mat3f_minor(minor_mat, 0, 0); 
    float y = mat3f_minor(minor_mat, 0, 1);
    float z = mat3f_minor(minor_mat, 0, 2);

    return vec3f(x, y, z);
}

float vec3f_dot(vec3f lhs, vec3f rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float vec3f_sqrlen(vec3f v)
{
    return sqrf(v.x) + sqrf(v.y) + sqrf(v.z);
}

float vec3f_len(vec3f v)
{
    return sqrtf(vec3f_sqrlen(v));
}
    
void vec3f_print(const char* name, vec3f v)
{
    printf("%s = (%f, %f, %f)\n", name, v.x, v.y, v.z);
}

// ===== vec4f =====

vec4f vec4f_add(vec4f lhs, vec4f rhs)
{
    return vec4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

vec4f vec4f_sub(vec4f lhs, vec4f rhs)
{
    return vec4f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

vec4f vec4f_mul(vec4f v, float val)
{
    return vec4f(v.x * val, v.y * val, v.z * val, v.w * val);
}

vec4f vec4f_div(vec4f v, float val)
{
    return vec4f_mul(v, 1 / val);
}

vec4f vec4f_norm(vec4f v)
{
    float len = vec4f_len(v);
    assert(len > 0);

    return vec4f(v.x / len, v.y / len, v.z / len, v.w / len);
}

vec4f vec4f_neg(vec4f v)
{
    return vec4f(-v.x, -v.y, -v.z, -v.w);
}

float vec4f_dot(vec4f lhs, vec4f rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

float vec4f_sqrlen(vec4f v)
{
    return sqrf(v.x) + sqrf(v.y) + sqrf(v.z) + sqrf(v.w);
}

float vec4f_len(vec4f v)
{
    return sqrtf(vec4f_sqrlen(v));
}

void vec4f_print(const char* name, vec4f v)
{
    printf("%s = (%f, %f, %f, %f)\n", name, v.x, v.y, v.z, v.w);
}

// ===== mat2f

mat2f mat2f_identity(void)
{
    return (mat2f)
    {{
	{1, 0},
	{0, 1}
    }};
}

mat2f mat2f_from_vec2fs(vec2f r0, vec2f r1)
{
    return (mat2f)
    {{ 
	{r0.x, r0.y},
	{r1.x, r1.y}
    }};
}

mat2f mat2f_add(mat2f lhs, mat2f rhs)
{
    mat2f out;

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    out.m[r][c] = lhs.m[r][c] + rhs.m[r][c];
	}
    }

    return out;
}

mat2f mat2f_sub(mat2f lhs, mat2f rhs)
{
    mat2f out;

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    out.m[r][c] = lhs.m[r][c] - rhs.m[r][c];
	}
    }

    return out;
}

mat2f mat2f_mul_val(mat2f m, float val)
{
    mat2f out;

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    out.m[r][c] = m.m[r][c] * val;
	}
    }

    return out;
}

vec2f mat2f_mul_vec2f(mat2f m, vec2f v)
{
    float x, y;
    x = m.m[0][0] * v.x + m.m[0][1] * v.y;
    y = m.m[1][0] * v.x + m.m[1][1] * v.y;

    return vec2f(x, y);
}

mat2f mat2f_mul_mat2f(mat2f lhs, mat2f rhs)
{
    mat2f out = {{{ 0 }}};

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    for (int k = 0; k < 2; ++k)
	    {
		out.m[r][c] += lhs.m[r][k] * rhs.m[k][c];
	    }
	}
    }

    return out;
}

mat2f mat2f_transpose(mat2f m)
{
    mat2f out;

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    out.m[r][c] = m.m[c][r];
	}
    }

    return out;
}

float mat2f_minor(mat2f m, int r, int c)
{
    return m.m[1 - r][1 - c];
}

float mat2f_cof(mat2f m, int r, int c)
{
    int sign = ((r + c) % 2 == 0) ? 1 : -1;

    return sign * mat2f_minor(m, r, c);
}

float mat2f_det(mat2f m)
{
    float det = 0;

    for (int c = 0; c < 2; ++c)
    {
	det += m.m[0][c] * mat2f_cof(m, 0, c);
    }

    return det;
}

mat2f mat2f_adj(mat2f m)
{
    mat2f out;

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    out.m[r][c] = mat2f_cof(m, r, c);
	}
    }

    return mat2f_transpose(out);
}

mat2f mat2f_inverse(mat2f m)
{
    float det = mat2f_det(m);
    assert(det != 0);

    float inv_det = 1 / det;
    mat2f adj = mat2f_adj(m);

    return mat2f_mul_val(adj, inv_det);
}


void mat2f_print(const char* name, mat2f m)
{
    printf("%s:\n", name);

    for (int r = 0; r < 2; ++r)
    {
	for (int c = 0; c < 2; ++c)
	{
	    printf("%f ", m.m[r][c]);
	}
	putchar('\n');
    }
}

// ===== mat3f =====

mat3f mat3f_identity(void)
{
    return (mat3f)
    {{ 
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
    }};
}

mat3f mat3f_from_vec3fs(vec3f r0, vec3f r1, vec3f r2)
{
    return (mat3f)
    {{ 
	{r0.x, r0.y, r0.z},
	{r1.x, r1.y, r1.z},
	{r2.x, r2.y, r2.z}
    }};
}

mat3f mat3f_add(mat3f lhs, mat3f rhs)
{
    mat3f out;

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    out.m[r][c] = lhs.m[r][c] + rhs.m[r][c];
	}
    }

    return out;
}

mat3f mat3f_sub(mat3f lhs, mat3f rhs)
{
    mat3f out;

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    out.m[r][c] = lhs.m[r][c] - rhs.m[r][c];
	}
    }

    return out;
}

mat3f mat3f_mul_val(mat3f m, float val)
{
    mat3f out;

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    out.m[r][c] = m.m[r][c] * val;
	}
    }

    return out;
}

vec3f mat3f_mul_vec3f(mat3f m, vec3f v)
{
    float x, y, z;
    x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
    y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
    z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;

    return vec3f(x, y, z);
}

mat3f mat3f_mul_mat3f(mat3f lhs, mat3f rhs)
{
    mat3f out = {{{ 0 }}};

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    for (int k = 0; k < 3; ++k)
	    {
		out.m[r][c] += lhs.m[r][k] * rhs.m[k][c];
	    }
	}
    }

    return out;
}

mat3f mat3f_transpose(mat3f m)
{
    mat3f out;

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    out.m[r][c] = m.m[c][r];
	}
    }

    return out;
}

float mat3f_minor(mat3f m, int r0, int c0)
{
    int y = 0;
    int x = 0;
    mat2f minor_mat;
    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    if (r != r0 && c != c0)
	    {
		minor_mat.m[y][x] = m.m[r][c];

		if (++x == 2)
		{
		    x = 0;
		    ++y;
		}
	    }
	}
    }

    return mat2f_det(minor_mat);
}

float mat3f_cof(mat3f m, int r, int c)
{
    int sign = ((r + c) % 2 == 0) ? 1 : -1;

    return sign * mat3f_minor(m, r, c);
}

float mat3f_det(mat3f m)
{
    float det = 0;

    for (int c = 0; c < 3; ++c)
    {
	det += m.m[0][c] * mat3f_cof(m, 0, c);
    }

    return det;
}

mat3f mat3f_adj(mat3f m)
{
    mat3f out;

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    out.m[r][c] = mat3f_cof(m, r, c);
	}
    }

    return mat3f_transpose(out);
}

mat3f mat3f_inverse(mat3f m)
{
    float det = mat3f_det(m);
    assert(det != 0);

    float inv_det = 1 / det;
    mat3f adj = mat3f_adj(m);

    return mat3f_mul_val(adj, inv_det);
}


void mat3f_print(const char* name, mat3f m)
{
    printf("%s:\n", name);

    for (int r = 0; r < 3; ++r)
    {
	for (int c = 0; c < 3; ++c)
	{
	    printf("%f ", m.m[r][c]);
	}
	putchar('\n');
    }
}

// ===== mat3f =====

mat4f mat4f_identity(void)
{
    return (mat4f)
    {{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
    }};
}

mat4f mat4f_from_vec4fs(vec4f r0, vec4f r1, vec4f r2, vec4f r3)
{
    return (mat4f)
    {{
	{r0.x, r0.y, r0.z, r0.w},
	{r1.x, r1.y, r1.z, r1.w},
	{r2.x, r2.y, r2.z, r2.w},
	{r3.x, r3.y, r3.z, r3.w}
    }};
}

vec4f mat4f_mul_vec4f(mat4f m, vec4f v)
{
    float product[4];

    for (int i = 0; i < 4; ++i)
    {
	float a = m.m[i][0] * v.x;
	float b = m.m[i][1] * v.y;
	float c = m.m[i][2] * v.z;
	float d = m.m[i][3] * v.w;

	product[i] = a + b + c + d;
    }

    return vec4f(product[0], product[1], product[2], product[3]);
}

mat4f mat4f_mul_mat4f(mat4f lhs, mat4f rhs)
{
    mat4f out = {{{ 0 }}};

    for (int r = 0; r < 4; ++r)
    {
	for (int c = 0; c < 4; ++c)
	{
	    for (int ind = 0; ind < 4; ++ind)
	    {
		out.m[r][c] += lhs.m[r][ind] * rhs.m[ind][c];
	    }
	}
    }

    return out;
}

mat4f mat4f_transpose(mat4f m)
{
    mat4f out = {{{ 0 }}};

    for (int r = 0; r < 4; ++r)
    {
	for (int c = 0; c < 4; ++c)
	{
	    out.m[r][c] = m.m[c][r];
	}
    }

    return out;
}

void mat4f_print(const char* name, mat4f m)
{
    printf("%s:\n", name);
    for (int r = 0; r < 4; ++r)
    {
	for (int c = 0; c < 4; ++c)
	{
	    printf("%f ", m.m[r][c]);
	}
	putchar('\n');
    }
}

#endif

#endif
