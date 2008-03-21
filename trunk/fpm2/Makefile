
clean:

distclean: clean
	rm -f *~ */*~ */*/*~ */*/*/*~

benchmark: benchmark.c
	gcc -I `pwd`/include -o benchmark benchmark.c -W -Wall -O3 -lm -s

