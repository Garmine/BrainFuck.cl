#include "opencl_api.h"

#include "bfio.h"

int ocaIn(char* c){
	return 1;
}

int ocaOut(char c){
	return 1;
}

int initOpenClApi(){

	// Add API to BFIO
	Api api;
	api.code = 1;
	api.out  = ocaOut;
	api.in   = ocaIn;
	addApi(api);

	return 1;
}

