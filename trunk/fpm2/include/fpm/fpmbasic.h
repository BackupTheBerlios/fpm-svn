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

#ifndef FPM_FPMBASIC_H
#define FPM_FPMBASIC_H

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

/* floor (round down to nearest integer) */

#define FPMFLOOR(a,b) FPMFUNC a##_t floor##a(a##_t x) { return x & b; }; \
               FPMFUNC u##a##_t flooru##a(u##a##_t x) { return x & b; };

FPMFLOOR(fp8p8  , 0xff00    )   FPMFLOOR(fp24p8 , 0xffffff00)
FPMFLOOR(fp16p16, 0xffff0000)   FPMFLOOR(fp8p24 , 0xff000000)

/* ceil (round up to nearest integer) */

#define FPMCEIL(a,b,c) FPMFUNC a##_t ceil##a(a##_t x) { return (x+b) & c; }; \
              FPMFUNC u##a##_t ceil##u##a(u##a##_t x) { return (x+b) & c; };

FPMCEIL(fp8p8  , 0x0100    ,0xff00    ) FPMCEIL(fp24p8, 0x00000100,0xffffff00)
FPMCEIL(fp16p16, 0x00010000,0xffff0000) FPMCEIL(fp8p24, 0x01000000,0xff000000)

/* fract (return fraction of fixed point value) */

#define FPMFRAC(a) FPMFUNC a##_t fract##a(a##_t x) { \
    if (x>= 0) return fractu##a(x); else return fractu##a(~x)+1; }

FPMFRAC(fp8p8) FPMFRAC(fp24p8) FPMFRAC(fp16p16) FPMFRAC(fp8p24)

FPMFUNC ufp8p8_t   fractufp8p8  (ufp8p8_t   x) { return x & 0x00ff; }
FPMFUNC ufp24p8_t  fractufp24p8 (ufp24p8_t  x) { return x & 0x000000ff; }
FPMFUNC ufp16p16_t fractufp16p16(ufp16p16_t x) { return x & 0x0000ffff; }
FPMFUNC ufp8p24_t  fractufp8p24 (ufp8p24_t  x) { return x & 0x00ffffff; }

/* ------------------------------------------------------------------------- */

#endif
#endif
