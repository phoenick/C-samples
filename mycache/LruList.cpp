/*

*/
#include "LruList.h"
#include "HashTable.h"

typedef struct {
	
	char *record;
	LruListNodePtr previous;
	LruListNodePtr next;
	//time 
} LruListNode;

typedef struct {
	
	LruListNodePtr first;
	LruListNodePtr last;
	
} LruList;


LruListPtr createLruList() {

	LruListPtr newList = (LruListPtr) malloc(sizeof(LruList));
	if(newList){
		newListPtr->first = NULL;
		newListPtr->last = NULL;
	}
	else{
		return NULL;
	}
}