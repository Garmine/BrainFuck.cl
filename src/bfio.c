#include "bfio.h"

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESC 0x1B

Api calls[256];
int init=0;

void* defStates[256] = {0};

int initBfio(){
	// API 00 is reserved
	calls[0].code=0;
	calls[0].out=NULL;
	calls[0].in=NULL;
	defStates[0]=NULL;

	// empty calls[]	
	int i;
	for (i=1; i<256; i++) calls[i].code=-1;

	// initalization successful
	init=1;
	return 1;
}

int terminateBfio(){
	// free default API state structs
	int i;
	for(i=0; i<256; i++)
		if(defStates[i])
			free(defStates[i]);

	return 1;
}

int addApi(Api api, void* defState){
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
	
	// Add default state
	defStates[i] = defState;

	// Register syscall
	calls[i]=api;
	return 1;
}

void* getDefStates(){
	void** ret = (void*)malloc(sizeof(void*)*256);

	// Copy defStates[] structs
	int i;
	for(i=0; i<256; i++){
		if(defStates[i]){
			ret[i] = malloc(sizeof(defStates[i]));
			memcpy(ret[i], defStates[i], sizeof(defStates[i]));
		}else{
			ret[i]=NULL;
		}
	}
	return ret;
}

void activateApi(Host* host, int api){
	host->out=calls[api].out;
	host->in=calls[api].in;
}

int input(Host* host){
	if(host->in){
		// read char from API
		int r = host->in(host, host->ptr);
		if (r==0) activateApi(host, 0);
		return r;
	}else{
		// read char from stdin
		*host->ptr=getchar();
		return 1;
	}
}

int output(Host* host){
	if(host->out){
		// send data[ptr] to API
		int r = host->out(host, *host->ptr);
		if (r==0) activateApi(host, 0);
		return r;
	}else{
		// out == stdout => API call detection

		char c = *host->ptr;

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
	return 1;
}

