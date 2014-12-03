#ifndef BFIO_H
#define BFIO_H

#include "host.h"

typedef int(*BfOut)(Host* h, char);
typedef int(*BfIn)(Host* h, char*);

typedef struct{
	int code;
	BfOut out;
	BfIn in;
}Api;

int initBfio();
int terminateBfio();

int addApi(Api api, void* defState);

void* getDefStates();

char input(Host* host);
void output(Host* host, char c);

#endif

