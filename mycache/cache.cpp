#include <cstdio>
#include "HashTable.h"
#include "LruList.h"
using namespace std;

typedef struct {

	HashTablePtr hashTable;
	LruListPtr lrulist;
	char *fileName;
	int size;
	
} Cache;

/* Public */
CachePtr createCache(int size, char *fileName){
	
	CachePtr newCache = (CachePtr)malloc(sizeof(Cache));
	newCache->hashTable = createHashTable(size);
	newCache->lrulist = createLruList();
	newCache->filename = fileName;
	newCache->size = size;
	
}

/* Private */
char * findPhoneNumInFile(CachePtr cache, char *givenPhoneNum){// returns the rest information (name, adress etc) 
													//of the record corresponding to the given phone number or NULL
													//if nothing is found
	
	FILE *file;
	file = fopen(cache->fileName, “r”) ;
	
	char *line = (char *)malloc(129*sizeof(char));
	
	while(fgets(line, 128, file) != NULL){
		char *token;
		token = strtok(line, ";");
		if(strcmp((const char*)givenPhoneNum, (const char*)token) == 0){
			return strtok(NULL, "\n"); 
		}
		else
			continue;
	
	
	}
	
	return NULL; //did not find anything
}

char * getRecord(CachePtr cache, char *givenPhoneNum){
	/*
		Search First in Cache
	*/
	int position;
	long hashKey;
	hashKey = (long) atoi((const char*)givenPhoneNum);
	
	/*
		the following code uses a very simple hash function but we believe
		it should work just fine because we consider that the given
		phone numbers are randomly generated. But in case it does not
		work efficiently, we use quadratic probing to solve the collisions,
		so the system, in the end, should work efficiently enough
	*/
	
	for(int i = 0; i < cache->size; i++){
	
		position = (int)((hashKey + i * i) % (long) cache->size); 
		
		LruListNodePtr item = getItem(cache->hashTable, position);
		if(item){
			if(strcmp((const char*)givenPhoneNum, (const char*)getPhoneNumber(item)) == 0){
			
			
			}
			else
				continue;
		}
		else
			continue;
	}

}



