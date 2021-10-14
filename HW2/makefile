CC = gcc
CFLAGS = -g -Wall 

0811562: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562 sample.in sample.out
	./0811562 testcase1 output1

see:
	cat sample.out
	cat output1

clean:
	rm 0811562 out* sample.out