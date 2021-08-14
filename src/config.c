#include "config.h"

/**
	* This function gets the value of the configuration files
*/
char *
getValue(char *value, const char *field)
{
	FILE *configFile;
	char buffer[MAX_BUF] = {"\0"};
	char readField[MAX_BUF] = {"\0"};
	char data[MAX_BUF] = {"\0"};
	char configPath [MAX_BUF] = {"\0"};
	
	getPath (NULL, configPath, 99);
	changeSlash (configPath);
	remFileName (configPath);
	strcat (configPath, "/config.cfg");
	
	configFile = fopen(configPath, "r");
		while (fgets(buffer, sizeof(buffer), configFile) != NULL) {
			sscanf (buffer, "%[^=]=%s", readField, data);
			buffer[strlen(buffer) - 1] = '\0';
			if (strcmp (readField, field) == 0) {
				strcpy (value, data);
				break;
			} else {
				continue;
			}
		}
	fclose(configFile);
	
	return (value);
}

