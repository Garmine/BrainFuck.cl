Terminology
===========

Kernel - either the OpenCL kernel code (the BF interpreter), or
       - the compiled BF code (usually called "BrainFuck kernel")

Tape - data array, either associated with the host or ONE device

Thread - instantiated BF kernel associated with ONE tape and ONE device 
       - (it's status is either NOT_STARTED, RUNNING, READY)

Host - the main thread running on the C interpreter on the CPU

Host code - common BainFuck code: "+-<>[].,"

Device - any OpenCL device (including the CPU potentially)

Device code - restricted BrainFuck code, IO is blocked (i.e. no ",.", others work: "+-<>[]")

API - API attached to STDIN and STDOUT, see api.md for details

