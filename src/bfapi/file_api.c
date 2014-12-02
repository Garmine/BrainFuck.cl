#include "file_api.h"

#include "bfio.h"

int faIn(char* c){
	return 1;
}

int faOut(char c){
	return 1;
}

int initFileApi(){

	// Add API to BFIO
	Api api;
	api.code = 2;
	api.out  = faOut;
	api.in   = faIn;
	addApi(api);

	return 1;
}

