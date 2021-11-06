CC = gcc
CFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562.exe sample.in sample_out
	./0811562.exe test.in test_out

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe sample.in sample_out
	$(CHECKCC) $(CHECKFLAGS) ./0811562.exe test.in test_out

see:
	cat sample_out

clean:
	rm 0811562.exe  *_out