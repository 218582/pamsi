#ifndef _HASH_HH
#define _HASH_HH

#include <iostream>
#include <string>
#include "lista.hh"



template <class T>
class entry {
public:
	std::string name;
	T data;
};

template <class T>
class IHash : public entry<T>{
public:
	virtual void add(int,entry<int>) = 0;
	virtual T find(std::string) = 0;
	virtual ~IHash () {}	
};

template <class T>
class Hash : public IHash<T>, public entry<T>{
private:
	Itabn<entry<int>> * tablica;
	int numberOfBuckets=0;
public:
	Hash (int nOBuckets) : tablica (new tabn<entry<int>>) {
		numberOfBuckets = nOBuckets;
	}
	
	virtual void add(int bucket, entry<int> ent) {
	if (bucket<=numberOfBuckets) {
		tablica->add(ent,bucket);
	}
	else throw ContinueException("Bucket number wrong!");
	}

};
#endif
