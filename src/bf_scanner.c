#include "bf_scanner.h"

/**
	* Lexically check the characters in the file
*/
unsigned short int 
_charCheck (char *filename) 
{	
	FILE *file;
	char check [MAX_BUF] = {"\0"};
	int count = 0;
	int line = 0;
	int isValid = 0;
	
	file = fopen (filename, "r+");
	
		while (fgets (check, MAX_BUF, file) != NULL) {
			line++;
			for (count = 0; count < MAX_BUF; count++) {
				if (check[count] == '<' || 
					check[count] == '>' || 
					check[count] == '+' || 
					check[count] == '-' || 
					check[count] == '.' || 
					check[count] == ',' || 
					check[count] == '[' || 
					check[count] == ']' ||
					check[count] == ' ' ||
					check[count] == '\n' || 
					check[count] == '\t' ||
					check[count] == '\0') {
					// ignore and continue
					continue;
				} else {
					isValid = 1;
					printf ("BFC.EXE: (Unkown character: '%c' on Line %d Column %d)\n", check[count], line, count);
				}
			}
		}
	
	fclose (file);
	
	return (isValid);
}

/**
	* Check the if present in the file
*/
unsigned short int 
_loopCheck (char *filename) 
{
	FILE *file;
	char check [MAX_BUF] = {"\0"};
	int isValid = 0;
	int openBracket = 0;
	int closeBracket = 0;
	int count = 0;
	int line = 0;
	
	file = fopen (filename, "r+");
		while (fgets (check, MAX_BUF, file) != NULL) {
			line++;
			for (count = 0; count < MAX_BUF; count++) {
				if (check[count] == '[') {
					openBracket++;
				} else if (check[count] == ']') {
					closeBracket++;
				}
				
				if (closeBracket > openBracket) {
					printf ("BF.EXE: Invalid symbol ']' in line %d column %d.", line, count);
				}
			}
		}
	fclose (file);
	
	if (openBracket > closeBracket) {
		isValid = 1;
		printf ("BFC.EXE: (Reached end of file while parsing. No matching ']' found. )\n");
	} else if (openBracket < closeBracket) {
		isValid = 1;
		printf ("BFC.EXE: (Reached end of file while parsing. No matching '[' found. )\n");
	} else {
		// ignore and proceed
	}
	
	return (isValid);
}

/**
	* Check passes in the source file
*/
unsigned short int 
passCheck (char *filename)
{
	short unsigned int passed = 0;
	short unsigned int pass1Check = 0;
	short unsigned int pass2Check = 0;
	short unsigned int pass3Check = 0;
	
	pass1Check = _extCheck(filename);
	pass2Check = _charCheck(filename);
	pass3Check = _loopCheck(filename);
	
	if (pass1Check == 1 && pass2Check == 1 && pass3Check == 1) {
		passed = 1;
	}
	
	return (passed);
}
