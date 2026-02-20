#include <assert.h>
#include <stdio.h>
#define _VMATH_IMPLEMENTATION_
#include "vmath.h"

void test_vectors() {
    printf("Testing Vectors.. ");
    f32 first[] =  { 1.0f, 6.0f  };
    f32 second[] = { 2.0f, 4.0f  };
    f32 expected[] = { 3.0f, 10.0f };
    f32 result[2];
    VM2_AddO(first, second, result);
    assert(VM2_Eq(result, expected));

    expected[0] = 5.0f; expected[1] = 30.0f;
    VM2_ScaleO(first, 5.0, result);
    assert(VM2_Eq(result, expected));

    f32 d_from[] = {1.0, 1.0, 2.0};
    f32 d_to[] = {4.0, 5.0, 2.0};
    assert(VM3_Distance(d_from, d_to) == 5.0);
    printf("%f\n", VM3_Distance(d_from, d_to));
    
    printf("OK\n");
}

void test_vectors_packed() {
    printf("Testing Packed Vectors.. ");
    f32 unpacked[6] =  {  1.0f, 6.0f,   3.0f, 4.0f,   5.0f, 6.0f  };
    f32 packed[3][2] = { {1.0f, 6.0f}, {3.0f, 4.0f}, {5.0f, 6.0f} };
    f32 result_p[3][2];
    f32 result_up[6];

    VM2_Pack(unpacked, 6, result_p);
    assert(VM2P_Eq(result_p, packed, 3));

    VM2_Unpack(packed, 3, result_up);
    assert(VMV_Eq(result_up, unpacked, 6));
    printf("OK\n");
}

void test_matricies() {
    printf("Testing Matricies.. ");
    f32 first[4] = VM22_IDENTITY;
    f32 second[4] = { 1.0, 2.0, 3.0, 4.0 };
    f32 expected[4] = {2.0, 2.0, 3.0, 5.0};
    f32 result[4];

    VM22_AddO(first, second, result);
    assert(VM22_Eq(result, expected));

    VM22_ScaleO(first, 2, result);
    VM22_Set(expected, 2., 0., 0., 2.);
    assert(VM22_Eq(result, expected));
    

    f32 matrix[16] = VM44_IDENTITY;
    f32 t[3] = {1, 2, 3};
    f32 a[3] = {3.14159265, 0, 3.14159265};
    VM44_Rotate(matrix, a);
    VM44_Translate(matrix, t);


    printf("OK\n");

    f32 matrix1[16] = {
	 1, 2, 4, 4,
	 5, 57, 12, 8,
	 9,10,23,12,
	13,14,15,15
    };
    f32 out[16];
    
    VM44_InverseO(matrix1, out);
    VM44_Debug(out);
}


int main() {
    test_vectors();
    test_matricies();
    test_vectors_packed();
}
