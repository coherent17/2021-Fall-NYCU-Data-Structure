CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do1:
	./0811562.exe sample1.in sample1.out
	./0811562.exe sample2.in sample2.out

do2:
	./0811562.exe testcase1 case1.out
	./0811562.exe testcase2 case2.out
	./0811562.exe testcase3 case3.out

check1:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample1.in sample1.out
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample2.in sample2.out

check2:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe testcase1 case1.out
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe testcase2 case2.out
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe testcase3 case3.out

see1:
	cat sample1.out
	cat sample2.out

see2:
	cat case1.out
	cat case2.out
	cat case3.out

clean:
	rm 0811562.exe  *.out