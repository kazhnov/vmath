#include <assert.h>
#include <stdio.h>
#define _VMATH_IMPLEMENTATION_
#include "vmath.h"

void test_vectors() {
    printf("Testing Vectors.. ");
    float first[] =  { 1.0f, 6.0f  };
    float second[] = { 2.0f, 4.0f  };
    float expected[] = { 3.0f, 10.0f };
    float result[2];
    VM2_AddO(first, second, result);
    assert(VM2_Eq(result, expected));

    expected[0] = 5.0f; expected[1] = 30.0f;
    VM2_ScaleO(first, 5.0, result);
    assert(VM2_Eq(result, expected));

    printf("OK\n");
}

void test_matricies() {
    printf("Testing Matricies.. ");
    float first[4] = VM22_IDENTITY;
    float second[4] = { 1.0, 2.0, 3.0, 4.0 };
    float expected[4] = {2.0, 2.0, 3.0, 5.0};
    float result[4];

    VM22_AddO(first, second, result);
    assert(VM22_Eq(result, expected));

    VM22_ScaleO(first, 2, result);
    VM22_Set(expected, 2., 0., 0., 2.);
    assert(VM22_Eq(result, expected));
    
    printf("OK\n");
}


int main() {
    test_vectors();
    test_matricies();
}
