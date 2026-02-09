tests: tests.c
	cc tests.c -o test -lm -Wall -Wextra -Werror
	./test
