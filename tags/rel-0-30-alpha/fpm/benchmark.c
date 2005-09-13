/* ------------------------------------------------------------------------- */

/*
 * Fixed Point Math Macro Library - Benchmark
 *
 * (C)2005 by Ivo van Poorten
 * Licensed under version 2 of the GPL
 *
 * $Id$
 *
 */

/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>

#include "fixedpointmath.h"

/* ------------------------------------------------------------------------- */

/* 10000 and 100000 or something, but lower values while testing scripts,
 * Makefile, etc... */

#define INNERLOOP   10000
#define OUTERLOOP   1000
#define VAL1        2.9
#define VAL2        213
#define VAL3        3.1

/* ------------------------------------------------------------------------- */

static inline long long rdtsc()
{
    long long timestamp;
    asm volatile ("rdtsc\n" : "=A"(timestamp));
    return timestamp;
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
        PRC = (AVG*100)/AVGR; \
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

int main()
{
    unsigned int i, j, num;
    ufp8p8_t   a1, a2, a3, a4;
    ufp24p8_t  b1, b2, b3, b4;
    ufp16p16_t c1, c2, c3, c4;
    ufp8p24_t  d1, d2, d3, d4;
    float      f1, f2, f3, f4;
    double     g1, g2, g3, g4;
    uint64_t   start, end, sum;
    uint64_t   avga, avgb, avgc, avgd, avgf, avgg;
    int        prca, prcb, prcc, prcd, prcf, prcg;
    int        foo, bar;

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

    /* MUL */

    timeloop(avga, a1=mulufp8p8(a2,a3)  );
    timeloop(avgb, b1=mulufp24p8(b2,b3) );
    timeloop(avgc, c1=mulufp16p16(c2,c3));
    timeloop(avgd, d1=mulufp8p24(d2,d3) );
    timeloop(avgf, f1=f2*f3);
    timeloop(avgg, g1=g2*g3);
    calcallperc;
    printreport("MUL", 2);

    /* DIV */

    timeloop(avga, a1=divufp8p8(a2,a3)  );
    timeloop(avgb, b1=divufp24p8(b2,b3) );
    timeloop(avgc, c1=divufp16p16(c2,c3));
    timeloop(avgd, d1=divufp8p24(d2,d3) );
    timeloop(avgf, f1=f2/f3);
    timeloop(avgg, g1=g2/g3);
    calcallperc;
    printreport("DIV", 3);

    /* SQRT */

    timeloop(avga, a1=sqrtufp8p8(a2)  );
    timeloop(avgb, b1=sqrtufp24p8(b2) );
    timeloop(avgc, c1=sqrtufp16p16(c2));
    timeloop(avgd, d1=sqrtufp8p24(d2) );
    timeloop(avgf, f1=sqrt(f2));
    timeloop(avgg, g1=sqrt(g2));
    calcallperc;
    printreport("SQRT", 4);

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

    return 0;
}

/* ------------------------------------------------------------------------- */

