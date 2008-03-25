
clean:
	rm -f benchmark

distclean: clean
	rm -f *~ */*~ */*/*~ */*/*/*~

benchmark: benchmark.c include/fpm/fpm.h include/fpm/fpmcode.h
	gcc -I `pwd`/include -o benchmark benchmark.c -W -Wall -O3 -lm -s

