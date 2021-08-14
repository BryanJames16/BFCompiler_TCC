#ifndef __BF_FILEMAP_H_
#define __BF_FILEMAP_H_

#include "bfcdef.h"

/**
	* Rename io.h _access() function to access()
*/
#define MAX_BUF 999
#if	defined ( WIN64 ) || ( __WIN64__ )
	#define access _access
#elif defined ( WIN32 ) || ( __WIN32__ )
	#define access _access
#endif

/**
	* Function Declarations
*/
void changeSlash (char *pathname);
int checkFile (const char *filename);
char * getDefaultCompilerPath (void);
int _extCheck (char *filename);
void remFileName (char *pathname);

#endif /* __BF_FILEMAP_H_ */
