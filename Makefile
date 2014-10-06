CC = clang

all:
	clang -c ttld.c -o ttld.o -pedantic -Wmost -Werror -O3
	clang main.c ttld.o -o ttld -pedantic -Weverything -Werror -O3

clean:
	rm -f *.o
