mycache: main.cpp cache.o 
	g++ main.cpp cache.o -o mycache

cache.o: cache.cpp HashTable.o LruList.o
	g++ -c cache.cpp HashTable.o LruList.o

HashTable.o: HashTable.cpp
	g++ -c HashTable.cpp

LruList.o: LruList.cpp
	g++ -c LruList.cpp