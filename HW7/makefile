CC = gcc
CFLAGS = -g -Wall

0811562.exe: 0811562.c
	$(CC) $(CFLAGS) $< -o $@

do:
	./0811562.exe case1_input.in case1_target.in case1.out
	./0811562.exe case2_input.in case2_target.in case2.out
	./0811562.exe case3_input.in case3_target.in case3.out
	./0811562.exe case4_input.in case4_target.in case4.out
	./0811562.exe case5_input.in case5_target.in case5.out

clean:
	rm 0811562.exe *.out