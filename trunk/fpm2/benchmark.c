/* ------------------------------------------------------------------------- */

/*
 * Fixed Point Math Macro Library - Benchmark
 *
 * (C)2005,2006 by Ivo van Poorten
 * Licensed under version 2 of the GPL
 *
 * $Id$
 *
 */

/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "fpm/fpm.h"

#ifndef HAVE_RDTSC
#include <sys/time.h>
#include <time.h>
#endif

/* ------------------------------------------------------------------------- */

#define INNERLOOP   10000
#define OUTERLOOP   1000        /* adjust for slower machines */
#define VAL1        2.9
#define VAL2        213
#define VAL3        3.1

/* ------------------------------------------------------------------------- */

static inline long long rdtsc()
{
#ifdef HAVE_RDTSC
    long long timestamp;
    asm volatile ("rdtsc\n" : "=A"(timestamp));
    return timestamp;
#else
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    
    return tv.tv_sec*1000000L + tv.tv_usec;
#endif
}

/* ------------------------------------------------------------------------- */

#define timeloop(AVG, CODE) \
    do { \
        sum = (uint64_t) 0; \
        for (j=0; j<OUTERLOOP; j++) { \
            start = rdtsc(); \
            for (i=0; i<INNERLOOP; i++) { \
                CODE; \
            } \
            end = rdtsc(); \
            sum += (end-start); \
        } \
        AVG = sum / OUTERLOOP; \
    } while(0)

#define NINEi "%i %i %i %i %i %i %i %i %i\n"

#define printreport(HEADER, a) \
    do { \
        printf("#"HEADER"\n"); \
        num=a*10; \
        printf(NINEi, num++, 0, 0, 0, 0, 0, 0, 0, 0); \
        printf(NINEi, num++, 0, prca, 0, 0, 0, 0, 0, 0); \
        printf(NINEi, num++, 0, 0, prcb, 0, 0, 0, 0, 0); \
        printf(NINEi, num++, 0, 0, 0, prcc, 0, 0, 0, 0); \
        printf(NINEi, num++, 0, 0, 0, 0, prcd, 0, 0, 0); \
        printf(NINEi, num++, 0, 0, 0, 0, 0, prcf, 0, 0); \
        printf(NINEi, num++, 0, 0, 0, 0, 0, 0, prcg, 0); \
        printf(NINEi, num++, 0, 0, 0, 0, 0, 0, 0, 0); \
        printf("\n"); \
        fflush(stdout); \
        fprintf(stderr, "#"HEADER"\n"); \
        fprintf(stderr, "# %-10s - % 4i%%\n", "fp8p8_t", prca); \
        fprintf(stderr, "# %-10s - % 4i%%\n", "fp24p8_t", prcb); \
        fprintf(stderr, "# %-10s - % 4i%%\n", "fp16p16_t", prcc); \
        fprintf(stderr, "# %-10s - % 4i%%\n", "fp8p24_t", prcd); \
        fprintf(stderr, "# %-10s - % 4i%%\n", "float", prcf); \
        fprintf(stderr, "# %-10s - % 4i%%\n\n", "double", prcg); \
        fflush(stderr); \
    } while(0)

#define calcperc(PRC, AVG, AVGR) \
    do { \
        PRC = (AVG*100)/(AVGR?AVGR:1); \
    } while(0)

#define calcallperc \
    do { \
        calcperc(prca, avga, avgf); \
        calcperc(prcb, avgb, avgf); \
        calcperc(prcc, avgc, avgf); \
        calcperc(prcd, avgd, avgf); \
        calcperc(prcf, avgf, avgf); \
        calcperc(prcg, avgg, avgf); \
    } while(0)

/* ------------------------------------------------------------------------- */

/* There's a foobar timeloop between the fp8p8 add/sub test and fp24p8 test,
 * because somehow (can anybody explain?) one needs to "kick" the CPU out of
 * 16-bit short int mode */

int main(int argc, char **argv)
{
    unsigned int i, j, num;
    volatile ufp8p8_t   a1, a2, a3, a4;
    volatile ufp24p8_t  b1, b2, b3, b4;
    volatile ufp16p16_t c1, c2, c3, c4;
    volatile ufp8p24_t  d1, d2, d3, d4;
    volatile float      f1, f2, f3, f4;
    volatile double     g1, g2, g3, g4;
    volatile uint64_t   start, end, sum;
    uint64_t   avga, avgb, avgc, avgd, avgf, avgg;
    int        prca, prcb, prcc, prcd, prcf, prcg;
    int        foo, bar;
    int        doall, doadd, dosub, domul, dodiv, dosqrt;

    doall = doadd = dosub = domul = dodiv = dosqrt = 0;

#define ELSIF(a) else if (!strcmp(*argv, #a)) do##a = 1
    argv++;
    while (--argc) {
        if (0) ; ELSIF(add); ELSIF(sub); ELSIF(mul); ELSIF(div); ELSIF(sqrt);
    }
    if (doall)
        doadd = dosub = domul = dodiv = dosqrt = 1;

    a2 = dtoufp8p8(VAL1);
    b2 = dtoufp24p8(VAL1);
    c2 = dtoufp16p16(VAL1);
    d2 = dtoufp8p24(VAL1);
    f2 = VAL1;
    g2 = VAL1;

    a3 = dtoufp8p8(VAL2);
    b3 = dtoufp24p8(VAL2);
    c3 = dtoufp16p16(VAL2);
    d3 = dtoufp8p24(VAL2);
    f3 = VAL2;
    g3 = VAL2;

    a4 = dtoufp8p8(VAL3);
    b4 = dtoufp24p8(VAL3);
    c4 = dtoufp16p16(VAL3);
    d4 = dtoufp8p24(VAL3);
    f4 = VAL3;
    g4 = VAL3;

  if (doadd) {
    /* ADD */

    timeloop(avga, a1=a2+a3);
    timeloop(foo, bar=bar);
    timeloop(avgb, b1=b2+b3);
    timeloop(avgc, c1=c2+c3);
    timeloop(avgd, d1=d2+d3);
    timeloop(avgf, f1=f2+f3);
    timeloop(avgg, g1=g2+g3);
    calcallperc;
    printreport("ADD", 0);
  }

  if (dosub) {
    /* SUB */

    timeloop(avga, a1=a2-a3);
    timeloop(foo, bar=bar);
    timeloop(avgb, b1=b2-b3);
    timeloop(avgc, c1=c2-c3);
    timeloop(avgd, d1=d2-d3);
    timeloop(avgf, f1=f2-f3);
    timeloop(avgg, g1=g2-g3);
    calcallperc;
    printreport("SUB", 1);
  }

  if (domul) {
    /* MUL */

    timeloop(avga, a1=mulufp8p8(a2,a3)  );
    timeloop(avgb, b1=mulufp24p8(b2,b3) );
    timeloop(avgc, c1=mulufp16p16(c2,c3));
    timeloop(avgd, d1=mulufp8p24(d2,d3) );
    timeloop(avgf, f1=f2*f3);
    timeloop(avgg, g1=g2*g3);
    calcallperc;
    printreport("MUL", 2);
  }

  if (dodiv) {
    /* DIV */

    timeloop(avga, a1=divufp8p8(a2,a3)  );
    timeloop(avgb, b1=divufp24p8(b2,b3) );
    timeloop(avgc, c1=divufp16p16(c2,c3));
    timeloop(avgd, d1=divufp8p24(d2,d3) );
    timeloop(avgf, f1=f2/f3);
    timeloop(avgg, g1=g2/g3);
    calcallperc;
    printreport("DIV", 3);
  }

  if (dosqrt) {
    /* SQRT */

    timeloop(avga, a1=sqrtufp8p8(a2)  );
    timeloop(avgb, b1=sqrtufp24p8(b2) );
    timeloop(avgc, c1=sqrtufp16p16(c2));
    timeloop(avgd, d1=sqrtufp8p24(d2) );
    timeloop(avgf, f1=sqrt(f2));
    timeloop(avgg, g1=sqrt(g2));
    calcallperc;
    printreport("SQRT", 4);
  }

#if 0
    /* EXP */

    timeloop(avga, a1=expufp8p8(a2)  );
    timeloop(avgb, b1=expufp24p8(b2) );
    timeloop(avgc, c1=expufp16p16(c2));
    timeloop(avgd, d1=expufp8p24(d2) );
    timeloop(avgf, f1=exp(f2));
    timeloop(avgg, g1=exp(g2));
    calcallperc;
    printreport("EXP", 5);

    /* LN */

    timeloop(avga, a1=lnufp8p8(a3)  );
    timeloop(avgb, b1=lnufp24p8(b3) );
    timeloop(avgc, c1=lnufp16p16(c3));
    timeloop(avgd, d1=lnufp8p24(d3) );
    timeloop(avgf, f1=log(f3));
    timeloop(avgg, g1=log(g3));
    calcallperc;
    printreport("LN", 6);

    /* POW */

    timeloop(avga, a1=powufp8p8(a3,a4)  );
    timeloop(avgb, b1=powufp24p8(b3,b4) );
    timeloop(avgc, c1=powufp16p16(c3,c4));
    timeloop(avgd, d1=powufp8p24(d3,d4) );
    timeloop(avgf, f1=pow(f3,f4));
    timeloop(avgg, g1=pow(g3,g4));
    calcallperc;
    printreport("POW", 7);
#endif
    return 0;
}

/* ------------------------------------------------------------------------- */

