#ifndef HOST_DEBUG_H
#define HOST_DEBUG_H

#include "host.h"

#define DEBUG 1

#if DEBUG
void printHostInstr(Host* host);
#else
#define printHostInstr(x)
#endif

#endif

