CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do1:
	./0811562.exe sample1.in sample1.out

do2:
	./0811562.exe sample2.in sample2.out

check1:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample1.in sample1.out

check2:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample2.in sample2.out

see1:
	cat sample1.out

see2:
	cat sample2.out

clean:
	rm 0811562.exe  *.out