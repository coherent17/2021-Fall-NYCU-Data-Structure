CC = gcc
CFLAGS = -g -Wall

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562.exe sample1.in sample1.out
	./0811562.exe sample2.in sample2.out
	./0811562.exe testcase1.in testcase1.out
	./0811562.exe testcase2.in testcase2.out
	./0811562.exe testcase3.in testcase3.out

clean:
	rm 0811562.exe  *.out