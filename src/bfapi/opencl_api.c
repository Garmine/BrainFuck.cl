#include "opencl_api.h"

#include "bfio.h"
#include <stdlib.h>

#define API_CODE 1

typedef struct{
	
}OpenClApiState;

// Host->State extractor
OpenClApiState* state(Host* h){
	return (OpenClApiState*)(h->apiStates[API_CODE]);
}

// stdin:  host <-- API
int ocaIn(Host* h, char* c){
	return 1;
}

// stdout: host --> API
int ocaOut(Host* h, char c){
	return 1;
}

int initOpenClApi(){
	// Default state black magic
	OpenClApiState* def = 
		(OpenClApiState*)malloc(sizeof(OpenClApiState));

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = ocaOut;
	api.in   = ocaIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

