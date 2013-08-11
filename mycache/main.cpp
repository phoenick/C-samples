/*

*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;



int main(int argc, char* argv[]) {

	if(argc != 5){
		printf("Invalid arguments! Usage: ./mycache -n NumOfRecords -f FileWithPhones");
		return 1;
	}
	
	if((strcmp("-n", (const char*)argv[1]) != 0) || (strcmp("-f", (const char*)argv[3]) != 0)){
		printf("Invalid arguments! Usage: ./mycache -n NumOfRecords -f FileWithPhones");
		return 1;
	}
	
	char *loadedFileName = 	argv[4];
	int cacheSize = atoi((const char*)argv[2]);
	
	char line[32];
	char *command;
	char *cmdArgument;
	
	while(1){
		printf("cmd>");
		gets(line);
		
		command = strtok(line, " ");
		if(strcmp("e", (const char*)command) == 0){
			printf("Thank you for using mycache. See you again!\n");
			return 0;
		}
		else if(strcmp("r", (const char*)command) == 0){
			char *phoneNum = strtok(NULL, " ");
		}
		else if(strcmp("r", (const char*)command) == 0){
			loadedFileName = strtok(NULL, " ");
		}
		putchar('\n');
	}
	
	return 0;
}