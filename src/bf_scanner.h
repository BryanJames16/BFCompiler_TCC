#ifndef __BF_SCANNER_H_
#define __BF_SCANNER_H_

#define MAX_BUF 999

#include "bf_filemap.h"

/**
	* Function declaration
*/
unsigned short int _charCheck (char *filename);
unsigned short int _loopCheck (char *filename);
unsigned short int passCheck (char *filename);

#endif /* __BF_SCANNER_H_ */
