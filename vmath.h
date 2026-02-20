#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
//#ifndef _VMATH_H_
//#define _VMATH_H_

// Some typedefs
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;

typedef uint8_t  b8;
typedef uint16_t b16;
typedef uint32_t b32;
typedef uint64_t b64;

typedef size_t   usize;

// Vectors are arrays of f32s
// i.e. Vec2 f32[2]
// i.e. Vec3 f32[3]
//
// O-functions Output result to the last argument
// other functions either return value or
// output it into the first argument

// Scalar
f32 VM_InverseSqrt(f32);
#define V_PI (3.1415926535)


// Variable Vectors
bool VMV_Eq(f32* first, f32* second, u32 dims);
void VMV_Copy(f32* first, f32* second, u32 dims);
void VMV_AddO(f32* first, f32* second, f32* out, u32 dims);
void VMV_Add(f32* to, f32* from, u32 dims);
f32 VMV_Length(f32* of, u32 dims);
void VMV_NormalizeO(f32* from, f32* to, u32 dims);
void VMV_Normalize(f32* of, u32 dims);
f32 VMV_Distance(f32* of, f32* to, u32 dims);
f32 VMV_Dot(f32* a, f32* b, u32 dims);
// Vector2
#define VM2_AddO(first, second, out) (VMV_AddO(first, second, out, 2))
#define VM2_Add(to, from)            (VMV_Add(to, from, 2))

void  VM2_SubO(f32*, f32*, f32* out);
void  VM2_Sub(f32* to, f32*);

void  VM2_ScaleO(f32*, f32, f32* out);
void  VM2_Scale(f32* to, f32);

void  VM2_DotO(f32*, f32*, f32* out);
f32 VM2_Dot(f32*, f32*);

void  VM2_AreaO(f32*, f32*, f32* out);
f32 VM2_Area(f32*, f32*);

void  VM2_LengthO(f32*, f32*);
f32 VM2_Length(f32*);

f32 VM2_LengthSquared(f32*);
f32 VM2_InverseLength(f32*);

void VM2_RotateO(f32*, f32, f32* out);
void VM2_Rotate(f32*, f32);

//void  VM2_Copy(f32* to, f32* from);
#define VM2_Copy(to, from) (VMV_Copy(to, from, 2))
bool VM2_Eq(f32*, f32*);

void VM2_Set(f32*, f32, f32);

void VM2_Pack(f32* values, u32 amount, f32 (*out)[2]);
void VM2_Unpack(f32 (*values)[2], u32 amount, f32* out);
bool VM2P_Eq(f32 (*first)[2], f32 (*second)[2], u32 amount);

#define VM3_AddO(first, second, out)   (VMV_AddO(first, second, out, 3))
#define VM3_Add(first, second)         (VMV_Add(first, second, 3))
#define VM3_SubtractO(first, second, out) (VMV_SubtractO(first, second, out, 3))
#define VM3_Subtract(first, second)       (VMV_Subtract(first, second, 3))
#define VM3_ScaleO(first, second, out) (VMV_ScaleO(first, second, out, 3))
#define VM3_Scale(first, second)       (VMV_Scale(first, second, 3))
#define VM3_Eq(first, second) (VMV_Eq(first, second, 3))
#define VM3_Copy(to, from)    (VMV_Copy(to, from, 3))
#define VM3_Length(of)        (VMV_Length(of, 3))
#define VM3_Normalize(of)     (VMV_Normalize(of, 3))
#define VM3_NormalizeO(of, to) (VMV_NormalizeO(of, to, 3))
#define VM3_Distance(of, to) (VMV_Distance(of, to, 3))
#define VM3_Dot(a, b) (VMV_Dot(a, b, 3))


void VM3_Set(f32* to, f32 x, f32 y, f32 z);

#define VM2_ZERO {0.0f, 0.0f}
#define VM2_ONE  {1.0f, 1.0f}

// Vector3
void VM3_RotateY(f32 *vec, f32 angle);


// Matrix 2x2
void  VM22_AddO(f32*, f32*, f32* out);
void  VM22_Add(f32* to, f32*);

void  VM22_SubO(f32* from, f32*, f32* out);
void  VM22_Sub(f32* to, f32*);

void  VM22_ScaleO(f32*, f32, f32* out);
void  VM22_Scale(f32*, f32);

void  VM22_Copy(f32* to, f32* from);
bool VM22_Eq(f32*, f32*);

void  VM22_Transform(f32* vec, f32* mat);
void  VM22_TransformO(f32* vec, f32* mat, f32* out);
void  VM22_Identity(f32*);
void  VM22_InverseO(f32*, f32* out);
void  VM22_Inverse(f32*);
void  VM22_DetO(f32*, f32* out);
f32 VM22_Det(f32*);
void  VM22_Set(f32*, f32, f32, f32, f32);


#define VM22_IDENTITY {1.0, 0.0, \
                        0.0, 1.0}

#define VM44_IDENTITY {\
    1, 0, 0, 0,	       \
	0, 1, 0, 0,    \
	0, 0, 1, 0,    \
	0, 0, 0, 1}

#define VM44_Copy(to, from) VMV_Copy(to, from, 16)

bool VM44_InverseO(f32* mat, f32* o);

bool VM44_Inverse(f32* mat);

void VM44_Translate(f32* mat, f32* pos);

void VM44_Transpose(f32* mat);

void VM44_Scale(f32* mat, f32* scale);

void VM44_Rotate(f32* mat, f32* a);

void VM44_V3A3(f32* pos, f32* a, f32* out);

void VM44_V2A1(f32* pos, f32 angle, f32* out);

void VM44_ProjectionPerspective(f32* mat, f32 fov, f32 aratio, f32 near, f32 far);

void VM44_Debug(f32* mat);

void VM44_V3MultiplyO(f32* mat, f32 *v, f32* out);

void VM44_V3Multiply(f32* mat, f32 *v);


//#endif
#ifdef _VMATH_IMPLEMENTATION_

// the infamous quake quick inverse square root function (Comments preserved)
f32 VM_InverseSqrt(f32 number) {
    long i = 0;
    f32 x2 = 0, y = 0;
    const f32 threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil f32ing point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( f32 * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

/* void VM2_AddO(f32* first, f32* second, f32* out) { */
/*     out[0] = first[0] + second[0]; */
/*     out[1] = first[1] + second[1]; */
/* } */

/* void VM2_Add(f32* first, f32* second) { */
/*     f32 temp[2]; */
/*     VM2_AddO(first, second, temp); */
/*     VM2_Copy(first, temp); */
/* } */

void VM2_SubO(f32* first, f32* second, f32* out) {
    out[0] = first[0] - second[0];
    out[1] = first[1] - second[1];
}

void VM2_Sub(f32* first, f32* second) {
    f32 temp[2];
    VM2_SubO(first, second, temp);
    VM2_Copy(first, temp);
}

void VM2_ScaleO(f32* first, f32 scale, f32* out) {
    out[0] = first[0] * scale;
    out[1] = first[1] * scale;
}

void VM2_Scale(f32* first, f32 scale) {
    f32 temp[2];
    VM2_ScaleO(first, scale, temp);
    VM2_Copy(first, temp);
}

f32 VM2_Dot(f32* first, f32* second) {
    return first[0]*second[0]+first[1]*second[1];
}

void VM2_DotO(f32* first, f32* second, f32* out) {
    out[0] = VM2_Dot(first, second);
}

f32 VM2_Area(f32* first, f32* second) {
    return first[0]*second[1]-first[1]*second[0];
}

void VM2_AreaO(f32* first, f32* second, f32* out) {
    out[0] = VM2_Area(first, second);
}

f32 VM2_LengthSquared(f32* v) {
    return v[0]*v[0] + v[1]*v[1];
}

f32 VM2_InverseLength(f32* v) {
    return VM_InverseSqrt(VM2_LengthSquared(v));
}

void VM2_RotateO(f32* in, f32 angle, f32* out) {
    out[0] = in[0] * cosf(angle) - in[1] * sinf(angle);
    out[1] = in[0] * sinf(angle) + in[1] * cosf(angle);
}

void VM2_Rotate(f32* to, f32 angle) {
    f32 temp[2];
    VM2_RotateO(to, angle, temp);
    VM2_Copy(to, temp);
}

bool VM2_Eq(f32* first, f32* second) {
    return first[0] == second[0] && first[1] == second[1];
}

void VM2_Set(f32* to, f32 x, f32 y) {
    to[0] = x;
    to[1] = y;
}

void VM2_Pack(f32* values, u32 amount, f32 (*out)[2]) {
    for (u32 i = 0; i < amount/2; i++) {
	VM2_Copy(out[i], values+2*i);
    }
}

void VM2_Unpack(f32 (*values)[2], u32 amount, f32* out) {
    for (u32 i = 0; i < amount; i++) {
	VM2_Copy(out+2*i, values[i]);
    }    
}

bool VM2P_Eq(f32 (*first)[2], f32 (*second)[2], u32 amount) {
    for (u32 i = 0; i < amount; i++) {
	if (!VM2_Eq(first[i], second[i])) return 0;
    }
    return 1;
}

void VM3_Set(f32* to, f32 x, f32 y, f32 z) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
}

void VM3_RotateY(f32 *vec, f32 angle) {
    f32 temp[3];
    temp[0] = vec[0]*cosf(angle) + vec[2]*sinf(angle);
    temp[1] = vec[1];
    temp[2] = -vec[0]*sinf(angle)+ vec[2]*cosf(angle);
    VM3_Copy(vec, temp);
}

bool VMV_Eq(f32* first, f32* second, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	if (first[i] != second[i]) return 0;
    }
    return 1;
}

void VMV_AddO(f32* first, f32* second, f32* out, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	out[i] = first[i] + second[i];
    }
}

void VMV_Add(f32* to, f32* from, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	to[i] += from[i];
    }
}


void VMV_SubtractO(f32* first, f32* second, f32* out, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	out[i] = first[i] - second[i];
    }
}

void VMV_Subtract(f32* first, f32* second, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	first[i] -= second[i];
    }
}


void VMV_ScaleO(f32* first, f32 second, f32* out, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	out[i] = first[i] * second;
    }
}

void VMV_Scale(f32* to, f32 from, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	to[i] *= from;
    }
}


void VMV_Copy(f32* to, f32* from, u32 dims) {
    for (u32 i = 0; i < dims; i++) {
	to[i] = from[i];
    }
}

f32 VMV_Length(f32* of, u32 dims) {
    f32 length_squared = 0;
    for (u32 i = 0; i < dims; i++) {
	length_squared += of[i]*of[i];
    }
    return sqrtf(length_squared);
}

void VMV_NormalizeO(f32* from, f32* to, u32 dims) {
    f32 length = VMV_Length(from, dims);
    for (u32 i = 0; i < dims; i++) {
	to[i] = from[i]/length;
    }
}

void VMV_Normalize(f32* of, u32 dims) {
    f32 temp[dims];
    VMV_NormalizeO(of, temp, dims);
    VMV_Copy(of, temp, dims);
}

f32 VMV_Distance(f32* of, f32* to, u32 dims) {
    f32 temp[dims];
    VMV_SubtractO(of, to, temp, dims);
    return VMV_Length(temp, 3);
}

f32 VMV_Dot(f32* a, f32* b, u32 dims) {
    f32 sum = 0;
    for (u32 i = 0; i < dims; i++) {
	sum += a[i]*b[i];
    }
    return sum;
}

// Matrix 2x2

void VM22_AddO(f32* first, f32* second, f32* out) {
    for (u32 i = 0; i < 4; i++) {
	out[i] = first[i] + second[i];
    }
}

void  VM22_Add(f32* to, f32* from) {
    f32 temp[4] = {0, 0, 0, 0};
    VM22_AddO(to, from, temp);
    VM22_Copy(to, temp);
}

void VM22_SubO(f32* first, f32* second, f32* out) {
    for (u32 i = 0; i < 4; i++) {
	out[i] = first[i] - second[i];
    }
}

void  VM22_Sub(f32* to, f32* a) {
    f32 temp[4] = {0, 0, 0, 0};
    VM22_AddO(to, a, temp);
    VM22_Copy(to, temp);
}

void VM22_ScaleO(f32* first, f32 second, f32* out) {
    for (int i = 0; i < 4; i++) {
	out[i] = first[i] * second;
    }
}

void  VM22_Scale(f32* to, f32 a) {
    f32 temp[4] = {0, 0, 0, 0};
    VM22_ScaleO(to, a, temp);
    VM22_Copy(to, temp);
}

void  VM22_Copy(f32* to, f32* from) {
    for (u32 i = 0; i < 4; i++) {
	to[i] = from[i];
    }
}

bool VM22_Eq(f32* first, f32* second) {
    for (u32 i = 0; i < 4; i++) {
	if (first[i] != second[i]) return 0;
    }
    return 1;
}

void VM22_Set(f32* to, f32 x, f32 y, f32 z, f32 w) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
    to[3] = w;
}

void VM22_Transform(f32* vec, f32* mat);
void VM22_TransformO(f32* vec, f32* mat, f32* out);

void VM22_Identity(f32* to) {
    f32 temp[4] = VM22_IDENTITY;
    VM22_Copy(to, temp);
}

void VM22_InverseO(f32*, f32* out);
void VM22_Inverse(f32*);

void VM22_DetO(f32* of, f32* out) {
    VM2_AreaO(of, of+2, out);
}

f32 VM22_Det(f32* of) {
    f32 temp;
    VM22_DetO(of, &temp);
    return temp;
}

void VM4_Set(f32* to, f32 x, f32 y, f32 z, f32 w) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
    to[3] = w;
}

void VM44_MultiplyO(f32* a, f32* b, f32* out) {
    int d = 4;
    for (int i = 0; i < d*d; i++) out[i] = 0;

    for (int i = 0; i < d; i++) {
	for (int j = 0; j < d; j++) {
	    for (int k = 0; k < d; k++) {
		out[j*d+i] += a[k*d+i] * b[j*d+k];
	    }	
	}
    }
}

f32 VM44_Det(f32* mat) {
    assert(false && "Not implemented");
    return mat[0];
}

// taken from glu library
bool VM44_InverseO(f32* m, f32* invOut) {
    f32 inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

bool VM44_Inverse(f32* mat) {
    f32 temp[16];
    f32 result = VM44_InverseO(mat, temp);
    VM44_Copy(mat, temp);
    return result;
}

void VM44_Translate(f32* mat, f32* t) {
    f32 translated[16] = {
	1,   0,    0,    t[0],
	0,   1,    0,    t[1],
	0,   0,    1,    t[2],
	0,   0,    0,    1
    };
    f32 out[16];
    VM44_MultiplyO(mat, translated, out);
    VM44_Copy(mat, out);
}

void VM44_Scale(f32* mat, f32* s) {
    f32 scaled[16] = {
	s[0], 0,   0,    0,
	0,   s[1], 0,    0,
	0,   0,    s[2], 0,
	0,   0,    0,    1
    };
    f32 out[16];
    VM44_MultiplyO(mat, scaled, out);
    VM44_Copy(mat, out);
}

void VM44_Transpose(f32* mat) {
    f32 temp[16] = {
	mat[0], mat[4], mat[8], mat[12],
	mat[1], mat[5], mat[9], mat[13],
	mat[2], mat[6], mat[10], mat[14],
	mat[3], mat[7], mat[11], mat[15]
    };

    VM44_Copy(mat, temp);
}

void VM44_RotateX(f32* mat, f32 a) {
    f32 s = sinf(a);
    f32 c = cosf(a);

    f32 rotated[16] = {
	1,    0,    0,    0,
	0,    c,   -s,    0,
	0,    s,    c,    0,
	0,    0,    0,    1
    };
    f32 out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}

void VM44_RotateY(f32* mat, f32 a) {
    f32 s = sinf(a);
    f32 c = cosf(a);
    
    f32 rotated[16] = {
	c,    0,    s,    0,
	0,    1,    0,    0,
       -s,    0,    c,    0,
	0,    0,    0,    1
    };
    f32 out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}


void VM44_RotateZ(f32* mat, f32 a) {
    f32 s = sinf(a);
    f32 c = cosf(a);
    
    f32 rotated[16] = {
	c,   -s,    0,    0,
	s,    c,    0,    0,
        0,    0,    1,    0,
	0,    0,    0,    1
    };
    f32 out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}

void VM44_Rotate(f32* mat, f32* a) {
    VM44_RotateY(mat, a[1]);
    VM44_RotateX(mat, a[0]);
    VM44_RotateZ(mat, a[2]);
}

void VM44_V3A3(f32* pos, f32* a, f32* out) {
    f32 matrix[16] = VM44_IDENTITY;
    VM44_Rotate(matrix, a);
    VM44_Translate(matrix, pos);
    VMV_Copy(out, matrix, 16);
}

void VM44_V2A1(f32* pos, f32 angle, f32* out) {
    f32 s = sinf(angle);
    f32 c = cosf(angle);
    
    VM4_Set(out+0,  c, -s, 0, pos[0]);
    VM4_Set(out+4,  s,  c, 0, pos[1]);
    VM4_Set(out+8,  0,  0, 1, 0     );
    VM4_Set(out+12, 0,  0, 0, 1     );   
}

void VM44_Debug(f32* mat) {
    printf("MAT44\n");
    for (int i = 0; i < 16; i += 4) {
	printf("%.3f, %.3f, %.3f, %.3f\n", mat[i], mat[i+1], mat[i+2], mat[i+3]);
    }
}


void VM44_ProjectionPerspective(f32* mat, f32 fov, f32 aratio, f32 near, f32 far) {
    f32 out[16] = {
	1./(aratio*tanf(fov/2.)), 0,                 0,                           0,
	0,                       1./(tanf(fov/2.)),  0,                           0,
	0,                       0,                -1.*(far + near)/(far - near), -2.*far*near/(far - near),
	0,                       0,                -1,                            0
    };
    VM44_Copy(mat, out);
}

void VM44_V3MultiplyO(f32 mat[16], f32 v[3], f32 out[3]) {
    out[0] = v[0]*mat[0] + v[1]*mat[1] + v[2]*mat[2]  + mat[3];
    out[1] = v[0]*mat[4] + v[1]*mat[5] + v[2]*mat[6]  + mat[7];
    out[2] = v[0]*mat[8] + v[1]*mat[9] + v[2]*mat[10] + mat[11];
}

void VM44_V3Multiply(f32 mat[16], f32 v[3]) {
    float out[3];
    VM44_V3MultiplyO(mat, v, out);
    VM3_Copy(v, out);
}

#endif
