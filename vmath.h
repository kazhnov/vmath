//#ifndef _VMATH_H_
//#define _VMATH_H_

// Vectors are arrays of floats
// i.e. Vec2 float[2]
// i.e. Vec3 float[3]
//
// O-functions Output result to the last argument
// other functions either return value or
// output it into the first argument

void  VM2_AddO(float*, float*, float* out);
void  VM2_Add(float*, float*);
void  VM2_SubO(float*, float*, float* out);
void  VM2_Sub(float*, float*);
void  VM2_ScaleO(float*, float, float* out);
void  VM2_Scale(float*, float);
void  VM2_DotO(float*, float*, float* out);
float VM2_Dot(float*, float*);
void  VM2_AreaO(float*, float*, float* out);
float VM2_Area(float*, float*);

//#endif
#ifdef _VMATH_IMPLEMENTATION_

void VM2_AddO(float* first, float* second, float* out) {
    out[0] = first[0] + second[0];
    out[1] = first[1] + second[1];
}

void VM2_Add(float* first, float* second) {
    first[0] += second[0];
    first[1] += second[1];
}

void VM2_SubO(float* first, float* second, float* out) {
    out[0] = first[0] - second[0];
    out[1] = first[1] - second[1];
}

void VM2_Sub(float* first, float* second) {
    first[0] -= second[0];
    first[1] -= second[1];
}

void VM2_ScaleO(float* first, float scale, float* out) {
    out[0] = first[0] * scale;
    out[1] = first[1] * scale;
}

void VM2_Scale(float* first, float scale) {
    first[0] *= scale;
    first[1] *= scale;
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

#endif
