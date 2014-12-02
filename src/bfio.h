#ifndef BFIO_H
#define BFIO_H

#include "host.h"

typedef int(*BfOut)(char);
typedef int(*BfIn)(char*);

typedef struct{
	int code;
	BfOut out;
	BfIn in;
}Api;

int initBfio();

int addApi(Api api);

char input(Host* host);
void output(Host* host, char c);

#endif

