#ifdef TEST_INTRINSICS
#include <xmmintrin.h>
#endif

#ifdef TEST_ALWAYS_INLINE
static __attribute__((always_inline)) inline foo(int a) {
    return a+a;
}
#endif

int main(int argc, char **argv) {
    volatile float f = 9.0f;

#ifdef TEST_X87
    asm("fld %1\n\tfsqrt\n\tfstp %0\n\t" : "=m" (f) : "m" (f) );
#endif

#ifdef TEST_SSE
    asm("sqrtss %1, %%xmm0\n\tmovss %%xmm0, %0\n\t" : "=m" (f) : "m" (f) );
#endif

#ifdef TEST_INTRINSICS
    __m128 mm;
    mm = _mm_set_ss(f);
    mm = _mm_sqrt_ss(mm);
    _mm_store_ss(&f, mm);
#endif

#ifdef TEST_ALWAYS_INLINE
    return foo(f);
#else
    return f;
#endif
}
