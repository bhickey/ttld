CC = clang

all:
	$(CC) -c ttld.c -o ttld.o -pedantic -Wmost -Werror -O3
	$(CC) main.c ttld.o -o ttld -pedantic -Weverything -Werror -O3

clean:
	rm -f *.o
