CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562 sample.in sample.out

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811562 sample.in sample.out

see:
	cat sample.out

clean:
	rm 0811562  sample.out