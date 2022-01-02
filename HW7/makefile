CC = gcc
CPLUSCC = g++
CFLAGS = -g -Wall
EXE = 0811562
OUTFILE = case1.out case2.out case3.out case4.out case5.out

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $< -o $@.exe

%: %.cpp
	$(CPLUSCC) $(CFLAGS) $< -o $@.exe

do:
	time ./$(EXE).exe case1_input.in case1_target.in case1.out
	time ./$(EXE).exe case2_input.in case2_target.in case2.out
	time ./$(EXE).exe case3_input.in case3_target.in case3.out
	time ./$(EXE).exe case4_input.in case4_target.in case4.out
	time ./$(EXE).exe case5_input.in case5_target.in case5.out

compare:
	diff -w case1.out golden_case1.out > diff1.txt
	diff -w case2.out golden_case2.out > diff2.txt
	diff -w case3.out golden_case3.out > diff3.txt
	diff -w case4.out golden_case4.out > diff4.txt
	diff -w case5.out golden_case5.out > diff5.txt

see:
	cat diff1.txt
	cat diff2.txt
	cat diff3.txt
	cat diff4.txt
	cat diff5.txt

clean:
	rm $(OBJ) $(OUTFILE) *.txt