/* $Id$ */
#include <math.h>
#include <stdio.h>
#include "fixedpointmath.h"

double round(double x);

// used to calculate numbers for ln

int main(void)
{
    int i, d;
    double z;

    for (i=0; i<27; i++) {
        z = log(1 + pow(2, -(i+1)));
        d = round(z * 16777216);
        printf("%i\n", d );
    }

    printf("\n\n");

    for (i=0; i<=24; i++) {
        z = log(pow(2, i));
        d = round(z * 16777216);
        printf("%i\n", d);
    }

    printf("\n\n");

    for (i=0; i<24; i++) {
        z = 1.0 + 1/pow(2, 1+i);
        z = 1/z;
        d = round(z*16777216);
        printf("%i\n", d);
    }

    return 0;
}

