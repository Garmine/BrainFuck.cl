#ifndef BFIO_H
#define BFIO_H

typedef int(*SyscallOut)(char);
typedef int(*SyscallIn)(char*);
typedef struct{
	int code;
	SyscallOut out;
	SyscallIn in;
}Syscall;

int addSyscall(Syscall c);

char input();
void output(char c);

#endif

