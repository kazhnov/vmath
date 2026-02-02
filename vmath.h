#include <stdint.h>
#include <math.h>
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

#define VM3_Eq(first, second) (VMV_Eq(first, second, 3))
#define VM3_Copy(to, from)    (VMV_Copy(to, from, 3))
void VM3_Set(float* to, float x, float y, float z);

#define VM2_ZERO {0.0f, 0.0f}
#define VM2_ONE  {1.0f, 1.0f}

// Vector3



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

void VM44_V3A3(float* pos, float* a, float* out);

void VM44_V2A1(float* pos, float angle, float* out);


//#endif
#ifdef _VMATH_IMPLEMENTATION_

// the infamous quake quick inverse square root function (Comments preserved)
float VM_InverseSqrt(float number) {
    long i;
    float x2, y;
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
    for (int i = 0; i < amount/2; i++) {
	VM2_Copy(out[i], values+2*i);
    }
}

void VM2_Unpack(float (*values)[2], uint32_t amount, float* out) {
    for (int i = 0; i < amount; i++) {
	VM2_Copy(out+2*i, values[i]);
    }    
}

_Bool VM2P_Eq(float (*first)[2], float (*second)[2], uint32_t amount) {
    for (int i = 0; i < amount; i++) {
	if (!VM2_Eq(first[i], second[i])) return 0;
    }
    return 1;
}

void VM3_Set(float* to, float x, float y, float z) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
}

_Bool VMV_Eq(float* first, float* second, uint32_t dims) {
    for (int i = 0; i < dims; i++) {
	if (first[i] != second[i]) return 0;
    }
    return 1;
}

void VMV_AddO(float* first, float* second, float* out, uint32_t dims) {
    for (int i = 0; i < dims; i++) {
	out[i] = first[i] + second[i];
    }
}

void VMV_Add(float* to, float* from, uint32_t dims) {
    for (int i = 0; i < dims; i++) {
	to[i] += from[i];
    }
}

void VMV_Copy(float* to, float* from, uint32_t dims) {
    for (int i = 0; i < dims; i++) {
	to[i] = from[i];
    }
}

// Matrix 2x2

void VM22_AddO(float* first, float* second, float* out) {
    for (int i = 0; i < 4; i++) {
	out[i] = first[i] + second[i];
    }
}

void  VM22_Add(float* to, float* from) {
    float temp[4] = {0, 0, 0, 0};
    VM22_AddO(to, from, temp);
    VM22_Copy(to, temp);
}

void VM22_SubO(float* first, float* second, float* out) {
    for (int i = 0; i < 4; i++) {
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
    for (int i = 0; i < 4; i++) {
	to[i] = from[i];
    }
}

_Bool VM22_Eq(float* first, float* second) {
    for (int i = 0; i < 4; i++) {
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
    float temp[4];
    VM22_DetO(of, temp);
    VM22_Copy(of, temp);
}


void VM4_Set(float* to, float x, float y, float z, float w) {
    to[0] = x;
    to[1] = y;
    to[2] = z;
    to[3] = w;
}

void VM44_V3A3(float* pos, float* a, float* out) {
    float s[3] = {sinf(a[0]), sinf(a[1]), sinf(a[2])};
    float c[3] = {cosf(a[0]), cosf(a[1]), cosf(a[2])};
    VM4_Set(out+0,  c[0]*c[1],  c[0]*s[1]*s[2] - s[0]*c[2],  c[0]*s[1]*c[2] + s[0]*s[2], pos[0]);
    VM4_Set(out+4,  s[0]*c[1],  s[0]*s[1]*s[2] - c[0]*c[2],  s[0]*s[1]*c[2] - c[0]*s[2], pos[1]);
    VM4_Set(out+8,      -s[1],       c[1]*s[2],                   c[1]*c[2],             pos[2]);
    VM4_Set(out+12, 0,          0,                            0,                         1     );
}

void VM44_V2A1(float* pos, float angle, float* out) {
    float s = sinf(angle);
    float c = cosf(angle);

    VM4_Set(out+0,  c, -s, 0, pos[0]);
    VM4_Set(out+4,  s,  c, 0, pos[1]);
    VM4_Set(out+8,  0,  0, 1, pos[2]);
    VM4_Set(out+12, 0,  0, 0, 1     );   
}

#endif
