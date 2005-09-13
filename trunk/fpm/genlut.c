/* ------------------------------------------------------------------------- */

/*
 * Fixed Point Math Macro Library - Generate Look-Up-Tables
 *
 * (C)opyright 2005 by Ivo van Poorten
 * Licensed under version 2 of the GPL
 *
 * $Id$
 *
 */

/* ------------------------------------------------------------------------- */

#include <math.h>
#include <stdio.h>
#include <inttypes.h>

/* ------------------------------------------------------------------------- */

#define outputccode(A, B, C, D, e) \
    printf("\n/* "A" */\n\n"); \
    printf("static "B" "C"[%i] = {\n", e); \
    for (i=0; i<e-1; i++) { \
        printf("%uU, ", D[i]); \
    } \
    printf("%uU };\n", D[i]);

/* ------------------------------------------------------------------------- */

int main()
{
    double round(double d);
    uint16_t ufp8p8sqrtlut_16[129],   ufp8p8sqrtlut_256[121];
    uint32_t ufp24p8sqrtlut_16[129],  ufp24p8sqrtlut_256[121],
             ufp24p8sqrtlut_64k[129], ufp24p8sqrtlut_16m[129];
    uint32_t ufp16p16sqrtlut_16[129], ufp16p16sqrtlut_256[121],
             ufp16p16sqrtlut_64k[129];
    uint32_t ufp8p24sqrtlut_4[129],   ufp8p24sqrtlut_16[129],
             ufp8p24sqrtlut_256[121];

    uint16_t ufp8p8explut_16[129],   ufp8p8explut_256[121];
    uint32_t ufp24p8explut_16[129],  ufp24p8explut_256[121],
             ufp24p8explut_64k[129], ufp24p8explut_16m[129];
    uint32_t ufp16p16explut_16[129], ufp16p16explut_256[121],
             ufp16p16explut_64k[129];
    uint32_t ufp8p24explut_4[129],   ufp8p24explut_16[129],
             ufp8p24explut_256[121];

    uint16_t ufp8p8lnlut_16[129],   ufp8p8lnlut_256[121];
    uint32_t ufp24p8lnlut_16[129],  ufp24p8lnlut_256[121],
             ufp24p8lnlut_64k[129], ufp24p8lnlut_16m[129];
    uint32_t ufp16p16lnlut_16[129], ufp16p16lnlut_256[121],
             ufp16p16lnlut_64k[129];
    uint32_t ufp8p24lnlut_4[129],   ufp8p24lnlut_16[129],
             ufp8p24lnlut_256[121];
    int i;
    double d, e, f;

    for (i=0; i<=128; i++) {
        d = sqrt(i/32.0);
        e = exp(i/32.0);
        f = log(i/32.0);
        /* sqrt */
        ufp8p24sqrtlut_4[i] = round(d*65536.0*256.0);
        /* exp */
        ufp8p24explut_4[i]  = round(e*65536.0*256.0);
        /* ln */
        if (f<0) f = 0.0;
        ufp8p24lnlut_4[i]   = round(f*65536.0*256.0);
    }

    for (i=0; i<=128; i++) {
        d = sqrt(i/8.0);
        e = exp(i/8.0);
        f = log(i/8.0);
        /* sqrt */
        ufp8p8sqrtlut_16[i]   = round(d*256.0);
        ufp24p8sqrtlut_16[i]  = round(d*256.0);
        ufp16p16sqrtlut_16[i] = round(d*65536.0);
        ufp8p24sqrtlut_16[i]  = round(d*65536.0*256.0);
        /* exp */
        if (e>=16777216.0) e = 0.0;
        ufp24p8explut_16[i]  = round(e*256.0);
        if (e>=65536.0) e = 0.0;
        ufp16p16explut_16[i] = round(e*65536.0);
        if (e>=256.0) e = 256.0;
        ufp8p24explut_16[i]  = round(e*65536.0*256.0);
        ufp8p8explut_16[i]   = round(e*256.0);
        /* ln */
        if (f<0) f = 0.0;
        ufp8p8lnlut_16[i]   = round(f*256.0);
        ufp24p8lnlut_16[i]  = round(f*256.0);
        ufp16p16lnlut_16[i] = round(f*65536.0);
        ufp8p24lnlut_16[i]  = round(f*65536.0*256.0);
    }

    for (i=0; i<=120; i++) {
        d = sqrt(16.0 + i*2.0);
        e = exp(16.0 + i*2.0);
        f = log(16.0 + i*2.0);
        /* sqrt */
        ufp8p8sqrtlut_256[i]   = round(d*256.0);
        ufp24p8sqrtlut_256[i]  = round(d*256.0);
        ufp16p16sqrtlut_256[i] = round(d*65536.0);
        ufp8p24sqrtlut_256[i]  = round(d*65536.0*256.0);
        /* exp */
        if (e>=16777216.0) e = 0.0;
        ufp24p8explut_256[i]  = round(e*256.0);
        if (e>=65536.0) e = 0.0;
        ufp16p16explut_256[i] = round(e*65536.0);
        if (e>=256.0) e = 0.0;
        ufp8p24explut_256[i]  = round(e*65536.0*256.0);
        ufp8p8explut_256[i]   = round(e*256.0);
        /* ln */
        ufp8p8lnlut_256[i]   = round(f*256.0);
        ufp24p8lnlut_256[i]  = round(f*256.0);
        ufp16p16lnlut_256[i] = round(f*65536.0);
        ufp8p24lnlut_256[i]  = round(f*65536.0*256.0);
    }

    for (i=0; i<=128; i++) {
        d = sqrt(256.0 + i*2.0*256.0);
        e = exp(256.0 + i*2.0*256.0);
        f = log(256.0 + i*2.0*256.0);
        /* sqrt */
        ufp24p8sqrtlut_64k[i]   = round(d*256.0);
        ufp16p16sqrtlut_64k[i]  = round(d*65536.0);
        /* exp */
        e = 0.0;
        ufp24p8explut_64k[i]   = round(e*256.0);
        ufp16p16explut_64k[i]  = round(e*65536.0);
        /* ln */
        ufp24p8lnlut_64k[i]   = round(f*256.0);
        ufp16p16lnlut_64k[i]  = round(f*65536.0);
    }

    for (i=0; i<=128; i++) {
        d = sqrt(65536.0 + i*2.0*65536.0);
        e = exp(65536.0 + i*2.0*65536.0);
        f = log(65536.0 + i*2.0*65536.0);
        /* sqrt */
        ufp24p8sqrtlut_16m[i] = round(d*256.0);
        /* exp */
        e = 0.0;
        ufp24p8explut_16m[i] = round(e*256.0);
        /* ln */
        ufp24p8lnlut_16m[i] = round(f*256.0);
    }

    printf("/* DO NOT INCLUDE THIS FILE DIRECTLY! ALWAYS ");
    printf("INCLUDE fixedpointmath.h only!! */\n\n");

    printf("/*\n * Fixed Point Math Macro Library - Look Up Tables\n");
    printf(" * Licensed under version 2 of the GPL\n */\n\n");

    printf("#ifndef __FIXEDPOINTMATHLUT_H__\n");
    printf("#define __FIXEDPOINTMATHLUT_H__\n");

    /* sqrt */
    printf("\n#if defined(__FPM_ENABLE_SQRT_LUT__) || "
                 "defined(__FPM_ENABLE_ALL_LUT__)\n");

    outputccode("ufp8p8 sqrt 16",  "ufp8p8_t", "_ufp8p8sqrtlut_16",
                ufp8p8sqrtlut_16, 129);
    outputccode("ufp8p8 sqrt 256", "ufp8p8_t", "_ufp8p8sqrtlut_256",
                ufp8p8sqrtlut_256, 121);

    outputccode("ufp24p8 sqrt 16",  "ufp24p8_t", "_ufp24p8sqrtlut_16",
                ufp24p8sqrtlut_16, 129);
    outputccode("ufp24p8 sqrt 256", "ufp24p8_t", "_ufp24p8sqrtlut_256",
                ufp24p8sqrtlut_256, 121);
    outputccode("ufp24p8 sqrt 64k", "ufp24p8_t", "_ufp24p8sqrtlut_64k",
                ufp24p8sqrtlut_64k, 129);
    outputccode("ufp24p8 sqrt 16m", "ufp24p8_t", "_ufp24p8sqrtlut_16m",
                ufp24p8sqrtlut_16m, 129);

    outputccode("ufp16p16 sqrt 16",  "ufp16p16_t", "_ufp16p16sqrtlut_16",
                ufp16p16sqrtlut_16, 129);
    outputccode("ufp16p16 sqrt 256", "ufp16p16_t", "_ufp16p16sqrtlut_256",
                ufp16p16sqrtlut_256, 121);
    outputccode("ufp16p16 sqrt 64k", "ufp16p16_t", "_ufp16p16sqrtlut_64k",
                ufp16p16sqrtlut_64k, 129);

    outputccode("ufp8p24 sqrt 4",  "ufp8p24_t", "_ufp8p24sqrtlut_4",
                ufp8p24sqrtlut_4, 129);
    outputccode("ufp8p24 sqrt 16", "ufp8p24_t", "_ufp8p24sqrtlut_16",
                ufp8p24sqrtlut_16, 129);
    outputccode("ufp8p24 sqrt 256", "ufp8p24_t", "_ufp8p24sqrtlut_256",
                ufp8p24sqrtlut_256, 121);

    printf("\n#endif /* SQRT LUT */\n");

    /* exp */
    printf("\n#if defined(__FPM_ENABLE_EXP_LUT__) || "
                 "defined(__FPM_ENABLE_ALL_LUT__)\n");

    outputccode("ufp8p8 exp 16",  "ufp8p8_t", "_ufp8p8explut_16",
                ufp8p8explut_16, 129);
    outputccode("ufp8p8 exp 256", "ufp8p8_t", "_ufp8p8explut_256",
                ufp8p8explut_256, 121);

    outputccode("ufp24p8 exp 16",  "ufp24p8_t", "_ufp24p8explut_16",
                ufp24p8explut_16, 129);
    outputccode("ufp24p8 exp 256", "ufp24p8_t", "_ufp24p8explut_256",
                ufp24p8explut_256, 121);
    outputccode("ufp24p8 exp 64k", "ufp24p8_t", "_ufp24p8explut_64k",
                ufp24p8explut_64k, 129);
    outputccode("ufp24p8 exp 16m", "ufp24p8_t", "_ufp24p8explut_16m",
                ufp24p8explut_16m, 129);

    outputccode("ufp16p16 exp 16",  "ufp16p16_t", "_ufp16p16explut_16",
                ufp16p16explut_16, 129);
    outputccode("ufp16p16 exp 256", "ufp16p16_t", "_ufp16p16explut_256",
                ufp16p16explut_256, 121);
    outputccode("ufp16p16 exp 64k", "ufp16p16_t", "_ufp16p16explut_64k",
                ufp16p16explut_64k, 129);

    outputccode("ufp8p24 exp 4",  "ufp8p24_t", "_ufp8p24explut_4",
                ufp8p24explut_4, 129);
    outputccode("ufp8p24 exp 16", "ufp8p24_t", "_ufp8p24explut_16",
                ufp8p24explut_16, 129);
    outputccode("ufp8p24 exp 256", "ufp8p24_t", "_ufp8p24explut_256",
                ufp8p24explut_256, 121);

    printf("\n#endif /* EXP LUT */\n");

    /* ln */
    printf("\n#if defined(__FPM_ENABLE_LN_LUT__) || "
                 "defined(__FPM_ENABLE_ALL_LUT__)\n");

    outputccode("ufp8p8 ln 16",  "ufp8p8_t", "_ufp8p8lnlut_16",
                ufp8p8lnlut_16, 129);
    outputccode("ufp8p8 ln 256", "ufp8p8_t", "_ufp8p8lnlut_256",
                ufp8p8lnlut_256, 121);

    outputccode("ufp24p8 ln 16",  "ufp24p8_t", "_ufp24p8lnlut_16",
                ufp24p8lnlut_16, 129);
    outputccode("ufp24p8 ln 256", "ufp24p8_t", "_ufp24p8lnlut_256",
                ufp24p8lnlut_256, 121);
    outputccode("ufp24p8 ln 64k", "ufp24p8_t", "_ufp24p8lnlut_64k",
                ufp24p8lnlut_64k, 129);
    outputccode("ufp24p8 ln 16m", "ufp24p8_t", "_ufp24p8lnlut_16m",
                ufp24p8lnlut_16m, 129);

    outputccode("ufp16p16 ln 16",  "ufp16p16_t", "_ufp16p16lnlut_16",
                ufp16p16lnlut_16, 129);
    outputccode("ufp16p16 ln 256", "ufp16p16_t", "_ufp16p16lnlut_256",
                ufp16p16lnlut_256, 121);
    outputccode("ufp16p16 ln 64k", "ufp16p16_t", "_ufp16p16lnlut_64k",
                ufp16p16lnlut_64k, 129);

    outputccode("ufp8p24 ln 4",  "ufp8p24_t", "_ufp8p24lnlut_4",
                ufp8p24lnlut_4, 129);
    outputccode("ufp8p24 ln 16", "ufp8p24_t", "_ufp8p24lnlut_16",
                ufp8p24lnlut_16, 129);
    outputccode("ufp8p24 ln 256", "ufp8p24_t", "_ufp8p24lnlut_256",
                ufp8p24lnlut_256, 121);

    printf("\n#endif /* LN LUT */\n");

    printf("\n#endif\n");

    return 0;
}

/* ------------------------------------------------------------------------- */

