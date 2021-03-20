CFLAGS=-std=c11 -g -static

9ccc: 9ccc.c
test: 9ccc
		./test.sh
clean:
		rm -f 9ccc *.o *~ tmp*

.PHONY: test clean
