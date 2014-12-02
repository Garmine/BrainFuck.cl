#include "util.h"

void errors(const char *type, const char *msg, const char* str){
	fprintf(stderr, "%s error: %s %s\n", type, msg);
}

void error(const char *type, const char *msg){
	error(type, msg, "");
}

void ferror(const char *msg){
	error("FATAL", msg, "");
	exit(EXIT_FAILURE);
}

char* readFile(const char* fileName){
	// open file
	FILE* f = fopen(fileName, "r");
	if(!f){
		error("makeShader()", "couldn't open file: ", fileName);
		return NULL;
	}

	// find size of file
	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	rewind(f);

	// allocate buffer
	char* buffer = (char*)malloc(sizeof(char)*(size+1));
	if(!buffer){
		error("makeShader()", "couldn't allocate memory for buffer");
		fclose(f);
		return NULL;
	}

	// read in file
	if(fread(buffer, size, 1, f) != 1){
		error("makeShader()", "couldn't read file: ", fileName);
		fclose(f);
		return NULL;
	}
	fclose(f);

	// return read in file
	return buffer;
}

