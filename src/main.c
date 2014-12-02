#include <stdlib.h>
#include <stdio.h>

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
	Host* host = initHost(code, 128);
	run(host);
	return 0;
}

