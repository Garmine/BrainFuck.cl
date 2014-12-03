#ifndef HOST_H
#define HOST_H

// Theoretically, this struct allows multiple host threads.
// In practice, at most 1 such thread will ever run.
// (Unless I stop being lazy and grab pthreads.)

typedef struct Host Host;

struct Host{
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
	int(*out)(Host* h, char);
	// stdin  == BfIn
	int(*in)(Host* h, char*);

	// API states
	void* apiStates[256];
};

Host* initHost(const char* src, const int dataSize);
void freeHost(Host* h);

#endif

