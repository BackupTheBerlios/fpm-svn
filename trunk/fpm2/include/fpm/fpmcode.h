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

/* CONVERSION */

/* int to fixed point */

#define FPMI2FP(a,c) FPMFUNC a##_t    ito##a (         int x) { return x c; } \
                     FPMFUNC u##a##_t itou##a(unsigned int x) { return x c; }

FPMI2FP(fp8p8  , <<8 )      FPMI2FP(fp24p8 , <<8 )
FPMI2FP(fp16p16, <<16)      FPMI2FP(fp8p24 , <<24)

/* float to fixed point */

#define FPMF2FP(a,c) FPMFUNC a##_t    fto##a (float x) { return x * c; } \
                     FPMFUNC u##a##_t ftou##a(float x) { return x * c; }

FPMF2FP(fp8p8  , 256     )  FPMF2FP(fp24p8 , 256     )
FPMF2FP(fp16p16, 65536   )  FPMF2FP(fp8p24 , 16777216)

/* double to fixed point */

#define FPMD2FP(a,c) FPMFUNC a##_t    dto##a (double x) { return x * c; } \
                     FPMFUNC u##a##_t dtou##a(double x) { return x * c; }

FPMD2FP(fp8p8  , 256     )  FPMD2FP(fp24p8 , 256     )
FPMD2FP(fp16p16, 65536   )  FPMD2FP(fp8p24 , 16777216)

/* fixed point to int (truncated) */

#define FPMFP2I(a,c) FPMFUNC int a##toi (a##_t x) { return x c; } \
      FPMFUNC unsigned int u##a##toi (u##a##_t x) { return x c; }

FPMFP2I(fp8p8  , >>8 )      FPMFP2I(fp24p8 , >>8 )
FPMFP2I(fp16p16, >>16)      FPMFP2I(fp8p24 , >>24)

/* fixed point to float */

#define FPMFP2F(a,c) FPMFUNC float a##tof (a##_t x) { return x / c; } \
               FPMFUNC float u##a##tof (u##a##_t x) { return x / c; }

FPMFP2F(fp8p8  , 256.0     )    FPMFP2F(fp24p8 , 256.0     )
FPMFP2F(fp16p16, 65536.0   )    FPMFP2F(fp8p24 , 16777216.0)

/* fixed point to double */

#define FPMFP2D(a,c) FPMFUNC double a##tod (a##_t x) { return x / c; } \
               FPMFUNC double u##a##tod (u##a##_t x) { return x / c; }

FPMFP2D(fp8p8  , 256.0     )    FPMFP2D(fp24p8 , 256.0     )
FPMFP2D(fp16p16, 65536.0   )    FPMFP2D(fp8p24 , 16777216.0)

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

#define FPMXY8p8    fp8p8_t    x, fp8p8_t    y
#define FPMXY24p8   fp24p8_t   x, fp24p8_t   y
#define FPMXY16p16  fp16p16_t  x, fp16p16_t  y
#define FPMXY8p24   fp8p24_t   x, fp8p24_t   y
#define FPMXYu8p8   ufp8p8_t   x, ufp8p8_t   y
#define FPMXYu24p8  ufp24p8_t  x, ufp24p8_t  y
#define FPMXYu16p16 ufp16p16_t x, ufp16p16_t y
#define FPMXYu8p24  ufp8p24_t  x, ufp8p24_t  y

/* multiplication (x*y) */

FPMFUNC fp8p8_t    mulfp8p8   (FPMXY8p8   ) { return ( int32_t) x * y >> 8;  }
FPMFUNC fp24p8_t   mulfp24p8  (FPMXY24p8  ) { return ( int64_t) x * y >> 8;  }
FPMFUNC fp16p16_t  mulfp16p16 (FPMXY16p16 ) { return ( int64_t) x * y >> 16; }
FPMFUNC fp8p24_t   mulfp8p24  (FPMXY8p24  ) { return ( int64_t) x * y >> 24; }
FPMFUNC ufp8p8_t   mulufp8p8  (FPMXYu8p8  ) { return (uint32_t) x * y >> 8;  }
FPMFUNC ufp24p8_t  mulufp24p8 (FPMXYu24p8 ) { return (uint64_t) x * y >> 8;  }
FPMFUNC ufp16p16_t mulufp16p16(FPMXYu16p16) { return (uint64_t) x * y >> 16; }
FPMFUNC ufp8p24_t  mulufp8p24 (FPMXYu8p24 ) { return (uint64_t) x * y >> 24; }

/* fast multiplication, less precision */

FPMFUNC fp8p8_t    fastmulfp8p8   (FPMXY8p8   ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC fp24p8_t   fastmulfp24p8  (FPMXY24p8  ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC fp16p16_t  fastmulfp16p16 (FPMXY16p16 ) { return (x>>8 ) * (y>>8 ); }
FPMFUNC fp8p24_t   fastmulfp8p24  (FPMXY8p24  ) { return (x>>12) * (y>>12); }
FPMFUNC ufp8p8_t   fastmulufp8p8  (FPMXYu8p8  ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC ufp24p8_t  fastmulufp24p8 (FPMXYu24p8 ) { return (x>>4 ) * (y>>4 ); }
FPMFUNC ufp16p16_t fastmulufp16p16(FPMXYu16p16) { return (x>>8 ) * (y>>8 ); }
FPMFUNC ufp8p24_t  fastmulufp8p24 (FPMXYu8p24 ) { return (x>>12) * (y>>12); }

/* division (x/y) */

FPMFUNC fp8p8_t    divfp8p8   (FPMXY8p8   ) { return (( int32_t) x<<8 ) / y; }
FPMFUNC fp24p8_t   divfp24p8  (FPMXY24p8  ) { return (( int64_t) x<<8 ) / y; }
FPMFUNC fp16p16_t  divfp16p16 (FPMXY16p16 ) { return (( int64_t) x<<16) / y; }
FPMFUNC fp8p24_t   divfp8p24  (FPMXY8p24  ) { return (( int64_t) x<<24) / y; }
FPMFUNC ufp8p8_t   divufp8p8  (FPMXYu8p8  ) { return ((uint32_t) x<<8 ) / y; }
FPMFUNC ufp24p8_t  divufp24p8 (FPMXYu24p8 ) { return ((uint64_t) x<<8 ) / y; }
FPMFUNC ufp16p16_t divufp16p16(FPMXYu16p16) { return ((uint64_t) x<<16) / y; }
FPMFUNC ufp8p24_t  divufp8p24 (FPMXYu8p24 ) { return ((uint64_t) x<<24) / y; }

/* fast division, less precision, smaller range, perhaps not that useful */

FPMFUNC fp8p8_t    fastdivfp8p8   (FPMXY8p8   ) { return ((x<<4) / y) << 4;  }
FPMFUNC fp24p8_t   fastdivfp24p8  (FPMXY24p8  ) { return ((x<<8) / y);       }
FPMFUNC fp16p16_t  fastdivfp16p16 (FPMXY16p16 ) { return ((x<<8) / y) << 8;  }
FPMFUNC fp8p24_t   fastdivfp8p24  (FPMXY8p24  ) { return ((x<<4) / y) << 20; }
FPMFUNC ufp8p8_t   fastdivufp8p8  (FPMXYu8p8  ) { return ((x<<4) / y) << 4;  }
FPMFUNC ufp24p8_t  fastdivufp24p8 (FPMXYu24p8 ) { return ((x<<8) / y);       }
FPMFUNC ufp16p16_t fastdivufp16p16(FPMXYu16p16) { return ((x<<8) / y) << 8;  }
FPMFUNC ufp8p24_t  fastdivufp8p24 (FPMXYu8p24 ) { return ((x<<4) / y) << 20; }

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
    register union { float f; int i; } u = { .f = a##tof(x) }; \
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
