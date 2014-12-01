#include <stdlib.h>
#include <stdio.h>

// lol, sed to change the BF code and test the interpreter? ;D
char programkod[]="\
++++[>++++[>+++++<-]<-]>>+++.    83=S\
<++++[>++++<-]>.                 99=c\
+++++.                          104=h\
+++++++.                        111=o\
+++.                            114=r\
<++++[>----<-]>.                 98=b\
>+++++[>++++++<-]>+++.<<         33=!\
<+++[>++++<-]>.                 110=n\
+.                              111=o\
>>>++[>+++++<-]>.                10=\n";

/* BF interpreter in BF, relative JMPs of [-128, 127] are too short for this T-T
 * should change JMP parameter to an unsigned index into a 256-widge jump table of
 * global addresses OTOH it'd limit the number JMPs to 256....

"\
>>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>[\
->>]<[>>]<<-]<[<]<+>>[>]>[<+>-[[<+>-]>]<[[[-]<]++<-[<+++++++++>[<->-]>>]>>]]<<\
]<]<[[<]>[[>]>>[>>]+[<<]<[<]<+>>-]>[>]+[->>]<<<<[[<<]<[<]+<<[+>+<<-[>-->+<<-[>\
+<[>>+<<-]]]>[<+>-]<]++>>-->[>]>>[>>]]<<[>>+<[[<]<]>[[<<]<[<]+[-<+>>-[<<+>++>-\
[<->[<<+>>-]]]<[>+<-]>]>[>]>]>[>>]>>]<<[>>+>>+>>]<<[->>>>>>>>]<<[>.>>>>>>>]<<[\
>->>>>>]<<[>,>>>]<<[>+>]<<[+<<]<]\
[\
	input a brainfuck program and its input, separated by an exclamation point.\
	Daniel B Cristofani (cristofdathevanetdotcom)\
	http://www.hevanet.com/cristofd/brainfuck/\
]";
*/

//=====================
// COMPILE TIME CONSTS
#define DATA_SIZE 32768
// num of instructions divided by 4
// I'm too lazy for dynamic memory mgmt
#define INSTR_SIZE 4096
// stack size for [] compilation
#define STACK_SIZE 1024

//=====================
// INSTRUCTIONS:

// BF: + - | BIN: 00
// data manipulation
#define DATA 0

// BF: > < | BIN: 01
// pointer manipulation
#define PTR 1

// BF: [ ] | BIN: 10
// jump to instruction (relative address)
#define JMP 2

// BF: , . | BIN: 11
// input/output
#define IO 3
// IO is special:
//     0 > OUT (dot is negative)
//     0 = NOOP
//     0 < IN (comma is positive)

// special invalid value
#define NOP 4

//=====================
// MEMORY:

// data tape
char data[DATA_SIZE] = {0};
// instruction tape - 2 bits/instr 
char instr[INSTR_SIZE] = {0};
// instruction parameter tape - 8 bits/instr
char param[INSTR_SIZE*4] = {0};
// end of instructions
int end = 0;
// pointer
char *ptr = data;

//=====================
// FLAGS:

// safe mode - error for overindexing etc.
//char safe=1;
// debug - print each and every instruction
char debug=0;

//=====================
// MAGIC:

void error(const char *type, const char *msg){
	fprintf(stderr, "%s ERROR: %s\n", type, msg);
	exit(EXIT_FAILURE);
}

// fetches instruction from instr at index i
char geti(int i){
	if (i<0 || i>=INSTR_SIZE*4) error("INSTR", "instruction READ out of range");
	char ret = (instr[i/4]>>(6-i%4*2))&3;
	return ret;
}

// writes instruction to instr at index i
void seti(int i, char inst){
	if (i<0 || i>=INSTR_SIZE*4) error("INSTR", "instruction WRITE out of range");
	instr[i/4] |= inst<<(6-i%4*2);
}

// parses the supplied char*
void parse(const char* code){
	int i=0, pc=-1, last=NOP, stack[STACK_SIZE], si=-1;
	char c;

	while((c=code[i++])){
		int sgn=1;
		switch(c){

			// DATA
			case '-':
				sgn=-1;
			case '+':
				if (last!=DATA) seti(++pc, DATA);
				last=DATA;
				param[pc] += sgn;
				break;

			// POINTER
			case '<':
				sgn=-1;
			case '>':
				if (last!=PTR) seti(++pc,  PTR);
				last=PTR;
				param[pc] += sgn;
				break;

			// IO
			case '.':
				sgn=-1;
			case ',':
				if (last!=IO || sgn*param[pc]<0) seti(++pc, IO);
				last=IO;
				param[pc] += sgn;
				break;

			// GOTO
			case '[':
				last=JMP;
				seti(++pc, JMP);
				if (si==STACK_SIZE-1) error("PARSE", "stack is full!");
				stack[++si] = pc;
				break;

			case ']':
				last=JMP;
				seti(++pc, JMP);
				if (si<0) error("PARSE", "] without opening [");
				int dist = pc-stack[si];
				if (dist < -128 || dist > 127) error("PARSE", "JMP out of range");
				char d = (char)dist;
				param[pc] = -d;
				param[stack[si]] = d;
				si--;
				break;
		}
	}

	if (si>-1) error("PARSE", "[ without closing ]\n");

	end=++pc;
}

// prints the instruction and the parameters tape
void printInstr(){
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

// runs the parsed BF code
void run(){
	int pc=0, p;
	while(pc<end){
		switch(geti(pc)){
			case DATA:
				if (debug) printf("%03d DATA %4d\n", pc, param[pc]);
				*ptr += param[pc];
				break;

			case PTR:
				if (debug) printf("%03d  PTR %4d\n", pc, param[pc]);
				ptr += param[pc];
				if (ptr<data || ptr>=&data[DATA_SIZE]) error("PTR", "pointer out of range");
				break;

			case JMP:
				if (debug) printf("%03d  JMP %4d", pc, param[pc]);
				p=param[pc];
				if( (p<0 && *ptr) || (p>0 && !*ptr) ){
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
					while (p--) *ptr=getchar();
				}else{
					if (debug) printf(" - WRITE '");
					while (p++) putchar(*ptr);
					if (debug) printf("'\n");
				}
				break;
		}
		pc++;
	}
}

int main(int argc, char** argv){
	parse(programkod);

	if (debug) printInstr();

	run();

	return 0;
}

