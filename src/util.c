#include "util.h"

void errors(const char *type, const char *msg, const char* str){
	fprintf(stderr, "%s error: %s %s\n", type, msg, str);
}

void error(const char *type, const char *msg){
	errors(type, msg, "");
}

void fatalError(const char *msg){
	errors("FATAL", msg, "");
	exit(EXIT_FAILURE);
}

long readFile(const char* fileName, char** dst){
	// open file
	FILE* f = fopen(fileName, "r");
	if(!f){
		errors("readFile()", "couldn't open file: ", fileName);
		*dst = NULL;
		return 0;
	}

	// find size of file
	fseek(f, 0L, SEEK_END);
	long size = ftell(f);
	rewind(f);

	// allocate buffer
	char* buffer = (char*)malloc(sizeof(char)*(size+1));
	if(!buffer){
		error("readFile()", "couldn't allocate memory for buffer");
		fclose(f);
		*dst = NULL;
		return 0;
	}

	// read in file
	if(fread(buffer, size, 1, f) != 1){
		errors("readFile()", "couldn't read file: ", fileName);
		fclose(f);
		*dst = NULL;
		return 0;
	}
	fclose(f);

	// set dst to read in file
	buffer[size]='\0';
	*dst = buffer;

	// return number read in bytes
	return size+1;
}

