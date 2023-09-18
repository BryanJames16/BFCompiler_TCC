/* Standard Libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Default Libraries */
#include "defaults.h"
#include "config.h"

/* Self Libraries */
#include "bfcdef.h"
#include "meta.h"
#include "bfcfile.h"

int
main (int argc, char *argv[])
{
	FILE *inputFile;
	FILE *outputFile;
	FILE *configurationFile;
	
	char buffer [MAX_BUF] = {"\0"};
	char outFile [MAX_BUF] = {"\0"};
	char exeFile [MAX_BUF] = {"\0"};
	char cmd [MAX_BUF] = {"\0"};
	char compiler_path [MAX_BUF] = {"\0"};
	char compiler_include_path [MAX_BUF] = {"\0"};
	char compiler_lib_path [MAX_BUF] = {"\0"};
	char compiler_sp_lib_path [MAX_BUF] = {"\0"};
	char compiler_static_path [MAX_BUF] = {"\0"};
	char currPath [MAX_BUF] = {"\0"};
	char fileonly [MAX_BUF] = {"\0"};
	
	char compiler_path_config [MAX_BUF] = {"\0"};
	char compiler_executable_config [MAX_BUF] = {"\0"};
	char tmp_folder_config [MAX_BUF] = {"\0"};
	char source_ext_config [MAX_BUF] = {"\0"};
	
	int count = 0;
	int count2 = 0;
	int tabCount = 0;
	int exists = 0;
	int addTab = 0;
	int compiled = 0;
	unsigned short int indicated = 0;
	unsigned short int passed = 0;
	
	if (argc == 1) {
		// Automatic invalid commandline argument
		printf (noInputFile);
	} else {
		count++;
		
		while (count < argc) {
			if (strcmp (argv[count], "-o") == 0 || strcmp (argv[count], "-O") == 0) {
				if (argc <= count + 2) {
					count++;
					exists = checkFile (argv[count]);
					
					if (exists == 2) {
						passed = passCheck(argv[count]);
						if (passed) {
							printf (errorsFound);
							break;
						}
						
						if (!indicated) {
							strcpy (compiler_path, getDefaultCompilerPath());
						}
						
						getPath (NULL, currPath, 99);
						changeSlash(currPath);
						remFileName(currPath);
						strcpy (outFile, argv[count]);
						sscanf (outFile, "%[^.]s", outFile);
						strcat (exeFile, outFile);
						strcpy (fileonly, outFile);
						strcat (exeFile, ".exe");
						strcpy (outFile, currPath);
						sprintf (outFile, "%s/%s/%s", currPath, getValue (tmp_folder_config, tmpfolder), fileonly);
						strcat (outFile, getValue (source_ext_config, source_ext));
						
						remove (outFile);
						remove (exeFile);
						
						inputFile = fopen (argv[count], "r+");
						outputFile = fopen (outFile, "w+");
							
							fprintf (outputFile, includes_comment);
							fprintf (outputFile, includes);
							fprintf (outputFile, mainFunctionTop);
							fprintf (outputFile, mainArray);
							fprintf (outputFile, mainPointer);
							
							while (fgets (buffer, MAX_BUF, inputFile) != NULL) {
								for (count2 = 0; count2 < strlen (buffer); count2++) {
									for (tabCount = 0; tabCount < addTab; tabCount++) {
										fprintf (outputFile, "\t");
									}
									
									if (buffer[count2] == '+') {
										fprintf (outputFile, incValue);
									} else if (buffer[count2] == '-') {
										fprintf (outputFile, decValue);
									} else if (buffer[count2] == '>') {
										fprintf (outputFile, incPointer);
									} else if (buffer[count2] == '<') {
										fprintf (outputFile, decPointer);
									} else if (buffer[count2] == '.') {
										fprintf (outputFile, print);
									} else if (buffer[count2] == ',') {
										fprintf (outputFile, get);
									} else if (buffer[count2] == '[') {
										fprintf (outputFile, openWhile);
										addTab++;
									} else if (buffer[count2] == ']') {
										fprintf (outputFile, closeWhile);
										addTab--;
									} else if (buffer[count2] == '\n' || buffer[count2] == '\t' || buffer[count2] == ' ') {
										// Ignore whitespaces
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
							
							fprintf (outputFile, mainReturn);
							fprintf (outputFile, mainFunctionBottom);
							
						fclose (outputFile);
						fclose (inputFile);
						
						sprintf (cmd, "%s \"%s\" %s \"%s\"", compiler_path, outFile, object_switch, exeFile);
						system (cmd);
						
						u_sleep (1000);
						
						remove (outFile);
						compiled = 1;
					} else if (exists == 1) {
						printf (inputFileAccessError);
					} else {
						printf (inputFileNotFound);
					}
				} else {
					printf (noInputFile);
				}
			} else if (strcmp (argv[count], "-x32") == 0 || strcmp (argv[count], "-x64") == 0) {
				if (compiled) {
					printf (resourceAlreadyCompiled);
				} else {
					getPath (NULL, currPath, 99);
					changeSlash (currPath);
					remFileName (currPath);
					strcpy (compiler_path, currPath);
					
					if (strcmp (argv[count], "-x32") == 0) {
						getPath (NULL, currPath, 99);
						changeSlash (currPath);
						remFileName (currPath);
						strcpy (compiler_path, currPath);
						getValue(compiler_path_config, compiler_x32);
						strcat (compiler_path, compiler_path_config);
						indicated = 1;
					} else if (strcmp (argv[count], "-x64") == 0) {
						getPath (NULL, currPath, 99);
						changeSlash (currPath);
						remFileName (currPath);
						strcpy (compiler_path, currPath);
						getValue(compiler_path_config, compiler_x64);
						indicated = 1;
					} else {
						printf ("Error: %d\n", buffer[count2]);
						printf (compileCompilerFailed);
						printf ("Error 0x000005FE\n");
						printf ("Please contact the developer.\n");
						printf ("Terminating compilation.\n");
					}
				}
			} else if (strcmp (argv[count], "-h") == 0 || strcmp (argv[count], "-H") == 0) {
				printf (helpFile);
				break;
			} else {
				printf (invalidCommand);
			}
			
			count++;
		}
	}
	
	return (0);
}

