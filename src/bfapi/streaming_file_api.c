#include "streaming_file_api.h"

#include "bfio.h"
#include <stdlib.h>

#define API_CODE 3

typedef struct{
	
}StreamingFileApiState;

int sfaIn(Host* h, char* c){
	return 1;
}

int sfaOut(Host* h, char c){
	return 1;
}

int initStreamingFileApi(){
	// Default state black magic
	StreamingFileApiState* def = 
		(StreamingFileApiState*)malloc(sizeof(StreamingFileApiState));

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = sfaOut;
	api.in   = sfaIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

