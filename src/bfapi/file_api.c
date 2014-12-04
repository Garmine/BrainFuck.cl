#include "file_api.h"

#include "bfio.h"
#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include <string.h>

#define API_CODE 2

// MODE - file access: R/W/A
// LENGTH, FILENAME
// execution starts in FN
typedef enum{
	MODE,
	LEN, FN
}State;

// File access modes:
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
}ApiState;

// Host->State extractor
static ApiState* state(Host* h){
	return (ApiState*)(h->apiStates[API_CODE]);
}

// stdin:  host <-- API
static int in(Host* h, char* c){
	*c=(char)getchar();
	return 1;
}

// stdout: host --> API
static int out(Host* h, char c){
	ApiState* st = state(h);
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
				FILE* f = NULL;
				switch(st->m){
					case R:
						if (st->len!=0) f=fopen(st->buff, "r");
						break;
					case W:
						f=fopen(st->buff, "w");
						break;
					case A:
						f=fopen(st->buff, "a");
						break;
				}

				// Read/write from/to DATA tape
				long n=st->len;
				char* ptr = h->ptr;
				if(st->m==R){
					// Read file
					char* buff = NULL;
					if(n==0){
						// Read whole file
						n = readFile(st->buff, &buff);
					}

					// Size check
					if(ptr+n > h->data+h->dLen){
						// file cannot fit on DATA tape!
						error("file API", 
								"file cannot fit on DATA tape!");
						return -1;
					}

					// Read file
					if(buff!=NULL){
						// Finish reading whole file
						memcpy(ptr, buff, n);
					}else{
						// Read first n bytes
						if(ptr+n > h->data+h->dLen){
							// file cannot fit on DATA tape!
							error("file API", 
									"file cannot fit on DATA tape!");
							return -1;
						}
						while (n--) *(ptr++)=fgetc(f);
					}
				}else{
					// Write file
					if(n==0){
						// Write 'till '\0'
						// TODO
					}else{
						// Write n bytes
						// TODO
					}
				}

				// Rinse & repeat!
				if (f!=NULL) fclose(f);
				st->s=MODE;
			}
			break;
	}
	return 1;
}


int initFileApi(){
	// Default state black magic
	ApiState* def = 
		(ApiState*)malloc(sizeof(ApiState));
	def->s = MODE;

	// Add API to BFIO
	Api api;
	api.code = API_CODE;
	api.out  = out;
	api.in   = in;
	if (!addApi(api, (void*)def)) return 0;

	return 1;
}

