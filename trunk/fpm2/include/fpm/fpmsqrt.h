/* -------------------------------------------------------------------------
 *
 * Fixed Point Math Library
 *
 * Copyright (C) 2005, 2006, 2008 by Ivo van Poorten
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 * ------------------------------------------------------------------------- */

#ifndef FPM_INTERNAL
#error "This header file should NOT be included directly!"
#else

#ifndef FPM_FPMSQRT_H
#define FPM_FPMSQRT_H

/* ------------------------------------------------------------------------- */

/* square root */

#ifndef FPM_SQUARE_ROOT_METHOD
#   define FPM_SQUARE_ROOT_METHOD 2
#endif

#if FPM_SQUARE_ROOT_METHOD == 6  || FPM_SQUARE_ROOT_METHOD == 7  || \
    FPM_SQUARE_ROOT_METHOD == 8  || FPM_SQUARE_ROOT_METHOD == 9  || \
    FPM_SQUARE_ROOT_METHOD == 10 || FPM_SQUARE_ROOT_METHOD == 11
#   ifndef FPM_HAVE_SSE
#       warning "SSE SQRT Method selected without having SSE"
#       warning "Falling back to x87 inline assembly"
#       undef FPM_SQUARE_ROOT_METHOD
#       define FPM_SQUARE_ROOT_METHOD 5
#   endif
#endif

#if FPM_SQUARE_ROOT_METHOD == 9 || FPM_SQUARE_ROOT_METHOD == 10 || \
    FPM_SQUARE_ROOT_METHOD == 11
#   ifndef FPM_HAVE_INTRINSICS
#       warning "SSE Intrinsics SQRT Method selected without having intrinsics"
#       warning "Falling back to inline assembly"
#       if FPM_SQUARE_ROOT_METHOD == 9
#           undef FPM_SQUARE_ROOT_METHOD
#           define FPM_SQUARE_ROOT_METHOD 6
#       endif
#       if FPM_SQUARE_ROOT_METHOD == 10
#           undef FPM_SQUARE_ROOT_METHOD
#           define FPM_SQUARE_ROOT_METHOD 7
#       endif
#       if FPM_SQUARE_ROOT_METHOD == 11
#           undef FPM_SQUARE_ROOT_METHOD
#           define FPM_SQUARE_ROOT_METHOD 8
#       endif
#   endif
#endif

#if FPM_SQUARE_ROOT_METHOD == 5
#   ifndef FPM_HAVE_X87
#       warning "x87 SQRT Method selected without having x87"
#       warning "Falling back to method 4 (QIII w/ integer math)"
#       undef FPM_SQUARE_ROOT_METHOD
#       define FPM_SQUARE_ROOT_METHOD 4
#   endif
#endif

#if FPM_SQUARE_ROOT_METHOD == 1
/* babylonian method */

#define FPMSQRT8p8(a,b) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register a##_t r; \
    if (b) return 0;  \
    r = x >> 2;       \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    return r; \
}
FPMSQRT8p8(fp8p8 , !x  )
FPMSQRT8p8(ufp8p8, x<=0)

#define FPMSQRT24p8(a,b) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register a##_t r; \
    if (b) return 0;  \
    r = x >> 2;       \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    return r; \
}
FPMSQRT24p8(fp24p8 , !x  )
FPMSQRT24p8(ufp24p8, x<=0)

#define FPMSQRT16p16(a,b) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register a##_t r; \
    if (b) return 0;  \
    r = x >> 2;       \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    return r; \
}
FPMSQRT16p16(fp16p16 , !x  )
FPMSQRT16p16(ufp16p16, x<=0)

#define FPMSQRT8p24(a,b) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register a##_t r; \
    if (b) return 0;  \
    r = x >> 2;       \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; r += div##a(x,r); r >>= 1; \
    r += div##a(x,r); r >>= 1; \
    return r; \
}
FPMSQRT8p24(fp8p24 , !x  )
FPMSQRT8p24(ufp8p24, x<=0)

#elif FPM_SQUARE_ROOT_METHOD == 2

/* digit-by-digit method, upper range of x is halved, result is less precise */

#define FPMSQRT(a,b,c) FPMFUNC a##_t sqrt##a(a##_t x) { \
    a##_t r = 0, s = 1<<b; \
    while (s>x) s >>= 2;   \
    while (s) {            \
        if (x >= r+s) {    \
            x -= r+s;      \
            r += s<<1;     \
        }                  \
        r >>= 1; s >>= 2;  \
    }                      \
    return r<<c;           \
}

FPMSQRT( fp8p8  , 14, 4 )   FPMSQRT(ufp8p8  , 14, 4 )
FPMSQRT( fp24p8 , 30, 4 )   FPMSQRT(ufp24p8 , 30, 4 )
FPMSQRT( fp16p16, 30, 8 )   FPMSQRT(ufp16p16, 30, 8 )
FPMSQRT( fp8p24 , 30, 12)   FPMSQRT(ufp8p24 , 30, 12)

#elif FPM_SQUARE_ROOT_METHOD == 3

/* John Carmack's Quake III algorithm with Chris Lomont's Initial Guess.
 * http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
 * Carmack: 0x5f3759df, Lomont: 0x5f375a86
 * Version for CPU's with an FPU
 */

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register union { float f; uint32_t i; } u = { .f = a##tof(x) }; \
    float xhalf = 0.5f * u.f;      \
    u.i = 0x5f375a86 - (u.i>>1); \
    u.f *= 1.5f - xhalf * u.f * u.f; \
    return fto##a(a##tof(x) * u.f);\
}

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 4

/* Same as 3 but without possibly slow float mul (depends on CPU) */

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
    register union { float f; uint32_t i; } u = { .f = a##tof(x) }; \
    register a##_t xhalf = x >> 1, y; \
    u.i = 0x5f375a86 - (u.i>>1); \
    y = fto##a(u.f); \
    y = mul##a(y, fto##a(1.5f) - mul##a(mul##a(xhalf,y),y)); \
    return mul##a(y,x); \
}

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 5

/* x87 FPU */

FPMFUNC float fpm_x87sqrt(float f) {
    asm(    "fld    %1  \n\t"
            "fsqrt      \n\t"
            "fstp   %0  \n\t"
            : "=m" (f) : "m" (f)    );
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_x87sqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 6

/* SSE sqrtss */

FPMFUNC float fpm_ssesqrt(float f) {
    asm(    "sqrtss %1,     %%xmm0  \n\t"
            "movss  %%xmm0, %0      \n\t"
            : "=m" (f) : "m" (f)    );
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 7

/* SSE rsqrtss */

FPMFUNC float fpm_ssesqrt(float f) {
    asm(    "rsqrtss    %1,     %%xmm0  \n\t"
            "rcpss      %%xmm0, %%xmm0  \n\t"
            "movss      %%xmm0, %0      \n\t"
            : "=m" (f) : "m" (f)    );
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 8

/* SSE rsqrtss (alternate version) */

FPMFUNC float fpm_ssesqrt(float f) {
    asm(    "rsqrtss    %1,     %%xmm0  \n\t"
            "mulss      %1,     %%xmm0  \n\t"
            "movss      %%xmm0, %0      \n\t"
            : "=m" (f) : "m" (f) );
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 9

/* SSE sqrtss w/ intrinsics */

#include <xmmintrin.h>

FPMFUNC float fpm_ssesqrt(float f) {
    __m128 mm;
    mm = _mm_set_ss(f);
    mm = _mm_sqrt_ss(mm);
    _mm_store_ss(&f, mm);
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 10

/* SSE rsqrtss w/ intrinsics */

#include <xmmintrin.h>

FPMFUNC float fpm_ssesqrt(float f) {
    __m128 mm;
    mm = _mm_set_ss(f);
    mm = _mm_rsqrt_ss(mm);
    mm = _mm_rcp_ss(mm);
    _mm_store_ss(&f, mm);
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#elif FPM_SQUARE_ROOT_METHOD == 11

/* SSE rsqrtss (alternate version) w/ intrinsics */

#include <xmmintrin.h>

FPMFUNC float fpm_ssesqrt(float f) {
    __m128 mm0, mm1;
    mm0 = _mm_set_ss(f);
    mm1 = _mm_rsqrt_ss(mm0);
    mm0 = _mm_mul_ss(mm0, mm1);
    _mm_store_ss(&f, mm0);
    return f;
}

#define FPMSQRT(a) FPMFUNC a##_t sqrt##a(a##_t x) { \
                                    return fto##a(fpm_ssesqrt(a##tof(x))); }

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#else
#   error "Invalid FPM_SQUARE_ROOT_METHOD"
#endif

/* ------------------------------------------------------------------------- */

#endif
#endif
