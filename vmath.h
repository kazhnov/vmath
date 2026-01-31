//#ifndef _VMATH_H_
//#define _VMATH_H_

// Vectors are arrays of floats
// i.e. Vec2 float[2]
// i.e. Vec3 float[3]
//
// O-functions Output result to the last argument
// other functions either return value or
// output it into the first argument

// Vector2
void  VM2_AddO(float*, float*, float* out);
void  VM2_Add(float* to, float*);

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

void  VM2_Copy(float* to, float* from);
_Bool VM2_Eq(float*, float*);
void VM2_Set(float*, float, float);


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

//#endif
#ifdef _VMATH_IMPLEMENTATION_

void VM2_AddO(float* first, float* second, float* out) {
    out[0] = first[0] + second[0];
    out[1] = first[1] + second[1];
}

void VM2_Add(float* first, float* second) {
    float temp[2];
    VM2_AddO(first, second, temp);
    VM2_Copy(first, temp);
}

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

void VM2_Copy(float* first, float* second) {
    first[0] = second[0];
    first[1] = second[1];
}

_Bool VM2_Eq(float* first, float* second) {
    return first[0] == second[0] && first[1] == second[1];
}

void VM2_Set(float* to, float x, float y) {
    to[0] = x;
    to[1] = y;
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



#endif
