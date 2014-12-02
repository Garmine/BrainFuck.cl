#include "host-instructions.h"

// fetches instruction from instr at index i
char geti(char* instr, int i){
	return (instr[i/4]>>(6-i%4*2))&3;
}

// writes instruction to instr at index i
void seti(char* instr, int i, char inst){
	instr[i/4] |= inst<<(6-i%4*2);
}

