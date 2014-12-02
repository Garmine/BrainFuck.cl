#ifndef HOST_H
#define HOST_H

// Theoretically, this struct allows multiple host threads.
// In practice, at most 1 such thread will ever run.

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

	// BFIO state
	// flag for 1st ESC (double triggers the API)
	char esc;
	// stdout == BfOut
	int(*out)(char);
	// stdin  == BfIn
	int(*in)(char*);
}Host;

Host* initHost(const char* src, const int dataSize);
void freeHost(Host* h);

#endif

