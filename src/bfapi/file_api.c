#include "file_api.h"

#include "bfio.h"
#include <stdlib.h>

#define API_CODE 2

typedef struct{
	
}FileApiState;

int faIn(Host* h, char* c){
	return 1;
}

int faOut(Host* h, char c){
	return 1;
}

int initFileApi(){
	// Default state black magic
	FileApiState* def = 
		(FileApiState*)malloc(sizeof(FileApiState));

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = faOut;
	api.in   = faIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

