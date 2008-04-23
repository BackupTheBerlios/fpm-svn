#! /bin/sh

LC_ALL=C

# these can be overridden from the command line (and CFLAGS is effective too)
CC=${CC:-cc}
arch=${arch:-`uname -m`}

ARCH=
OPTIMIZE=
FPM_HAVE_X87=
FPM_HAVE_SSE=
FPM_HAVE_INTRINSICS=

cc_vendor=unknown
if test "`$CC --help | grep -qi gcc >/dev/null 2>&1 && echo yes`" == "yes" ; then
    cc_vendor=gnu
elif test "`$CC -flags | grep -qi sun >/dev/null 2>&1 && echo yes`" == "yes" ; then
    cc_vendor=sun
fi

case "$cc_vendor" in
    gnu|unknown)
        OPTIMIZE=-O3
        ;;
    sun)
        OPTIMIZE=-xO5
        ;;
esac

echo "cc vendor: $cc_vendor"
echo "optimize: $OPTIMIZE"

cctest() {
    $CC $OPTIMIZE $ARCH $CFLAGS -o /dev/null tests.c $@ 1>/dev/null 2>&1
}

addcflags() {
    CFLAGS="$CFLAGS $@"
}

archflags() {
    if test "$cc_vendor" == "gnu" ; then
        cctest -march=$arch && ARCH="$ARCH -march=$arch"
        cctest -mtune=$arch && ARCH="$ARCH -mtune=$arch"
        cctest -mcpu=$arch && ARCH="$ARCH -mcpu=$arch"
    fi
    echo "arch flags: $ARCH"
}

archflags

cctest -DTEST_ALWAYS_INLINE -Werror && addcflags -DHAVE_ALWAYS_INLINE && echo have_always_inline
cctest -DTEST_X87 && FPM_HAVE_X87=1 && echo have_x87
cctest -DTEST_SSE && FPM_HAVE_SSE=1 && echo have_sse && case "$arch" in i?86) arch=pentium3; ARCH= ; archflags ;; esac
cctest -DTEST_INTRINSICS && FPM_HAVE_INTRINSICS=1 && echo have_intrinsics

toupper() {
    echo "$@" | tr '[abcdefghijklmnopqrstuvwxyz]' \
                   '[ABCDEFGHIJKLMNOPQRSTUVWXYZ]'
}

build() {
    echo $CC $OPTIMIZE $ARCH $CFLAGS $@
    $CC $OPTIMIZE $ARCH $CFLAGS $@
}

build_all() {
    pf=$1
    shift 1
    for _i in float double \
             fp8p8 fp24p8 fp16p16 fp8p24 \
             ufp8p8 ufp24p8 ufp16p16 ufp8p24
    do
        _j=`toupper $_i`
        build bench.c -o bench-$_i$pf -I`pwd`/../include -lm -DDO$_j $@
    done
}

check_config() {
    eval f=\$$1
    test "$f" == "1"
}

make_false() {
    for _i in float double \
             fp8p8 fp24p8 fp16p16 fp8p24 \
             ufp8p8 ufp24p8 ufp16p16 ufp8p24
    do
        echo skip: bench-$_i$1
        cat > bench-$_i$1 <<__EOF__
#! /bin/sh
exit 1
__EOF__
        chmod 755 bench-$_i$1
    done
}

build_all
build_all -nfmc -DFPM_NO_FPU_MUL_CONVERSIONS

for i in 1 2 ; do
    build_all -srm$i -DFPM_SQUARE_ROOT_METHOD=$i
done

for i in 3 4 ; do
    for j in "" "-nfmc -DFPM_NO_FPU_MUL_CONVERSIONS" ; do
        m=`echo $j | cut -d ' ' -f 1`
        n=`echo $j | cut -d ' ' -f 2`
        build_all $m-srm$i -DFPM_SQUARE_ROOT_METHOD=$i $n
    done
done

if check_config FPM_HAVE_X87 ; then
    for j in "" "-nfmc -DFPM_NO_FPU_MUL_CONVERSIONS" ; do
        m=`echo $j | cut -d ' ' -f 1`
        n=`echo $j | cut -d ' ' -f 2`
        build_all $m-srm5 -DFPM_SQUARE_ROOT_METHOD=5 -DFPM_HAVE_X87 $n
    done
else
    make_false -srm5
    make_false -nfmc-srm5
fi

if check_config FPM_HAVE_SSE ; then
    for i in 6 7 8 ; do
        for j in "" "-nfmc -DFPM_NO_FPU_MUL_CONVERSIONS" ; do
            m=`echo $j | cut -d ' ' -f 1`
            n=`echo $j | cut -d ' ' -f 2`
            build_all $m-srm$i -DFPM_SQUARE_ROOT_METHOD=$i -DFPM_HAVE_SSE $n
        done
    done
else
    for i in 6 7 8 ; do
        make_false -srm$i
        make_false -nfmc-srm$i
    done
fi

if check_config FPM_HAVE_SSE && check_config FPM_HAVE_INTRINSICS ; then
    for i in 9 10 11 ; do
        for j in "" "-nfmc -DFPM_NO_FPU_MUL_CONVERSIONS" ; do
            m=`echo $j | cut -d ' ' -f 1`
            n=`echo $j | cut -d ' ' -f 2`
            build_all $m-srm$i -DFPM_SQUARE_ROOT_METHOD=$i -DFPM_HAVE_SSE -DFPM_HAVE_INTRINSICS $n
        done
    done
else
    for i in 9 10 11 ; do
        make_false -srm$i
        make_false -nfmc-srm$i
    done
fi

