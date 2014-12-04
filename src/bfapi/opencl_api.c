#include "opencl_api.h"

#include "bfio.h"
#include <stdlib.h>
#include <stdio.h>

#define API_CODE 1

typedef struct{
	
}ApiState;

// Host->State extractor
static ApiState* state(Host* h){
	return (ApiState*)(h->apiStates[API_CODE]);
}

// stdin:  host <-- API
static int in(Host* h, char* c){
	return 1;
}

// stdout: host --> API
static int out(Host* h, char c){
	return 1;
}

int initOpenClApi(){
	// Default state black magic
	ApiState* def = 
		(ApiState*)malloc(sizeof(ApiState));

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = out;
	api.in   = in;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

