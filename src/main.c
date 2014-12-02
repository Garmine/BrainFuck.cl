#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "util.h"
#include "host.h"
#include "host-interpreter.h"

int main(int argc, char** argv){
	if(!initBrainfuckDotCl())
		fatalError("Failed to initialize Brainfuck.cl");


	// Read in some BF code from some file
	char* code = readFile("bf/schorbino.bf");
	if(code==NULL)
		fatalError("Failed to read in BF code");

		
	// Create host
	Host* host = initHost(code, 128);
	free(code);
	if(host==NULL)
		fatalError("Failed to create host thread");


	// Run host
	run(host);


	// KTHXBAI
	freeHost(host);
	return 0;
}

