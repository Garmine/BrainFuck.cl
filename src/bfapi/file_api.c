#include "file_api.h"

#include "bfio.h"
#include <stdlib.h>

#define API_CODE 2

// MODE SELECT: R/W/A
// LENGTH, FILENAME, I/O
typedef enum{
	MODE,
	LEN, FN, IO
}State;

// READ, WRITE, APPEND
typedef enum{
	R, W, A
}Mode;

typedef struct{
	State s;
	Mode m;
	// length
	int len;
	// filename
	char buff[256];
	int bi;
}FileApiState;

// Host->State extractor
FileApiState* state(Host* h){
	return (FileApiState*)(h->apiStates[API_CODE]);
}

// stdin:  host <-- API
int faIn(Host* h, char* c){
	c=getchar();
	return 1;
}

// stdout: host --> API
int faOut(Host* h, char c){
	FileApiState* st = state(h);
	switch(st->s){
		case MODE:
			// Mode parameter
			switch(c){
				case 1:
					st->m=R;
					break;
				case 2:
					st->m=W;
					break;
				case 3:
					st->m=A;
					break;
				default:
					return 0;
			}
			st->s=LEN;
			break;

		case LEN:
			// Length parameter
			st->len=c;
			st->bi=0;
			st->s=FN;
			break;

		case FN:
			// Filename parameter
			st->buff[st->bi++]=c;

			// Terminating NULL
			if(c=='\0'){

				// Open file according to selected mode
				FILE* f;
				switch(st->m){
					case R:
						f=fopen(st->buff, "r");
						break;
					case W:
						f=fopen(st->buff, "w");
						break;
					case A:
						f=fopen(st->buff, "a");
						break;
				}

				// Read/write from/to DATA tape
				int n=st->len;
				if(st->m==R){
					// TODO:
					// read n bytes OR
					// read 'till 0
					// TO tape
				}else{
					// TODO:
					// write n bytes OR
					// write 'till 0
					// FROM tape
				}
			}

			// Rinse & repeat!
			st->s=MODE;
			break;
	}
	return 1;
}

int initFileApi(){
	// Default state black magic
	FileApiState* def = 
		(FileApiState*)malloc(sizeof(FileApiState));
	def->s = MODE;

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = faOut;
	api.in   = faIn;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

