/* ------------------------------------------------------------------------- */

/*
 * Fixed Point Math Macro Library - Precision
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
#include <string.h>

#include "fixedpointmath.h"

/* ------------------------------------------------------------------------- */

#define TYPEufp8p8   0
#define TYPEufp24p8  1
#define TYPEufp16p16 2
#define TYPEufp8p24  3

#define FUNCsqrt    0
#define FUNCexp     1
#define FUNCln      2
#define FUNCpow     3

#define PVAL      2.0L

/* ------------------------------------------------------------------------- */

double startat[4] = { 0.0L, 0.0L, 1.0L, 1.0L };

/* ------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    double f, g1 = 0.0L, g2 = 0.0L;
    int fptype = -1, func = -1;

    if (argc != 3) {
        fprintf(stderr,"usage: %s <fixed-point-type> <function>\n", argv[0]);
        return -1;
    }

    if (!strncmp(argv[1], "ufp8p8",   5))    fptype = TYPEufp8p8;
    if (!strncmp(argv[1], "ufp24p8",  6))    fptype = TYPEufp24p8;
    if (!strncmp(argv[1], "ufp16p16", 7))    fptype = TYPEufp16p16;
    if (!strncmp(argv[1], "ufp8p24",  6))    fptype = TYPEufp8p24;

    if (!strncmp(argv[2], "sqrt", 4))       func = FUNCsqrt;
    if (!strncmp(argv[2], "exp",  3))       func = FUNCexp;
    if (!strncmp(argv[2], "ln",   2))       func = FUNCln;
    if (!strncmp(argv[2], "pow",  3))       func = FUNCpow;

    if (fptype == -1) {
        fprintf(stderr, "unknown type!\n");
        return -1;
    }

    if (func == -1) {
        fprintf(stderr, "unknown function!\n");
        return -1;
    }

    for (f=startat[func]; f<256.0L; f+=0.01L) {

        switch(func) {
        case FUNCsqrt:
            g1 = sqrt(f);
            break;
        case FUNCexp:
            g1 = exp(f);
            break;
        case FUNCln:
            g1 = log(f);
            break;
        case FUNCpow:
            g1 = pow(f, PVAL);
            break;
        }

        switch(fptype) {

        case TYPEufp8p8:
            switch(func) {
            case FUNCsqrt:
                g2 = ufp8p8tod ( sqrtufp8p8 (dtoufp8p8(f)) );
                break;
            case FUNCexp:
                g2 = ufp8p8tod ( expufp8p8 (dtoufp8p8(f)) );
                break;
            case FUNCln:
                g2 = ufp8p8tod ( lnufp8p8 (dtoufp8p8(f)) );
                break;
            case FUNCpow:
                g2 = ufp8p8tod ( powufp8p8 (dtoufp8p8(f), dtoufp8p8(PVAL)) );
                break;
            }
            break;

        case TYPEufp24p8:
            switch(func) {
            case FUNCsqrt:
                g2 = ufp24p8tod ( sqrtufp24p8 (dtoufp24p8(f)) );
                break;
            case FUNCexp:
                g2 = ufp24p8tod ( expufp24p8 (dtoufp24p8(f)) );
                break;
            case FUNCln:
                g2 = ufp24p8tod ( lnufp24p8 (dtoufp24p8(f)) );
                break;
            case FUNCpow:
                g2 = ufp24p8tod ( powufp24p8 (dtoufp24p8(f),
                                                        dtoufp24p8(PVAL)) );
                break;
            }
            break;

        case TYPEufp16p16:
            switch(func) {
            case FUNCsqrt:
                g2 = ufp16p16tod ( sqrtufp16p16 (dtoufp16p16(f)) );
                break;
            case FUNCexp:
                g2 = ufp16p16tod ( expufp16p16 (dtoufp16p16(f)) );
                break;
            case FUNCln:
                g2 = ufp16p16tod ( lnufp16p16 (dtoufp16p16(f)) );
                break;
            case FUNCpow:
                g2 = ufp16p16tod ( powufp16p16 (dtoufp16p16(f),
                                                        dtoufp16p16(PVAL)) );
                break;
            }
            break;

        case TYPEufp8p24:
            switch(func) {
            case FUNCsqrt:
                g2 = ufp8p24tod ( sqrtufp8p24 (dtoufp8p24(f)) );
                break;
            case FUNCexp:
                g2 = ufp8p24tod ( expufp8p24 (dtoufp8p24(f)) );
                break;
            case FUNCln:
                g2 = ufp8p24tod ( lnufp8p24 (dtoufp8p24(f)) );
                break;
            case FUNCpow:
                g2 = ufp8p24tod ( powufp8p24 (dtoufp8p24(f),
                                                        dtoufp8p24(PVAL)) );
                break;
            }
            break;

        } /* end of outer-switch */

        printf("%0.8lf %0.8lf %0.8lf\n", f, g1, g2);

    }

    return 0;
}

/* ------------------------------------------------------------------------- */

