#include <stdlib.h>
#include <stdio.h>

#include "init.h"
#include "util.h"
#include "host.h"
#include "host-interpreter.h"

int main(int argc, char** argv){
	// Init magic
	if(!initBrainfuckDotCl())
		fatalError("Failed to initialize Brainfuck.cl");


	// Read in some BF code from some file
	char* code = NULL;
	if(!readFile("bf/cat.bf", &code))
		fatalError("Failed to read in BF code");

		
	// Create host
	Host* host = initHost(code, 128);
	free(code);
	if(host==NULL)
		fatalError("Failed to create host thread");


	// Run host
	if(!run(host, 0)){
		freeHost(host);
		terminateBrainfuckDotCl();
		fatalError("BrainFuck program terminated unexpectedly.");
	}


	// KTHXBAI
	freeHost(host);
	terminateBrainfuckDotCl();
	return 0;
}

