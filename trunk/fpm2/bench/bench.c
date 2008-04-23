/* ------------------------------------------------------------------------- */

/* FPM Benchmark Program
 *
 * Copyright (C) 2008 by Ivo van Poorten
 *
 * License: LGPL v2.1
 */

/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

#include "fpm/fpm.h"

#ifndef HAVE_RDTSC
#include <sys/time.h>
#include <time.h>
#endif

/* ------------------------------------------------------------------------- */

#define OUTER   10
#define LOOP    1000000

/* ------------------------------------------------------------------------- */

#if defined(DOFLOAT)

#   define FPTYPE       float
#   define FPFROMI(a)   ((float)(a))
#   define FPFROMF(a)   (a)
#   define FPFROMD(a)   ((float)(a))
#   define FPTOI(a)     ((int)(a))
#   define FPTOF(a)     (a)
#   define FPTOD(a)     ((double)(a))
#   define FPMUL(a,b)   (a*b)
#   define FPDIV(a,b)   (a/b)
#   define FPSQRT(a)    sqrt(a)

#elif defined(DODOUBLE)

#   define FPTYPE       double
#   define FPFROMI(a)   ((double)(a))
#   define FPFROMF(a)   ((double)(a))
#   define FPFROMD(a)   (a)
#   define FPTOI(a)     ((int)(a))
#   define FPTOF(a)     ((float)(a))
#   define FPTOD(a)     (a)
#   define FPMUL(a,b)   (a*b)
#   define FPDIV(a,b)   (a/b)
#   define FPSQRT(a)    sqrt(a)

#elif defined(DOFP8P8)

#   define FPTYPE       fp8p8_t
#   define FPFROMI(a)   itofp8p8(a)
#   define FPFROMF(a)   ftofp8p8(a)
#   define FPFROMD(a)   dtofp8p8(a)
#   define FPTOI(a)     fp8p8toi(a)
#   define FPTOF(a)     fp8p8tof(a)
#   define FPTOD(a)     fp8p8tod(a)
#   define FPMUL(a,b)   mulfp8p8(a,b)
#   define FPDIV(a,b)   divfp8p8(a,b)
#   define FPSQRT(a)    sqrtfp8p8(a)

#elif defined(DOFP24P8)

#   define FPTYPE       fp24p8_t
#   define FPFROMI(a)   itofp24p8(a)
#   define FPFROMF(a)   ftofp24p8(a)
#   define FPFROMD(a)   dtofp24p8(a)
#   define FPTOI(a)     fp24p8toi(a)
#   define FPTOF(a)     fp24p8tof(a)
#   define FPTOD(a)     fp24p8tod(a)
#   define FPMUL(a,b)   mulfp24p8(a,b)
#   define FPDIV(a,b)   divfp24p8(a,b)
#   define FPSQRT(a)    sqrtfp24p8(a)

#elif defined(DOFP16P16)

#   define FPTYPE       fp16p16_t
#   define FPFROMI(a)   itofp16p16(a)
#   define FPFROMF(a)   ftofp16p16(a)
#   define FPFROMD(a)   dtofp16p16(a)
#   define FPTOI(a)     fp16p16toi(a)
#   define FPTOF(a)     fp16p16tof(a)
#   define FPTOD(a)     fp16p16tod(a)
#   define FPMUL(a,b)   mulfp16p16(a,b)
#   define FPDIV(a,b)   divfp16p16(a,b)
#   define FPSQRT(a)    sqrtfp16p16(a)

#elif defined(DOFP8P24)

#   define FPTYPE       fp8p24_t
#   define FPFROMI(a)   itofp8p24(a)
#   define FPFROMF(a)   ftofp8p24(a)
#   define FPFROMD(a)   dtofp8p24(a)
#   define FPTOI(a)     fp8p24toi(a)
#   define FPTOF(a)     fp8p24tof(a)
#   define FPTOD(a)     fp8p24tod(a)
#   define FPMUL(a,b)   mulfp8p24(a,b)
#   define FPDIV(a,b)   divfp8p24(a,b)
#   define FPSQRT(a)    sqrtfp8p24(a)

#elif defined(DOUFP8P8)

#   define FPTYPE       ufp8p8_t
#   define FPFROMI(a)   itoufp8p8(a)
#   define FPFROMF(a)   ftoufp8p8(a)
#   define FPFROMD(a)   dtoufp8p8(a)
#   define FPTOI(a)     ufp8p8toi(a)
#   define FPTOF(a)     ufp8p8tof(a)
#   define FPTOD(a)     ufp8p8tod(a)
#   define FPMUL(a,b)   mulufp8p8(a,b)
#   define FPDIV(a,b)   divufp8p8(a,b)
#   define FPSQRT(a)    sqrtufp8p8(a)

#elif defined(DOUFP24P8)

#   define FPTYPE       ufp24p8_t
#   define FPFROMI(a)   itoufp24p8(a)
#   define FPFROMF(a)   ftoufp24p8(a)
#   define FPFROMD(a)   dtoufp24p8(a)
#   define FPTOI(a)     ufp24p8toi(a)
#   define FPTOF(a)     ufp24p8tof(a)
#   define FPTOD(a)     ufp24p8tod(a)
#   define FPMUL(a,b)   mulufp24p8(a,b)
#   define FPDIV(a,b)   divufp24p8(a,b)
#   define FPSQRT(a)    sqrtufp24p8(a)

#elif defined(DOUFP16P16)

#   define FPTYPE       ufp16p16_t
#   define FPFROMI(a)   itoufp16p16(a)
#   define FPFROMF(a)   ftoufp16p16(a)
#   define FPFROMD(a)   dtoufp16p16(a)
#   define FPTOI(a)     ufp16p16toi(a)
#   define FPTOF(a)     ufp16p16tof(a)
#   define FPTOD(a)     ufp16p16tod(a)
#   define FPMUL(a,b)   mulufp16p16(a,b)
#   define FPDIV(a,b)   divufp16p16(a,b)
#   define FPSQRT(a)    sqrtufp16p16(a)

#elif defined(DOUFP8P24)

#   define FPTYPE       ufp8p24_t
#   define FPFROMI(a)   itoufp8p24(a)
#   define FPFROMF(a)   ftoufp8p24(a)
#   define FPFROMD(a)   dtoufp8p24(a)
#   define FPTOI(a)     ufp8p24toi(a)
#   define FPTOF(a)     ufp8p24tof(a)
#   define FPTOD(a)     ufp8p24tod(a)
#   define FPMUL(a,b)   mulufp8p24(a,b)
#   define FPDIV(a,b)   divufp8p24(a,b)
#   define FPSQRT(a)    sqrtufp8p24(a)

#endif

/* ------------------------------------------------------------------------- */

static fpm_always_inline long long rdtsc()
{
#ifdef FPM_HAVE_RDTSC
    long long timestamp;
    asm volatile ("rdtsc\n" : "=A"(timestamp));
    return timestamp;
#else
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    
    return (tv.tv_sec*1000000LL + tv.tv_usec) * 1000LL;
#endif
}

static int print = 1;

static void PRINT(const char *fmt, ...) {
    va_list ap;

    if (print) {
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

/* ------------------------------------------------------------------------- */

static int llcompare(const void *p1, const void *p2) {
    long long a = *(long long *)p1;
    long long b = *(long long *)p2;
    if (a<b) return -1;
    else if (a>b) return 1;
    return 0;
}

static int fromi, fromf, fromd, toi, tof, tod, add, sub, mul, div, sqr;
#define ALL fromi = fromf = fromd = toi = tof = tod = add = sub = mul = div = sqr
#define ELSIF(a)    else if (!strcmp(*argv, #a))    a = v

static void command_line(int argc, char **argv) {
    ALL = 1;

    ++argv;
    while (--argc) {
        char f = *(*argv)++, v = f == '+';
        if (!strcmp(*argv, "all")) ALL = v;
        ELSIF(fromi);   ELSIF(fromf);   ELSIF(fromd);
        ELSIF(toi);     ELSIF(tof);     ELSIF(tod);
        ELSIF(add);     ELSIF(sub);     ELSIF(mul);     ELSIF(div);
        ELSIF(sqr);
        ELSIF(print);
        argv++;
    }
}

int main(int argc, char **argv)
{
    unsigned int i, j;
    volatile long long times[OUTER], tstart, tend, tsum;
    volatile FPTYPE a, b, c, d;
    volatile int xi;
    volatile float xf;
    volatile double xd;

    command_line(argc, argv);

#define LOOPSTART(name) \
    PRINT("%-12s : ", name); \
    for (i=0; i<OUTER; i++) { \
        tstart = rdtsc(); \
        for (j=0; j<LOOP; j++) {

#define LOOPEND \
        } \
        tend = rdtsc(); \
        assert(tend>tstart); \
        times[i] = tend - tstart; \
    } \
    /* now sort and drop fastest and slowest result when taking average */ \
    qsort(times, OUTER, sizeof(long long), llcompare); \
    for (tsum=0, i=1; i<OUTER-1; i++) { \
        tsum += times[i]; \
    } \
    tsum /= OUTER-2; \
    PRINT("%10llu\n", tsum);

    if(fromi){  LOOPSTART("FROMI")  a  = FPFROMI(xi);   LOOPEND }
    if(fromf){  LOOPSTART("FROMF")  a  = FPFROMF(xi);   LOOPEND }
    if(fromd){  LOOPSTART("FROMD")  a  = FPFROMD(xi);   LOOPEND }
    if(toi){    LOOPSTART("TOI")    xi = FPTOI(a);      LOOPEND }
    if(tof){    LOOPSTART("TOF")    xf = FPTOF(a);      LOOPEND }
    if(tod){    LOOPSTART("TOD")    xd = FPTOD(a);      LOOPEND }

    a = FPFROMF(12.3456789f);
    b = FPFROMF(98.7654321f);

    if(add){    LOOPSTART("ADD")    c = a + b;          LOOPEND }
    if(sub){    LOOPSTART("SUB")    c = a - b;          LOOPEND }
    if(mul){    LOOPSTART("MUL")    c = FPMUL(a,b);     LOOPEND }
    if(div){    LOOPSTART("DIV")    c = FPDIV(a,b);     LOOPEND }

    if(sqr){    LOOPSTART("SQRT")   c = FPSQRT(b);      LOOPEND }

    return 0;
}

/* ------------------------------------------------------------------------- */

