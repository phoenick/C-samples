/*

*/
#include "HashTable.h"
#include "LruList.h"

typedef struct {

	int size;
	LruListNodePtr *items;

} HashTable;

/* Public */
HashTablePtr createHashTable(int size){
	
	HashTablePtr newHashTable = (HashTablePtr) malloc(sizeof(HashTable));
	if(newHashTable){
		newHashTable->size = size;
		newHashTable->items = (LruListNodePtr *)malloc(size * sizeof(LruListNodePtr));
		for(int i = 0; i < size; i++){
			newHashTable->items[i] = NULL;
		}
		return newHashTable;
	}
	else
		return NULL;

}

LruListNodePtr getItem(HashTablePtr hashTable, int position){
	if(position >= 0 && position < hashTable->size)
		return hashTable->items[position];
	else
		return NULL;
}