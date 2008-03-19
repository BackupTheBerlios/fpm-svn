#!/bin/sh

# $Id$

# Script to generate barcharts from benchmark output
# (C)opyright 2005,2006 by Ivo van Poorten
# Licensed under version 2 of the GPL

# awk trick inspired by:
# http://www.togaware.com/datamining/gdatamine/barchart

# Read config

. ./config.sh

# Test if all tools were available

testavail() {
    if test "$1" = "" ; then
        echo "Can't create barcharts. $2 is not available on your system."
        exit 0
    fi
}

testavail "$_gnuplot" "gnuplot"
testavail "$_awk" "awk"
testavail "$_fig2dev" "fig2dev"

if test "$_fig2dev_png" = "no" ; then
    echo "Can't generate barcharts. Your $_fig2dev doesn't have PNG support."
    exit 0
fi

# check command line

if test "$#" != "3" ; then
    echo "usage: $0 <datafile> <outputdirectory> <prefix-to-filenames>"
    exit -1
fi

# generate all barcharts

xleft=0
xright=7

for i in add sub mul div sqrt exp ln pow
do

( cat << __EOF__
set nokey
set xrange [$xleft:$xright]
set yrange [0:150]
set data style boxes
set grid
set noborder

set terminal fig color

plot "$1" using 1:2, "$1" using 1:3, "$1" using 1:4, "$1" using 1:5, "$1" using 1:6, "$1" using 1:7, "$1" using 1:8, "$1" using 1:9

__EOF__
) | $_gnuplot | $_awk 'BEGIN {} /10 0 -1     0.000 0 0 0 0 0 5/{$9=20} {print}' | $_fig2dev -L png -m 1 > $2/$3\_benchmark_$i.png

xleft=`expr $xleft + 10`
xright=`expr $xright + 10`

done

