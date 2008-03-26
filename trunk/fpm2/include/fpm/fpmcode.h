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

#ifndef FPM_FPMCODE_H
#define FPM_FPMCODE_H

/* ------------------------------------------------------------------------- */

/* Internal types */

typedef union {
    float    f;
    uint32_t u32;
    uint16_t u16[2];
    uint8_t  u8[4];
} fpm_funion_t;

typedef union {
    double   d;
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t  u8[8];
} fpm_dunion_t;

/* ------------------------------------------------------------------------- */

/* CONVERSION */

/* int to fixed point */

#define FPMI2FP(a,c) FPMFUNC a##_t    ito##a (         int x) { return x c; } \
                     FPMFUNC u##a##_t itou##a(unsigned int x) { return x c; }

FPMI2FP(fp8p8  , <<8 )      FPMI2FP(fp24p8 , <<8 )
FPMI2FP(fp16p16, <<16)      FPMI2FP(fp8p24 , <<24)

/* float to fixed point */

#ifndef FPM_NO_FPU_MUL_CONVERSIONS

#define FPMF2FP(a,c) FPMFUNC a##_t    fto##a (float x) { return x * c; } \
                     FPMFUNC u##a##_t ftou##a(float x) { return x * c; }

FPMF2FP(fp8p8  ,   256.0f)      FPMF2FP(fp24p8 ,      256.0f)
FPMF2FP(fp16p16, 65536.0f)      FPMF2FP(fp8p24 , 16777216.0f)

#else

/* XXX: signed shift right does not preserve the sign bit everywhere */

#define FPMF2FP(a,b,c) a##_t fto##a(float f) { \
    fpm_funion_t x = { .f = f }; \
    a##_t fp, s = x.u8[3] >> 7;         /* extract sign XXX */      \
    x.u8[3] &= 0x7f;                    /* abs() */             \
    x.f += b;                           /* range 0.0 ... b */   \
    fp   = (x.u32 & 0x7fffff) c;        /* extract mantissa */  \
    fp  ^= -s;                          /* one's complement */  \
    return fp + s;                      /* two's complement */  \
}

FPMF2FP(fp8p8  ,   128.0f, >>8)     FPMF2FP(fp24p8 , 8388608.0f, <<8)
FPMF2FP(fp16p16, 32768.0f, <<8)     FPMF2FP(fp8p24 ,     128.0f, <<8)

#define FPMF2UFP(a,b,c) a##_t fto##a(float f) { \
    fpm_funion_t x = { .f = f }; \
    x.f += b; \
    return (x.u32 & 0x7fffff) c; \
}

FPMF2UFP(ufp8p8  ,   256.0f, >>7)   FPMF2UFP(ufp24p8 , 16777216.0f, <<9)
FPMF2UFP(ufp16p16, 65536.0f, <<9)   FPMF2UFP(ufp8p24 ,      256.0f, <<9)

#endif

/* double to fixed point */

#ifndef FPM_NO_FPU_MUL_CONVERSIONS

#define FPMD2FP(a,c) FPMFUNC a##_t    dto##a (double x) { return x * c; } \
                     FPMFUNC u##a##_t dtou##a(double x) { return x * c; }

FPMD2FP(fp8p8  ,   256.0f)      FPMD2FP(fp24p8 ,      256.0f)
FPMD2FP(fp16p16, 65536.0f)      FPMD2FP(fp8p24 , 16777216.0f)

#else

#define FPMD2FP(a,b,c) a##_t dto##a(double d) { \
    fpm_dunion_t x = { .d = d }; \
    a##_t fp, s = x.u8[7] >> 7;                 /* extract sign */      \
    x.u8[7] &= 0x7f;                            /* abs() */             \
    x.d += b;                                   /* range 0.0 ... b */   \
    fp   = (x.u64 & 0x000fffffffffffffULL) c;   /* extract mantissa */  \
    fp  ^= -s;                                  /* one's complement */  \
    return fp + s;                              /* two's complement */  \
}

FPMD2FP(fp8p8  ,   128.0, >>37)   FPMD2FP(fp24p8 , 8388608.0, >>21)
FPMD2FP(fp16p16, 32768.0, >>21)   FPMD2FP(fp8p24 ,     128.0, >>21)

#define FPMD2UFP(a,b,c) a##_t dto##a(double d) { \
    fpm_dunion_t x = { .d = d }; \
    x.d += b; \
    return (x.u64 & 0x000fffffffffffffULL) c; \
}

FPMD2UFP(ufp8p8  ,   256.0, >>36)   FPMD2UFP(ufp24p8 , 16777216.0, >>20)
FPMD2UFP(ufp16p16, 65536.0, >>20)   FPMD2UFP(ufp8p24 ,      256.0, >>20)

#endif

/* fixed point to int (truncated) */

#define FPMFP2I(a,c) FPMFUNC int a##toi (a##_t x) { return x c; } \
      FPMFUNC unsigned int u##a##toi (u##a##_t x) { return x c; }

FPMFP2I(fp8p8  , >>8 )      FPMFP2I(fp24p8 , >>8 )
FPMFP2I(fp16p16, >>16)      FPMFP2I(fp8p24 , >>24)

/* fixed point to float */

#define FPMFP2F(a,c) FPMFUNC float a##tof (a##_t x) { return x / c; } \
               FPMFUNC float u##a##tof (u##a##_t x) { return x / c; }

FPMFP2F(fp8p8  ,   256.0f)      FPMFP2F(fp24p8 ,      256.0f)
FPMFP2F(fp16p16, 65536.0f)      FPMFP2F(fp8p24 , 16777216.0f)

/* fixed point to double */

#define FPMFP2D(a,c) FPMFUNC double a##tod (a##_t x) { return x / c; } \
               FPMFUNC double u##a##tod (u##a##_t x) { return x / c; }

FPMFP2D(fp8p8  ,   256.0)       FPMFP2D(fp24p8 ,      256.0)
FPMFP2D(fp16p16, 65536.0)       FPMFP2D(fp8p24 , 16777216.0)

/* fixed point to fixed point */

#define FPMA2B(a,b,c) FPMFUNC b##_t a##to##b(a##_t x) { return x c; } \
          FPMFUNC u##b##_t u##a##to##u##b(u##a##_t x) { return x c; }

FPMA2B(fp8p8  , fp8p8  ,     )      FPMA2B(fp8p8  , fp24p8 ,     )
FPMA2B(fp8p8  , fp16p16, <<8 )      FPMA2B(fp8p8  , fp8p24 , <<16)
FPMA2B(fp24p8 , fp8p8  ,     )      FPMA2B(fp24p8 , fp24p8 ,     )
FPMA2B(fp24p8 , fp16p16, <<8 )      FPMA2B(fp24p8 , fp8p24 , <<16)
FPMA2B(fp16p16, fp8p8  , >>8 )      FPMA2B(fp16p16, fp24p8 , >>8 )
FPMA2B(fp16p16, fp16p16,     )      FPMA2B(fp16p16, fp8p24 , <<8 )
FPMA2B(fp8p24 , fp8p8  , >>16)      FPMA2B(fp8p24 , fp24p8 , >>16)
FPMA2B(fp8p24 , fp16p16, >>8 )      FPMA2B(fp8p24 , fp8p24 ,     )

/* ------------------------------------------------------------------------- */

/* BASIC MATH */

/* multiplication (x*y) */

#define FPMMUL(a,b,c) FPMFUNC a##_t mul##a(a##_t x, a##_t y){return (b)x*y>>c;}

FPMMUL( fp8p8  ,  int32_t, 8 )  FPMMUL( fp24p8 ,  int64_t, 8 )
FPMMUL( fp16p16,  int64_t, 16)  FPMMUL( fp8p24 ,  int64_t, 24)
FPMMUL(ufp8p8  , uint32_t, 8 )  FPMMUL(ufp24p8 , uint64_t, 8 )
FPMMUL(ufp16p16, uint64_t, 16)  FPMMUL(ufp8p24 , uint64_t, 24)

/* fast multiplication, less precision */

#define FPMFMUL(a,b) FPMFUNC a##_t fastmul##a(a##_t x, a##_t y) { \
    return (x>>b) * (y>>b); \
}

FPMFMUL(fp8p8, 4) FPMFMUL(fp24p8, 4) FPMFMUL(fp16p16, 8) FPMFMUL(fp8p24, 12)
FPMFMUL(ufp8p8,4) FPMFMUL(ufp24p8,4) FPMFMUL(ufp16p16,8) FPMFMUL(ufp8p24,12)

/* division (x/y) */

#define FPMDIV(a,b,c) FPMFUNC a##_t div##a(a##_t x, a##_t y) { \
    return ((b)x<<c) / y; }

FPMDIV( fp8p8  ,  int32_t, 8 )  FPMDIV( fp24p8 ,  int64_t, 8 )
FPMDIV( fp16p16,  int64_t, 16)  FPMDIV( fp8p24 ,  int64_t, 24)
FPMDIV(ufp8p8  , uint32_t, 8 )  FPMDIV(ufp24p8 , uint64_t, 8 )
FPMDIV(ufp16p16, uint64_t, 16)  FPMDIV(ufp8p24 , uint64_t, 24)

/* fast division, less precision, smaller range, perhaps not that useful */

#define FPMFDIV(a,b,c) FPMFUNC a##_t fastdiv##a(a##_t x, a##_t y) { \
    return ((x<<b) / y) << c; }

FPMFDIV( fp8p8  , 4, 4 )    FPMFDIV( fp24p8 , 8, 0 )
FPMFDIV( fp16p16, 8, 8 )    FPMFDIV( fp8p24 , 4, 20)
FPMFDIV(ufp8p8  , 4, 4 )    FPMFDIV(ufp24p8 , 8, 0 )
FPMFDIV(ufp16p16, 8, 8 )    FPMFDIV(ufp8p24 , 4, 20)

/* ------------------------------------------------------------------------- */

/* ADVANCED MATH */

/* square root */

#ifndef FPM_SQUARE_ROOT_METHOD
#   define FPM_SQUARE_ROOT_METHOD 2
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
    float xhalf = 0.5f * x;      \
    u.i = 0x5f375a86 - (u.i>>1); \
    return fto##a(u.f * (1.5f - xhalf * u.f * u.f)); \
}

FPMSQRT( fp8p8  )   FPMSQRT(ufp8p8  )   FPMSQRT( fp24p8 )   FPMSQRT(ufp24p8 )
FPMSQRT( fp16p16)   FPMSQRT(ufp16p16)   FPMSQRT( fp8p24 )   FPMSQRT(ufp8p24 )

#else
#   error "Invalid FPM_SQUARE_ROOT_METHOD"
#endif

/* ------------------------------------------------------------------------- */

#endif
#endif
