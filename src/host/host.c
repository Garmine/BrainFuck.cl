#include "host.h"

Host* initHost(const char* src, const int dataSize){
	// allocate new host
	Host* h = (Host*)malloc(sizeof(Host));
	if(!h){
		error("initHost()", "failed to allocate memory for host");
		return NULL;
	}
	h->data=NULL;
	h->instr=NULL;
	h->param=NULL;

	// parse source code
	if(!parse(h, src)){
		error("initHost()", "failed to parse source code");
		freeHost(h);
		return NULL;
	}

	// allocate memory for data tape
	h->data = (char*)malloc(sizeof(char)*dataSize);
	if(!h->data){
		error("initHost()", "failed to initalize data tape");
		freeHost(h);
		return NULL;
	}
	h->dLen = dataSize;

	// w00t
	return h;
}

void freeHost(Host* h){
	free(h->data);
	free(h->instr);
	free(h->param);
	free(h);
}

