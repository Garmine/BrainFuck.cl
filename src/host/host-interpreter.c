#include "host-interpreter.h"

#include "util.h"
#include "bfio.h"
#include "host-instructions.h"

// runs the parsed BF code
int run(Host* host, int debug){
	// aliases for tapes
	char* data = host->data;
	int dLen = host->dLen;
	char** ptr = &host->ptr;
	char* instr = host->instr;
	int* param = host->param;
	int iLen = host->iLen;

	int pc=0, p;
	while(pc<iLen){
		switch(geti(instr, pc)){
			case DATA:
				if (debug) printf("%03d DATA %4d\n", pc, param[pc]);
				**ptr += param[pc];
				break;

			case PTR:
				if (debug) printf("%03d  PTR %4d\n", pc, param[pc]);
				*ptr += param[pc];
				if (*ptr<data || *ptr>=&data[dLen]){
					printf("\n");
					error("interpreter", "pointer out of range "
							"(data tape is too short?)");
					return 0;
				}
				break;

			case JMP:
				if (debug) printf("%03d  JMP %4d", pc, param[pc]);
				p=param[pc];
				if( (p<0 && **ptr) || (p>0 && !**ptr) ){
					pc += param[pc]-1;
					if (debug) printf(" - GOTO %03d\n---", pc+1);
				}
				if (debug) printf("\n");
				break;

			case IO:
				if (debug) printf("%03d   IO %4d", pc, param[pc]);
				p=param[pc];
				if(p>0){
					if (debug) printf(" - READ: \n");
					while (p--) **ptr=input(host);
				}else{
					if (debug) printf(" - WRITE '");
					while (p++) output(host, **ptr);
					if (debug) printf("'\n");
				}
				break;
		}
		pc++;
	}

	// Completed program
	return 1;
}

