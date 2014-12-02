#include "interpreter.h"

#include "bfio.h"

#define DEBUG 0

#if DEBUG
#define DBG(x) x
#else
#define DBG(x)
#endif

// runs the parsed BF code
void run(Host* host){
	// aliases for tapes
	char* data = host->data;
	int dLen = host->dLen;
	char* instr = host->instr;
	int* param = host->param;
	int iLen = Host->iLen;

	// DATA pointer
	char* ptr = data;

	int pc=0, p;
	while(pc<end){
		switch(geti(instr, pc)){
			case DATA:
				DBG(printf("%03d DATA %4d\n", pc, param[pc]));
				*ptr += param[pc];
				break;

			case PTR:
				DBG(printf("%03d  PTR %4d\n", pc, param[pc]));
				ptr += param[pc];
				if (ptr<data || ptr>=&data[dLen]) 
					error("PTR", "pointer out of range");
				break;

			case JMP:
				DBG(printf("%03d  JMP %4d", pc, param[pc]));
				p=param[pc];
				if( (p<0 && *ptr) || (p>0 && !*ptr) ){
					pc += param[pc]-1;
					DBG(printf(" - GOTO %03d\n---", pc+1));
				}
				DBG(printf("\n"));
				break;

			case IO:
				DBG(printf("%03d   IO %4d", pc, param[pc]));
				p=param[pc];
				if(p>0){
					DBG(printf(" - READ: \n"));
					while (p--) *ptr=input();
				}else{
					DBG(printf(" - WRITE '"));
					while (p++) output(*ptr);
					DBG(printf("'\n"));
				}
				break;
		}
		pc++;
	}
}

