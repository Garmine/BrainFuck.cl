#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

void errors(const char *type, const char *msg, const char* str);
void error(const char *type, const char *msg);
void fatalError(const char *msg);

long readFile(const char* fileName, char** dst);

#endif

