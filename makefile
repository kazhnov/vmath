tests: tests.c
	cc tests.c -o test -lm
	./test
