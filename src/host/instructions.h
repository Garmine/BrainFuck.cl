#ifndef HOST_INSTRUCTIONS_H
#define HOST_INSTRUCTIONS_H

// host instructions
typedef enum{
	
	// BF: + - | BIN: 00
	// data manipulation
	DATA = 0;


	// BF: > < | BIN: 01
	// pointer manipulation
	PTR  = 1;


	// BF: [ ] | BIN: 10
	// jump to instruction (relative address)
	JMP  = 2;


	// BF: , . | BIN: 11
	// input/output
	IO   = 3;
	// IO is special:
	//     0 > OUT (dot is negative)
	//     0 = NOOP
	//     0 < IN (comma is positive)


	// special invalid value
	NOP = 4;
	
} Instruction;

char geti(char* instr, int i);
void seti(char* instr, int i, char inst);

#endif

