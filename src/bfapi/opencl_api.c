#include "opencl_api.h"

#include "bfio.h"
#include <stdlib.h>

typedef struct{
	
}OpenClApiState;

int ocaIn(Host* h, char* c){
	return 1;
}

int ocaOut(Host* h, char c){
	return 1;
}

int initOpenClApi(){
	// Default state black magic
	OpenClApiState* def = 
		(OpenClApiState*)malloc(sizeof(OpenClApiState));

	// Add API to BFIO
	Api api;
	api.code = 1;
	api.out  = ocaOut;
	api.in   = ocaIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

