CC = gcc
CPLUSCC = g++
CFLAGS = -g -Wall -std=c99
EXE = 0811562
OUTFILE = case1.out case2.out case3.out case4.out case5.out mysample_output.out

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
	time ./$(EXE).exe sample_input.in sample_target.in mysample_output.out

clean:
	rm $(OBJ) $(OUTFILE) 