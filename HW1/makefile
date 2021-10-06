CC = gcc
CFLAGS = -g -Wall 

0811562: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562 sample.in sample.out
	./0811562 testcase1 output1
	./0811562 testcase2 output2
	./0811562 testcase3 output3
	./0811562 testcase4 output4
	./0811562 testcase5 output5

see:
	cat sample.out
	cat output1
	cat output2
	cat output3
	cat output4
	cat output5

clean:
	rm 0811562 out* sample.out
