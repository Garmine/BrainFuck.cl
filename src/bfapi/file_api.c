#include "file_api.h"

#include "bfio.h"
#include <stdlib.h>

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
	api.code = 2;
	api.out  = faOut;
	api.in   = faIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

