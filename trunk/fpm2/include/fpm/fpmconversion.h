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

#ifndef FPM_FPMCONVERSION_H
#define FPM_FPMCONVERSION_H

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

#define FPMF2FP(a,b,c) a##_t fto##a(float f) { \
    fpm_funion_t x = { .f = f }; \
    a##_t fp, s = x.u8[3] >> 7;         /* extract sign */      \
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

#endif
#endif
