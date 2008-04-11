
# -DFPM_HAVE_RDTSC
# -DFPM_SQUARE_ROOT_METHOD=x	(and -DFPM_HAVE_X87, -DFPM_HAVE_SSE,
#  								 -DFPM_HAVE_INTRINSICS)
#

all:	bench-float 	\
		bench-double 	\
		all-fixed

all-fixed:	bench-fp8p8 	\
			bench-fp24p8 	\
			bench-fp16p16 	\
			bench-fp8p24 	\
			bench-ufp8p8 	\
			bench-ufp24p8 	\
			bench-ufp16p16 	\
			bench-ufp8p24

bench-float:	bench.c
	$(CC) -o bench-float bench.c -I`pwd`/../include -lm -DDOFLOAT

bench-double: 	bench.c
	$(CC) -o bench-double bench.c -I`pwd`/../include -lm -DDODOUBLE

bench-fp8p8: 	bench.c
	$(CC) -o bench-fp8p8 bench.c -I`pwd`/../include -lm -DDOFP8P8

bench-fp24p8: 	bench.c
	$(CC) -o bench-fp24p8 bench.c -I`pwd`/../include -lm -DDOFP24P8

bench-fp16p16: 	bench.c
	$(CC) -o bench-fp16p16 bench.c -I`pwd`/../include -lm -DDOFP16P16

bench-fp8p24: 	bench.c
	$(CC) -o bench-fp8p24 bench.c -I`pwd`/../include -lm -DDOFP8P24

bench-ufp8p8: 	bench.c
	$(CC) -o bench-ufp8p8 bench.c -I`pwd`/../include -lm -DDOUFP8P8

bench-ufp24p8: 	bench.c
	$(CC) -o bench-ufp24p8 bench.c -I`pwd`/../include -lm -DDOUFP24P8

bench-ufp16p16: 	bench.c
	$(CC) -o bench-ufp16p16 bench.c -I`pwd`/../include -lm -DDOUFP16P16

bench-ufp8p24: 	bench.c
	$(CC) -o bench-ufp8p24 bench.c -I`pwd`/../include -lm -DDOUFP8P24

clean:
	rm -f bench-*

distclean:	clean
	rm -f *~
