#include "host-debug.h"

#include "host-instructions.h"

#if DEBUG
// prints the instruction and the parameters tape
void printHostInstr(Host* host){
	int pc;
	printf("| ");
	for(pc=0; pc<host->iLen; pc++){
		switch(geti(host->instr, pc)){
			case DATA:	printf("DATA | ");	break;
			case IO:	printf("  IO | ");	break;
			case PTR:	printf(" PTR | ");	break;
			case JMP:	printf(" JMP | ");	break;
		}
	}
	printf("\n| ");
	for	(pc=0; pc<host->iLen; pc++) printf("%4d | ", host->param[pc]);
	printf("\n");
}
#endif

