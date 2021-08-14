#include "bf_filemap.h"

/**
	* Change backward slash to forward slash
*/
void
changeSlash (char *pathname)
{
	int count = 0;
	
	/* Traverse string and change all occurence of backslash to forward slash */
	for (count = 0; count < MAX_BUF; count++) {
		if (pathname[count] == '\\') {
			pathname[count] = '/';
		}
	} // for traverse
	
	return; /* Optional Return Statement */
} // changeSlash()

/**
	* Check if the file exists and readable
*/
int 
checkFile (const char *filename) 
{
	int exists = 0;
	const short int accessCheck = -1;
	
	/* Check if we can access file */
	if (access(filename, F_OK) != accessCheck) {
		exists++;
		
		/* Check if we can read or write to the file */
		if (access(filename, R_OK) != accessCheck) {
			exists++;
		} // if readable
	} // if exist
	
	return (exists);
} // checkFile()

/**
	* Check file extension
*/
int 
_extCheck (char *filename) 
{
	int isValid = 0;
	char extension [MAX_BUF] = {"\0"};
	char fileonly [MAX_BUF] = {"\0"};
	
	/* Get filename and remove extensions, then append ".bf" at the end of string */
	sscanf (filename, "%[^.]s", fileonly);
	strcat (fileonly, ".bf");
	
	/* Check whether they match of not */
	if (strcmp (fileonly, filename) == 0) {
		// ignore and proceed
	} else {
		sscanf (filename, "%[^.]s", fileonly);
		strcat (fileonly, ".BF");
		
		/* Ignore case in comparison */
		if (strcmp (strupr(fileonly), strupr(filename)) == 0) {
			// ignore and proceed
			isValid = 0;
		} else {
			isValid = 1;
			printf (invalidFileExt);
		}
	}
	
	return (isValid);
} // extCheck()

char * 
getDefaultCompilerPath (void)
{
	FILE *configFile;
	char buffer[MAX_BUF] = {"\0"};
	char readField[MAX_BUF] = {"\0"};
	char data[MAX_BUF] = {"\0"};
	char configPath [MAX_BUF] = {"\0"};
	char value[MAX_BUF] = {"\0"};
	char field[MAX_BUF] = {"\0"};
	
	char currPath [MAX_BUF] = {"\0"};
	char compiler_path [MAX_BUF] = {"\0"};
	char compiler_path_config [MAX_BUF] = {"\0"};
	char * complete_compiler_path = {"\0"};
	
	getPath (NULL, configPath, 99);
	changeSlash (configPath);
	remFileName (configPath);
	strcat (configPath, "/config.cfg");
	
	/////////////////////////
	
	getPath (NULL, currPath, 99);
	changeSlash (currPath);
	remFileName (currPath);
	strcpy (compiler_path, currPath);
	
	configFile = fopen(configPath, "r");
		while (fgets(buffer, sizeof(buffer), configFile) != NULL) {
			sscanf (buffer, "%[^=]=%s", readField, data);
			buffer[strlen(buffer) - 1] = '\0';
			if (strcmp (readField, compiler_x32) == 0) {
				strcpy (value, data);
				break;
			} else {
				continue;
			}
		}
	fclose(configFile);
	
	strcat (compiler_path, compiler_path_config);
	complete_compiler_path = compiler_path;
	strcpy (complete_compiler_path, compiler_path);
	strcat (complete_compiler_path, data);
	
	return (complete_compiler_path);
}

/**
	* Remove file name in path
*/
void
remFileName (char *pathname) 
{
	int count = 0;
	int last = 0;
	
	// find the last occurence of slash
	for (count = 0; count < MAX_BUF; count++) {
		if (pathname [count] == '/') {
			last = count;
		}
	}
	
	for (count = last; count < MAX_BUF; count++) {
		pathname [last] = '\0';
	}
} // remFileName()

