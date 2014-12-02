#ifndef HOST_DEBUG_H
#define HOST_DEBUG_H

#define DEBUG 0

#if DEBUG
void printHostInstr(Host* host);
#else
#define printHostInstr(x)
#endif

#endif

