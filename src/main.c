#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "util.h"
#include "host.h"
#include "host-interpreter.h"

// Prints "Schorbino!\n" to stdout
const char* code = "\
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

int main(int argc, char** argv){
	if(!initBrainfuckDotCl())
		fatalError("Failed to initialize Brainfuck.cl");

	// Create host
	Host* host = initHost(code, 128);

	if(host==NULL)
		fatalError("Failed to create host thread");

	// Run host
	run(host);

	// KTHXBAI
	return 0;
}

