#ifndef HOST_H
#define HOST_H

typedef struct{
	// data tape
	char *data;
	// size of data tape
	int dLen;

	// instruction tape - 2 bits/instr 
	char *instr;
	// instruction parameter tape (integers 'cause of JMPs)
	int *param;;
	// number of instructions
	int iLen;
}Host;

Host* initHost(const char* src, const int dataSize);
void freeHost(Host* h);

#endif

