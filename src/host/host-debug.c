#include "host-debug.h"

#include "instructions.h"

// prints the instruction and the parameters tape
void printHostInstr(Host* host){
	int pc;
	printf("| ");
	for(pc=0; pc<end; pc++){
		switch(geti(pc)){
			case DATA:	printf("DATA | ");	break;
			case IO:	printf("  IO | ");	break;
			case PTR:	printf(" PTR | ");	break;
			case JMP:	printf(" JMP | ");	break;
		}
	}
	printf("\n| ");
	for	(pc=0; pc<end; pc++) printf("%4d | ", param[pc]);
	printf("\n");
}

