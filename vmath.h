#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
//#ifndef _VMATH_H_
//#define _VMATH_H_

// Vectors are arrays of floats
// i.e. Vec2 float[2]
// i.e. Vec3 float[3]
//
// O-functions Output result to the last argument
// other functions either return value or
// output it into the first argument

// Scalar
float VM_InverseSqrt(float);
#define V_PI (3.1415926535)


// Variable Vectors
_Bool VMV_Eq(float* first, float* second, uint32_t dims);
void VMV_Copy(float* first, float* second, uint32_t dims);
void VMV_AddO(float* first, float* second, float* out, uint32_t dims);
void VMV_Add(float* to, float* from, uint32_t dims);


// Vector2
#define VM2_AddO(first, second, out) (VMV_AddO(first, second, out, 2))
#define VM2_Add(to, from)            (VMV_Add(to, from, 2))

void  VM2_SubO(float*, float*, float* out);
void  VM2_Sub(float* to, float*);

void  VM2_ScaleO(float*, float, float* out);
void  VM2_Scale(float* to, float);

void  VM2_DotO(float*, float*, float* out);
float VM2_Dot(float*, float*);

void  VM2_AreaO(float*, float*, float* out);
float VM2_Area(float*, float*);

void  VM2_LengthO(float*, float*);
float VM2_Length(float*);

float VM2_LengthSquared(float*);
float VM2_InverseLength(float*);

void VM2_RotateO(float*, float, float* out);
void VM2_Rotate(float*, float);

//void  VM2_Copy(float* to, float* from);
#define VM2_Copy(to, from) (VMV_Copy(to, from, 2))
_Bool VM2_Eq(float*, float*);

void VM2_Set(float*, float, float);

void VM2_Pack(float* values, uint32_t amount, float (*out)[2]);
void VM2_Unpack(float (*values)[2], uint32_t amount, float* out);
_Bool VM2P_Eq(float (*first)[2], float (*second)[2], uint32_t amount);

#define VM3_AddO(first, second, out)   (VMV_AddO(first, second, out, 3))
#define VM3_Add(first, second)         (VMV_Add(first, second, 3))
#define VM3_SubtractO(first, second, out) (VMV_SubtractO(first, second, out, 3))
#define VM3_Subtract(first, second)       (VMV_Subtract(first, second, 3))
#define VM3_ScaleO(first, second, out) (VMV_ScaleO(first, second, out, 3))
#define VM3_Scale(first, second)       (VMV_Scale(first, second, 3))
#define VM3_Eq(first, second) (VMV_Eq(first, second, 3))
#define VM3_Copy(to, from)    (VMV_Copy(to, from, 3))
void VM3_Set(float* to, float x, float y, float z);

#define VM2_ZERO {0.0f, 0.0f}
#define VM2_ONE  {1.0f, 1.0f}

// Vector3
void VM3_RotateY(float *vec, float angle);


// Matrix 2x2
void  VM22_AddO(float*, float*, float* out);
void  VM22_Add(float* to, float*);

void  VM22_SubO(float* from, float*, float* out);
void  VM22_Sub(float* to, float*);

void  VM22_ScaleO(float*, float, float* out);
void  VM22_Scale(float*, float);

void  VM22_Copy(float* to, float* from);
_Bool VM22_Eq(float*, float*);

void  VM22_Transform(float* vec, float* mat);
void  VM22_TransformO(float* vec, float* mat, float* out);
void  VM22_Identity(float*);
void  VM22_InverseO(float*, float* out);
void  VM22_Inverse(float*);
void  VM22_DetO(float*, float* out);
float VM22_Det(float*);
void  VM22_Set(float*, float, float, float, float);


#define VM22_IDENTITY {1.0, 0.0, \
                        0.0, 1.0}

#define VM44_IDENTITY {\
    1, 0, 0, 0,	       \
	0, 1, 0, 0,    \
	0, 0, 1, 0,    \
	0, 0, 0, 1}

#define VM44_Copy(to, from) VMV_Copy(to, from, 16)

bool VM44_InverseO(float* mat, float* o);

bool VM44_Inverse(float* mat);

void VM44_Translate(float* mat, float* pos);

void VM44_Scale(float* mat, float* scale);

void VM44_Rotate(float* mat, float* a);

void VM44_V3A3(float* pos, float* a, float* out);

void VM44_V2A1(float* pos, float angle, float* out);

void VM44_ProjectionPerspective(float* mat, float fov, float aratio, float near, float far);

void VM44_Debug(float* mat);

//#endif
#ifdef _VMATH_IMPLEMENTATION_

// the infamous quake quick inverse square root function (Comments preserved)
float VM_InverseSqrt(float number) {
    long i = 0;
    float x2 = 0, y = 0;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

/* void VM2_AddO(float* first, float* second, float* out) { */
/*     out[0] = first[0] + second[0]; */
/*     out[1] = first[1] + second[1]; */
/* } */

/* void VM2_Add(float* first, float* second) { */
/*     float temp[2]; */
/*     VM2_AddO(first, second, temp); */
/*     VM2_Copy(first, temp); */
/* } */

void VM2_SubO(float* first, float* second, float* out) {
    out[0] = first[0] - second[0];
    out[1] = first[1] - second[1];
}

void VM2_Sub(float* first, float* second) {
    float temp[2];
    VM2_SubO(first, second, temp);
    VM2_Copy(first, temp);
}

void VM2_ScaleO(float* first, float scale, float* out) {
    out[0] = first[0] * scale;
    out[1] = first[1] * scale;
}

void VM2_Scale(float* first, float scale) {
    float temp[2];
    VM2_ScaleO(first, scale, temp);
    VM2_Copy(first, temp);
}

float VM2_Dot(float* first, float* second) {
    return first[0]*second[0]+first[1]*second[1];
}

void VM2_DotO(float* first, float* second, float* out) {
    out[0] = VM2_Dot(first, second);
}

float VM2_Area(float* first, float* second) {
    return first[0]*second[1]-first[1]*second[0];
}

void VM2_AreaO(float* first, float* second, float* out) {
    out[0] = VM2_Area(first, second);
}

float VM2_LengthSquared(float* v) {
    return v[0]*v[0] + v[1]*v[1];
}

float VM2_InverseLength(float* v) {
    return VM_InverseSqrt(VM2_LengthSquared(v));
}

void VM2_RotateO(float* in, float angle, float* out) {
    out[0] = in[0] * cosf(angle) - in[1] * sinf(angle);
    out[1] = in[0] * sinf(angle) + in[1] * cosf(angle);
}

void VM2_Rotate(float* to, float angle) {
    float temp[2];
    VM2_RotateO(to, angle, temp);
    VM2_Copy(to, temp);
}

_Bool VM2_Eq(float* first, float* second) {
    return first[0] == second[0] && first[1] == second[1];
}

void VM2_Set(float* to, float x, float y) {
    to[0] = x;
    to[1] = y;
}

void VM2_Pack(float* values, uint32_t amount, float (*out)[2]) {
    for (uint32_t i = 0; i < amount/2; i++) {
	VM2_Copy(out[i], values+2*i);
    }
}

void VM2_Unpack(float (*values)[2], uint32_t amount, float* out) {
    for (uint32_t i = 0; i < amount; i++) {
	VM2_Copy(out+2*i, values[i]);
    }    
}

_Bool VM2P_Eq(float (*first)[2], float (*second)[2], uint32_t amount) {
    for (uint32_t i = 0; i < amount; i++) {
	if (!VM2_Eq(first[i], second[i])) return 0;
    }
    return 1;
}

void VM3_Set(float* to, float x, float y, float z) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
}

void VM3_RotateY(float *vec, float angle) {
    float temp[3];
    temp[0] = vec[0]*cosf(angle) + vec[2]*sinf(angle);
    temp[1] = vec[1];
    temp[2] = -vec[0]*sinf(angle)+ vec[2]*cosf(angle);
    VM3_Copy(vec, temp);
}

_Bool VMV_Eq(float* first, float* second, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	if (first[i] != second[i]) return 0;
    }
    return 1;
}

void VMV_AddO(float* first, float* second, float* out, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	out[i] = first[i] + second[i];
    }
}

void VMV_Add(float* to, float* from, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	to[i] += from[i];
    }
}


void VMV_SubtractO(float* first, float* second, float* out, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	out[i] = first[i] - second[i];
    }
}

void VMV_Subtract(float* first, float* second, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	first[i] -= second[i];
    }
}


void VMV_ScaleO(float* first, float second, float* out, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	out[i] = first[i] * second;
    }
}

void VMV_Scale(float* to, float from, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	to[i] *= from;
    }
}


void VMV_Copy(float* to, float* from, uint32_t dims) {
    for (uint32_t i = 0; i < dims; i++) {
	to[i] = from[i];
    }
}

// Matrix 2x2

void VM22_AddO(float* first, float* second, float* out) {
    for (uint32_t i = 0; i < 4; i++) {
	out[i] = first[i] + second[i];
    }
}

void  VM22_Add(float* to, float* from) {
    float temp[4] = {0, 0, 0, 0};
    VM22_AddO(to, from, temp);
    VM22_Copy(to, temp);
}

void VM22_SubO(float* first, float* second, float* out) {
    for (uint32_t i = 0; i < 4; i++) {
	out[i] = first[i] - second[i];
    }
}

void  VM22_Sub(float* to, float* a) {
    float temp[4] = {0, 0, 0, 0};
    VM22_AddO(to, a, temp);
    VM22_Copy(to, temp);
}

void VM22_ScaleO(float* first, float second, float* out) {
    for (int i = 0; i < 4; i++) {
	out[i] = first[i] * second;
    }
}

void  VM22_Scale(float* to, float a) {
    float temp[4] = {0, 0, 0, 0};
    VM22_ScaleO(to, a, temp);
    VM22_Copy(to, temp);
}

void  VM22_Copy(float* to, float* from) {
    for (uint32_t i = 0; i < 4; i++) {
	to[i] = from[i];
    }
}

_Bool VM22_Eq(float* first, float* second) {
    for (uint32_t i = 0; i < 4; i++) {
	if (first[i] != second[i]) return 0;
    }
    return 1;
}

void VM22_Set(float* to, float x, float y, float z, float w) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
    to[3] = w;
}

void VM22_Transform(float* vec, float* mat);
void VM22_TransformO(float* vec, float* mat, float* out);

void VM22_Identity(float* to) {
    float temp[4] = VM22_IDENTITY;
    VM22_Copy(to, temp);
}

void VM22_InverseO(float*, float* out);
void VM22_Inverse(float*);

void VM22_DetO(float* of, float* out) {
    VM2_AreaO(of, of+2, out);
}

float VM22_Det(float* of) {
    float temp;
    VM22_DetO(of, &temp);
    return temp;
}

void VM4_Set(float* to, float x, float y, float z, float w) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
    to[3] = w;
}

void VM44_MultiplyO(float* a, float* b, float* out) {
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


float VM44_Det(float* mat) {
    assert(false && "Not implemented");
    return mat[0];
}

// taken from glu library
bool VM44_InverseO(float* m, float* invOut) {
    float inv[16], det;
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

bool VM44_Inverse(float* mat) {
    float temp[16];
    float result = VM44_InverseO(mat, temp);
    VM44_Copy(mat, temp);
    return result;
}

void VM44_Translate(float* mat, float* t) {
    float translated[16] = {
	1,   0,    0,    t[0],
	0,   1,    0,    t[1],
	0,   0,    1,    t[2],
	0,   0,    0,    1
    };
    float out[16];
    VM44_MultiplyO(mat, translated, out);
    VM44_Copy(mat, out);
}

void VM44_Scale(float* mat, float* s) {
    float scaled[16] = {
	s[0], 0,   0,    0,
	0,   s[1], 0,    0,
	0,   0,    s[2], 0,
	0,   0,    0,    1
    };
    float out[16];
    VM44_MultiplyO(mat, scaled, out);
    VM44_Copy(mat, out);
}

void VM44_RotateX(float* mat, float a) {
    float s = sinf(a);
    float c = cosf(a);

    float rotated[16] = {
	1,    0,    0,    0,
	0,    c,   -s,    0,
	0,    s,    c,    0,
	0,    0,    0,    1
    };
    float out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}

void VM44_RotateY(float* mat, float a) {
    float s = sinf(a);
    float c = cosf(a);
    
    float rotated[16] = {
	c,    0,    s,    0,
	0,    1,    0,    0,
       -s,    0,    c,    0,
	0,    0,    0,    1
    };
    float out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}


void VM44_RotateZ(float* mat, float a) {
    float s = sinf(a);
    float c = cosf(a);
    
    float rotated[16] = {
	c,   -s,    0,    0,
	s,    c,    0,    0,
        0,    0,    1,    0,
	0,    0,    0,    1
    };
    float out[16];
    VM44_MultiplyO(mat, rotated, out);
    VM44_Copy(mat, out);
}

void VM44_Rotate(float* mat, float* a) {
    VM44_RotateY(mat, a[1]);
    VM44_RotateX(mat, a[0]);
    VM44_RotateZ(mat, a[2]);
}

void VM44_V3A3(float* pos, float* a, float* out) {
    float matrix[16] = VM44_IDENTITY;
    VM44_Rotate(matrix, a);
    VM44_Translate(matrix, pos);
    VMV_Copy(out, matrix, 16);
}

void VM44_V2A1(float* pos, float angle, float* out) {
    float s = sinf(angle);
    float c = cosf(angle);
    
    VM4_Set(out+0,  c, -s, 0, pos[0]);
    VM4_Set(out+4,  s,  c, 0, pos[1]);
    VM4_Set(out+8,  0,  0, 1, 0     );
    VM4_Set(out+12, 0,  0, 0, 1     );   
}

void VM44_Debug(float* mat) {
    printf("MAT44\n");
    for (int i = 0; i < 16; i += 4) {
	printf("%.3f, %.3f, %.3f, %.3f\n", mat[i], mat[i+1], mat[i+2], mat[i+3]);
    }
}


void VM44_ProjectionPerspective(float* mat, float fov, float aratio, float near, float far) {
    float out[16] = {
	1./(aratio*tanf(fov/2.)), 0,                 0,                           0,
	0,                       1./(tanf(fov/2.)),  0,                           0,
	0,                       0,                -1.*(far + near)/(far - near), -2.*far*near/(far - near),
	0,                       0,                -1,                            0
    };
    VM44_Copy(mat, out);
}

#endif
