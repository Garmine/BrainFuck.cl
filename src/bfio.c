#include "bfio.h"

#include "util.h"

#include <stdio.h>

#define ESC 0x1B

Api calls[256];
int init=0;

int initBfio(){
	// API 00 is reserved
	calls[0].code=0;
	calls[0].out=NULL;
	calls[0].in=NULL;

	// empty calls[]	
	int i;
	for (i=1; i<256; i++) calls[i].code=-1;

	// initalization successful
	init=1;
	return 1;
}

int addApi(Api api){
	int i = api.code;

	// Check for invalid index
	if(i<0 || i>255){
		char buff[16];
		sprintf(buff, "%d", i);
		errors("addApi()", "Invalid call index: ", buff);
		return 0;
	}

	
	// Check for usage
	if(calls[i].code != -1){
		char buff[16];
		sprintf(buff, "%d", i);
		errors("addApi()", "Index is already being used: ", buff);
		return 0;
	}

	// Register syscall
	calls[i]=api;
	return 1;
}

void activateApi(Host* host, int api){
	host->out=calls[api].out;
	host->in=calls[api].in;
}

char input(Host* host){
	if(host->in){
		// read char from API
		char c;
		if (!host->in(&c)) activateApi(host, 0);
		return c;
	}else{
		// read char from stdin
		return getchar();
	}
}

void output(Host* host, char c){
	if(host->out){
		// send c to API
		if (!host->out(c)) activateApi(host, 0);
	}else{
		// out == stdout => API call detection

		// ESC detection
		if(host->esc==2){
			// "ESC ESC API"
			host->esc=0;
			// signed to unsigned (if neccessary)
			int api = (c<0)?(127-c):(c);
			// activate API
			activateApi(host, api);

		}else if(c==ESC){
			// "... ESC"
			// "ESC ESC"
			host->esc++;

		}else if(host->esc==1){
			// "ESC char"
			host->esc=0;
			putchar(ESC);
			putchar(c);

		}else{
			// ordinary character -> stdout
			putchar(c);
		}
	}
}

