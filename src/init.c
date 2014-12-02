#include "init.h"

#include "util.h"
#include "bfio.h"

#include "opencl_api.h"
#include "file_api.h"
#include "streaming_file_api.h"

int initBrainfuckDotCl(){
	if(!initBfio()){
		error("initBrainfuckDotCl()", "failed to initialize I/O");
		return 0;
	}
	
	if(!initOpenClApi()){
		error("initBrainfuckDotCl()", "failed to initialize OpenCL API");
		return 0;
	}
	
	if(!initFileApi()){
		error("initBrainfuckDotCl()", "failed to initialize file API");
		return 0;
	}
	
	if(!initStreamingFileApi()){
		error("initBrainfuckDotCl()", "failed to initialize streaming file API");
		return 0;
	}

	return 1;
}

