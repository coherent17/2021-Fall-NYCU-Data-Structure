CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562.exe sample1.in sample1.out

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample1.in sample1.out

see:
	cat sample_out

clean:
	rm 0811562.exe  *_out