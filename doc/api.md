Using the BrainFuck.cl API
==========================

You can reach the API through STDOUT - sending ESC (0x1B) twice triggers the 
API, the next bytes determine the behavior.

By default API access is not echoed, in case of unused API calls STDOUT returns
to normal state after the unused code.

Return code is stored in the first byte of STDIN, newer return codes override 
earlier ones. By default 0 means success, anything else is an error code.
WARNING: some calls return 0 ON ERROR, always check the documentation first!
Simply read one char from STDIN to discard the latest return code.

###Example:

	stdout: ESC ESC 02 01 "/dev/null" 0 64
	command: read 64 bytes from /dev/null, write to tape

- - -

Full list of API codes:
=======================

	00 - reserved

	01 - access OpenCL API
		00 - init API
		01 - get list of OpenCL devices
			type - 0 for ALL, 1 for CPU, 2 for GPU, 3 for ACCELERATOR, 4 for DEFAULT
			writes the available device IDs to the tape
			returns number of devices written
		02 - copy data between tapes
			src - source tape
			srcptr - source pointer
			dest - destination tape
			destptr - destination pointer
			length - bytes to copy
		03 - compile kernel
			code - null terminated string of BF code
			returns the ID of the compiled kernel or 0 on failure
		04 - create data tape on device
			devid - device id
			length - length of data tape
		05 - instantiate kernel
			devid - ID of device (see 01-01)
			tapeid - ID of tape to associate kernel with
			kernelid - ID of compiled kernel code
			returns ID of created (and NOT running) thread, or 0 on failure
		06 - run kernel(s)
			id0, id1, ... - thread IDs (see 01-05 above)
			0 - end of IDs
		07 - is thread ready?
			id - thread id
			returns 1 if true, 0 if false
		08 - wait for thread: halts execution 'till thread is ready
			id - (running) thread's id

	02 - access file API
		00 - unused
		01 - read from
			length - if 0: read in whole file else read in length bytes
			filename - null terminated string
		02 - write to
			length - if 0: write 'till \0 else write length bytes
			filename - null terminated string
		03 - append to
			length - if 0: write 'till \0 else write length bytes
			filename - null terminated string

	03 - access streaming file API
		00 - unused
		01 - read from: STDIN will read from file
			filename - null terminated string
		02 - close read
		03 - write to: STDOUT will write to file
			filename - null terminated string
		04 - flush: flushes STDOUT
		05 - close write
		06 - I/O: STDIN will read from file, STDOUT will write to where STDIN is pointing
			filename - null terminated string
		07 - flush I/O
		08 - close I/O

	anything else - send "ESC ESC char" to STDOUT

- - -

