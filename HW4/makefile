CC = gcc
CFLAGS = -g -Wall

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562.exe sample.in sample.out
	./0811562.exe testcase1 1_out
	./0811562.exe testcase2 2_out2

see:
	cat sample_out

clean:
	rm 0811562.exe  *_out