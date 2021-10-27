CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562 sample.in sample.out
	./0811562 testcase1 out1
	./0811562 testcase2 out2

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811562 sample.in sample.out
	$(CHECKCC) $(CHECKFLAGS) ./0811562 testcase1 out1
	$(CHECKCC) $(CHECKFLAGS) ./0811562 testcase2 out2

see:
	cat sample.out

clean:
	rm 0811562  sample.out out*