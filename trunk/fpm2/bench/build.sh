#! /bin/sh

LC_ALL=C
CC=cc

toupper() {
    echo "$@" | tr '[abcdefghijklmnopqrstuvwxyz]' \
                   '[ABCDEFGHIJKLMNOPQRSTUVWXYZ]'
}

build_all() {
    for i in float double \
             fp8p8 fp24p8 fp16p16 fp8p24 \
             ufp8p8 ufp24p8 ufp16p16 ufp8p24
    do
        j=`toupper $i`
        $CC -o bench-$i$1 bench.c -I`pwd`/../include -lm -DDO$j $2
    done
}

build_all
build_all -no-fpu-mul -DFPM_NO_FPU_MUL_CONVERSIONS
