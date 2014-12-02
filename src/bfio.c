#include "bfio.h"

#include "util.h"

#include <stdio.h>

Syscall calls[256];
int init=0;

SyscallIn inCall = NULL;
SyscallOut outCall = NULL;

void initBfio(){
	int i;
	for (i=0; i<256; i++) calls[i].code=-1;
}

int addSyscall(Syscall c){
	int i = c.code;

	// Check for invalid index
	if(i<0 || i>255){
		char buff[16];
		sprintf(buff, "%d", i);
		errors("addSyscall()", "Invalid call index: ", buff);
		return 0;
	}

	
	// Check for usage
	if(calls[i].code != -1){
		char buff[16];
		sprintf(buff, "%d", i);
		errors("addSyscall()", "Index is already being used: ", buff);
		return 0;
	}

	// Register syscall
	call[i]=c;
	return 1;
}

char input(){
	if(inCall){
		// TODO use return value
		char* c;
		inCall(c);
		return *c;
	}else{
		return getchar();
	}
}

void output(char c){
	if(outCall){
		// TODO double-escape
		// TODO use return value
		outCall(c);
	}else{
		putchar(c);
	}
}

