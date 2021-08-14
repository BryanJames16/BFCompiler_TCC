/* Standard Libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Self Libraries */
#include "bfcdef.h"
#include "meta.h"
#include "bfcfile.h"

int
main (int argc, char *argv[])
{
	FILE *inputFile;
	char cells[1024] = {"\0"};
	int pointer = 0;
	char buffer[999] = {"\0"};
	int loopCount = 0;
	int innerLoop = 0;
	
	if (argc == 1) {
		// Automatic invalid commandline argument
		printf (noInputFile);
	} else {
		count++;
		exists = checkFile (argv[count]);
		
		if (exists == 2) {
			pass1Check = extCheck(argv[count]);
			pass2Check = charCheck(argv[count]);
			pass3Check = loopCheck(argv[count]);
			if (pass1Check || pass2Check || pass3Check) {
				printf (errorsFound);
			} else {
				inputFile = fopen (argv[argc - 1], "r+");
					while (fgets(buffer, 999, inputFile) != NULL) {
						for (loopCount = 0; loopCount < strlen (buffer); loopCount++) {
							if (buffer[loopCount] == '+') {
								cells[loopCount]++;
							} else if (buffer[loopCount] == '-') {
								cells[loopCount]--;
							} else if (buffer[loopCount] == '>') {
								loopCount++;
							} else if (buffer[loopCount] == '<') {
								loopCount--;
							} else if (buffer[loopCount] == '.') {
								putchar(cells[loopCount]);
							} else if (buffer[loopCount] == ',') {
								cells[loopCount] = getchar();
							} else if (buffer[loopCount] == '[') {
								continue;
							} else if (buffer[loopCount] == ']' && cells[loopCount] != 0) {
								innerLoop = 1;
								
								while (innerLoop > 0) {
									
								}
							} else if (buffer[loopCount] == '\n' || buffer[loopCount] == '\t' || buffer[loopCount] == ' ') {
								// ignore and continue
								continue;
							} else {
								printf ("Error: %d\n", buffer[count2]);
								printf (compileCompilerFailed);
								printf ("Error 0x000005FE\n");
								printf ("Please contact the developer.\n");
								printf ("Terminating compilation.\n");
								
								return (1);
								break;
							}
						}
					}
				fclose (inputFile);
			}
		} else if (exists == 1) {
			printf (inputFileAccessError);
		} else {
			printf (inputFileNotFound);
		}
	}
	
	return (0);
}

