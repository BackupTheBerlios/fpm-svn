#! /bin/sh

LC_ALL=C
CC=cc

toupper() {
    echo "$@" | tr '[abcdefghijklmnopqrstuvwxyz]' \
                   '[ABCDEFGHIJKLMNOPQRSTUVWXYZ]'
}

build() {
    echo "$@"
    $CC $@
}

build_all() {
    pf=$1
    shift 1
    for i in float double \
             fp8p8 fp24p8 fp16p16 fp8p24 \
             ufp8p8 ufp24p8 ufp16p16 ufp8p24
    do
        j=`toupper $i`
        build bench.c -o bench-$i$pf -I`pwd`/../include -lm -DDO$j $@
    done
}

build_all
build_all -no-fpu-mul -DFPM_NO_FPU_MUL_CONVERSIONS
