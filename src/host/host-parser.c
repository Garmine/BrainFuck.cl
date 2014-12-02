#include "host-parser.h"

#include "util.h"
#include "host-instructions.h"

#include <string.h>

// stack size for parsing [ and ]
// 1024 nested loops => THIS IS A LOT!
#define STACK_SIZE 1024
// buffer size for temporary storage of instructions
// 2^13 = 16384 = 278512 bytes = 278 KB => THIS IS A LOT!
#define BUFFER_SIZE 16384

// parse buffer for instruction tape
// reused for each & every parse()
char instr[BUFFER_SIZE];
int param[BUFFER_SIZE*4];
// stack for parsing [ and ]
int stack[STACK_SIZE];

// parses the supplied char*
int parse(Host* host, const char* code){
	if(host->instr!=NULL || host->param!=NULL){
		error("parse()", "host already contains code");
		return 0;
	}

	int i=0, pc=-1, last=NOP, si=-1;
	char c;

	while((c=code[i++])){
		int sgn=1;
		switch(c){

			// DATA
			case '-':
				sgn=-1;
			case '+':
				if (last!=DATA) seti(instr, ++pc, DATA);
				last=DATA;
				param[pc] += sgn;
				break;

			// POINTER
			case '<':
				sgn=-1;
			case '>':
				if (last!=PTR) seti(instr, ++pc,  PTR);
				last=PTR;
				param[pc] += sgn;
				break;

			// IO
			case '.':
				sgn=-1;
			case ',':
				if (last!=IO || sgn*param[pc]<0) seti(instr, ++pc, IO);
				last=IO;
				param[pc] += sgn;
				break;

			// GOTO
			case '[':
				last=JMP;
				seti(instr, ++pc, JMP);
				if(si==STACK_SIZE-1){
					error("parse()", "stack is full!");
					return 0;
				}
				stack[++si] = pc;
				break;

			case ']':
				last=JMP;
				seti(instr, ++pc, JMP);
				if(si<0){
					error("parse()", "] without opening [");
					return 0;
				}
				int d = pc-stack[si];
/*
				if(d < INT_MIN || d > INT_MAX){
					error("parse()", "JMP out of range");
					return 0;
				}
*/
				param[pc] = -d;
				param[stack[si]] = d;
				si--;
				break;
		}
	}

	// EOF
	int end = ++pc;

	// check JMPs
	if(si>-1){
		error("parse()", "[ without closing ]\n");
		return 0;
	}

	// save instructions
	host->instr = (char*)malloc(sizeof(char)*end);
	if(!host->instr){
		error("parse()", "failed to allocate memory for instruction tape");
		return 0;
	}
	memcpy(host->instr, instr, sizeof(char)*end);
	
	// save parameters
	host->param = (int*)malloc(sizeof(int)*end*4);
	if(!host->param){
		error("parse()", "failed to allocate memory for parameters tape");
		return 0;
	}
	memcpy(host->param, param, sizeof(int)*end*4);

	// save ze length
	host->iLen = end;
	
	return 1;
}

