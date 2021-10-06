CC = gcc
CFLAGS = -g -Wall 

0811562: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562 sample.in out
	./0811562 testcase1 output1
	./0811562 testcase2 output2
	./0811562 testcase3 output3
	./0811562 testcase4 output4
	./0811562 testcase5 output5
	./0811562 testcase6 output6

clean:
	rm 0811562 out*
