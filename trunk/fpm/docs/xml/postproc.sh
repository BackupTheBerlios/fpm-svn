#!/bin/sh

# Simple script to replace keywords by begining and ending of table instead of
# overriding "chunk-element-content" in the stylesheet, which results in an
# endless loop (<xsl:apply-imports/>).  If somebody knows how to fix that,
# please let me know.

# chunks:

_files=`find ../HTML -type f -name *.html`

for i in $_files
do
    sed -e 's/BEGINOFTABLEHERECHUNK/\<table bgcolor=\"#f0f0f0\" width=\"700\" border=\"0\" cellspacing=\"0\" cellpadding=\"16\" height=\"1000\" \> \<tr\> \<td valign=\"top\" align=\"left\"\>/' $i | sed -e 's/ENDOFTABLEHERECHUNK/\<\/td\> \<\/tr\> \<\/table\>/' | sed -e 's/BEGINOFTABLEHERESINGLE//' | sed -e 's/ENDOFTABLEHERESINGLE//' > $i.tmp
    mv -f $i.tmp $i
done

# singles:

_files=`find ../HTML-single -type f -name *.html`

for i in $_files
do
    sed -e 's/BEGINOFTABLEHERESINGLE/\<table bgcolor=\"#f0f0f0\" width=\"700\" border=\"0\" cellspacing=\"0\" cellpadding=\"16\" height=\"1000\" \> \<tr\> \<td valign=\"top\"\>/' $i | sed -e 's/ENDOFTABLEHERESINGLE/\<\/td\> \<\/tr\> \<\/table\>/' | sed -e 's/BEGINOFTABLEHERECHUNK//' | sed -e 's/ENDOFTABLEHERECHUNK//' > $i.tmp
    mv -f $i.tmp $i
done

