CFLAGS=-std=c11 -g -Bstatic

9ccc: 9ccc.c
test: 9ccc
		./test.sh
clean:
		rm -f 9ccc *.o *~ tmp*

.PHONY: test clean
