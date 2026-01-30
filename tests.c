#include <assert.h>
#define _VMATH_IMPLEMENTATION_
#include "vmath.h"

int main() {
    float first[] =  { 1.0f, 6.0f  };
    float second[] = { 2.0f, 4.0f  };
    float expected[] = { 3.0f, 10.0f };
    float result[2];
    VM2_AddO(first, second, result);
    assert(VM2_Eq(result, expected));

    expected[0] = 5.0f; expected[1] = 30.0f;
    VM2_ScaleO(first, 5.0, result);
    assert(VM2_Eq(result, expected));
    
}
