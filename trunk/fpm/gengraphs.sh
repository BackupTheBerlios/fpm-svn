#!/bin/sh

# $Id$

# Script to generate graphs from precision output
# (C)opyright 2005 by Ivo van Poorten
# Licensed under version 2 of the GPL

# generic function

# xrange yrange outfile

gengraph() {
    echo "Generating $3.png"
( cat << __EOF__
set nokey
set xrange [$1]
set yrange [$2]
set data style lines
set grid
set border

set terminal fig color

plot "precision.dat" using 1:2, "precision.dat" using 1:3

__EOF__
) | $_gnuplot | $_fig2dev -L png -m 0.85 > $3.png
}

# Read config

. ./config.sh

# Test if all tools were available

testavail() {
    if test "$1" = "" ; then
        echo "Can't create graphs. $2 is not available on your system."
        exit 0
    fi
}

testavail "$_gnuplot" "gnuplot"
testavail "$_fig2dev" "fig2dev"

if test "$_fig2dev_png" = "no" ; then
    echo "Can't generate barcharts. Your $_fig2dev doesn't have PNG support."
    exit 0
fi

# check command line

if [ "$#" != "1" ]; then
    echo "usage: $0 <output-directory>"
    exit -1
fi

# generate all graphs + index.html

( cat << __EOF__
<HTML>
<HEAD></HEAD>
<BODY BGCOLOR="#f0f0f0">
__EOF__
) > $1/index.html

overview(){
    case $1 in
    sqrt)
        echo 0:256 0:16
        ;;
    exp)
        echo 0:5.5 0:256
        ;;
    ln)
        echo 1:256 0:6
        ;;
    pow)
        echo 1:16 0:256
        ;;
    esac
}

zoom1() {
    case $1 in
    sqrt)
        echo 0:4 0:2
        ;;
    exp)
        echo 0:3 0:16
        ;;
    ln)
        echo 1:5 0:2
        ;;
    pow)
        echo 1:2 0:4
        ;;
    esac
}

zoom2() {
    case $1 in
    sqrt)
        echo 112:144 10.25:12.25
        ;;
    exp)
        echo 4:5 50:150
        ;;
    ln)
        echo 3:4 1:1.5
        ;;
    pow)
        echo 8:12 50:150
        ;;
    esac
}

for func in sqrt exp ln pow
do

    for fptype in ufp8p8 ufp24p8 ufp16p16 ufp8p24
    do
        echo "Calculating algorithmic data..."
        ./precision $fptype $func > precision.dat

        outfile=$1/algo_precision_$fptype\_$func
        gengraph `overview $func` $outfile\_overview
        gengraph `zoom1 $func` $outfile\_zoom1
        gengraph `zoom2 $func` $outfile\_zoom2

        echo "Adding lines to index.html..."

        outfile=`basename $outfile`
        ( cat << __EOF__
<B> $func - $fptype - algorithmic </B><BR>
<IMG SRC="${outfile}_overview.png">
<IMG SRC="${outfile}_zoom1.png">
<IMG SRC="${outfile}_zoom2.png">
<BR>
__EOF__
) >> $1/index.html

        echo "Calculating LUT data..."
        ./precisionlut $fptype $func > precision.dat

        outfile=$1/lut_precision_$fptype\_$func
        gengraph `overview $func` $outfile\_overview
        gengraph `zoom1 $func` $outfile\_zoom1
        gengraph `zoom2 $func` $outfile\_zoom2

        echo "Adding lines to index.html..."

        outfile=`basename $outfile`
        ( cat << __EOF__
<B> $func - $fptype - lut </B><BR>
<IMG SRC="${outfile}_overview.png">
<IMG SRC="${outfile}_zoom1.png">
<IMG SRC="${outfile}_zoom2.png">
<P><HR>
__EOF__
) >> $1/index.html


    done
done

echo "</BODY>" >> $1/index.html

