#!/bin/sh

# $Id$

# Script to generate index for barcharts
# (C)opyright 2005 by Ivo van Poorten
# Licensed under version 2 of the GPL

# Read config

# check command line

if [ "$#" != "2" ]; then
    echo "usage: $0 <outputdirectory> <title>"
    exit -1
fi

( cat << __EOF__
<HTML>
<HEAD></HEAD>
<BODY BGCOLOR="#f0f0f0">
<B> BENCHMARKS - $2 </B> <P>
Bars: ufp8p8, ufp24p8, ufp16p16, ufp8p24, float, double
<HR>
__EOF__
) > $1/index.html

for i in add sub mul div sqrt exp ln pow
do

( cat << __EOF__
<B>$i</B>
<TABLE> <TR>
<TD ALIGN="CENTER">
algorithmic <BR>
<IMG SRC="algo_benchmark_$i.png">
</TD>
<TD ALIGN="CENTER">
lut <BR>
<IMG SRC="lut_benchmark_$i.png">
</TD>
</TR> </TABLE>
<BR><HR>
__EOF__
) >> $1/index.html

done

