#include "host-debug.h"

#include "host-instructions.h"

#include <stdio.h>

#if DEBUG
// prints the instruction and the parameters tape
void printHostInstr(Host* host){
	int pc;
	for(pc=0; pc<host->iLen; pc++){
		printf("| ");
		switch(geti(host->instr, pc)){
			case DATA:	printf("DATA");	break;
			case IO:	printf("  IO");	break;
			case PTR:	printf(" PTR");	break;
			case JMP:	printf(" JMP");	break;
		}
		printf(" %4d |\n", host->param[pc]);
	}
}
#endif

