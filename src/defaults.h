#ifndef __DEFAULTS_H_
#define __DEFAULTS_H_

#if	defined ( WIN64 ) || ( __WIN64__ )
	#include <windows.h>
	#include <io.h>
	
	#define getPath GetModuleFileName
	#define u_sleep Sleep
#elif defined ( WIN32 ) || ( __WIN32__ )
	#include <windows.h>
	#include <io.h>
	
	#define getPath GetModuleFileName
	#define u_sleep Sleep
#else
	#include <unistd.h> 
	
	#define u_sleep usleep
#endif

#endif /* __DEFAULTS_H_ */
