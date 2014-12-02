#include "streaming_file_api.h"

#include "bfio.h"

int sfaIn(char* c){
	return 1;
}

int sfaOut(char c){
	return 1;
}

int initStreamingFileApi(){

	// Add API to BFIO
	Api api;
	api.code = 3;
	api.out  = sfaOut;
	api.in   = sfaIn;
	addApi(api);

	return 1;
}

