#
# Fixed Point Math Macro Library - Makefile
#
# (C)opyright 2005,2006 by Ivo van Poorten
# Licensed under version 2 of the GPL
#
# $Id$
#

include config.mak

GENLUTOBJS		= genlut.o
BENCHOBJS		= benchmark.o
BENCHLUTOBJS	= benchmarklut.o
PRECOBJS		= precision.o
PRECLUTOBJS		= precisionlut.o

GENERATEDFILES	= config.mak include/fixedpointmathlut.h

.PHONY:	all
all:				$(GENERATEDFILES)

#This file is generated
include/fixedpointmathlut.h:	genlut
	./genlut 2>/dev/null | $(INDENT) 1>include/fixedpointmathlut.h

genlut:				$(GENLUTOBJS)
	$(LD) -o $@ $(GENLUTOBJS) $(LDFLAGS)

benchmark:			$(GENERATEDFILES) $(BENCHOBJS)
	$(LD) -o $@ $(BENCHOBJS) $(LDFLAGS)

benchmarklut:		$(GENERATEDFILES) $(BENCHLUTOBJS)
	$(LD) -o $@ $(BENCHLUTOBJS) $(LDFLAGS)

precision:			$(GENERATEDFILES) $(PRECOBJS)
	$(LD) -o $@ $(PRECOBJS) $(LDFLAGS)

precisionlut:		$(GENERATEDFILES) $(PRECLUTOBJS)
	$(LD) -o $@ $(PRECLUTOBJS) $(LDFLAGS)

.PHONY:	benchmarks
benchmarks:			benchmark benchmarklut

.PHONY: precisions
precisions:			precision precisionlut

benchmarklut.c:		benchmark.c
	echo "#define __FPM_ENABLE_ALL_LUT__" 1> benchmarklut.c
	cat benchmark.c 1>> benchmarklut.c

precisionlut.c:		precision.c
	echo "#define __FPM_ENABLE_ALL_LUT__" 1> precisionlut.c
	cat precision.c 1>> precisionlut.c

.PHONY:	barcharts
barcharts:			benchmark.dat benchmarklut.dat
	mkdir -p barcharts
	sh ./genbarcharts.sh benchmark.dat    barcharts algo
	sh ./genbarcharts.sh benchmarklut.dat barcharts lut

benchmark.dat:		benchmark
	./benchmark		1> benchmark.dat 2>/dev/null

benchmarklut.dat:	benchmarklut
	./benchmarklut	1> benchmarklut.dat 2>/dev/null

graphs:				precision precisionlut
	mkdir -p graphs
	sh ./gengraphs.sh graphs

config.mak:			configure
	@echo
	@echo "#############################"
	@echo "Please run ./configure first!"
	@echo "#############################"
	@echo
	@echo "If you have done so before, you have to do it again, because it"
	@echo "has changed."
	@echo
	@exit 1

ifneq ($(GENLUTOBJS),)
-include $(patsubst %,deps/%,$(GENLUTOBJS:.o=.d))
endif

ifneq ($(BENCHOBJS),)
-include $(patsubst %,deps/%,$(BENCHOBJS:.o=.d))
endif

ifneq ($(BENCHLUTOBJS),)
-include $(patsubst %,deps/%,$(BENCHLUTOBJS:.o=.d))
endif

ifneq ($(PRECOBJS),)
-include $(patsubst %,deps/%,$(PRECOBJS:.o=.d))
endif

ifneq ($(PRECLUTOBJS),)
-include $(patsubst %,deps/%,$(PRECLUTOBJS:.o=.d))
endif

%.o:	%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $*.c -o $*.o $(DEBUG) $(WARNINGS)
	mkdir -p deps
	$(CCFORDEPS) $(CFLAGS) $(INCLUDES) $*.c 1>deps/$*.d

.PHONY:	clean
clean:
	$(MAKE) -C docs/xml clean
	$(MAKE) -C include clean
	$(MAKE) -C tools clean
	rm -f *.o benchmark genlut
	rm -f benchmark.dat benchmarklut benchmarklut.c benchmarklut.dat
	rm -f precision.dat precision precisionlut precisionlut.c
	rm -rf deps barcharts graphs

.PHONY:	distclean
distclean:		clean
	$(MAKE) -C docs/xml distclean
	$(MAKE) -C include distclean
	$(MAKE) -C tools distclean
	rm -f config.mak config.sh configure.log
	rm -f *~

.PHONY:	install
install:		all
	@echo Installing to $(PREFIX)
	test -d $(PREFIX)/include || mkdir -p $(PREFIX)/include
	cp -v include/fixedpointmath*.h $(PREFIX)/include
	chmod 644 $(PREFIX)/include/fixedpointmath*.h

.PHONY: uninstall
uninstall:
	@echo Uninstalling from $(PREFIX)
	rm -f $(PREFIX)/include/fixedpointmath*.h

.PHONY: docs
docs:
	$(MAKE) -C docs/xml

.PHONY: docs2web
docs2web:	docs
	@echo
	cp -af docs/HTML docs/HTML-single ../website/docs
	@echo
	@echo "Don't forget to run cvs diff and/or cvs commit in ../website/docs"
	@echo

