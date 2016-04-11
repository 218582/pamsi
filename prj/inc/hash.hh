#ifndef _HASH_HH
#define _HASH_HH

#include <iostream>
#include <string>
#include "lista.hh"



template <class T>
class entry {
private:
	std::string name;
	T data;
public:
	entry() {
		name = "no name";
	}
	entry(std::string entryName, T entryData) {
		name = entryName;
		data = entryData;
	}
	
	~entry () {}
	
	//Potrzeba operatorów porównania
	friend bool operator < (entry<T> one, entry<T> two) {
		if (one.name < two.name) return true;
		else return false;
	}
	
	friend bool operator > (entry<T> one, entry<T> two) {
		if (one.name > two.name) return true;
		else return false;
	}
	
	friend bool operator <= (entry<T> one, entry<T> two) {
		if (one.name <= two.name) return true;
		else return false;
	}
	
	friend bool operator >= (entry<T> one, entry<T> two) {
		if (one.name >= two.name) return true;
		else return false;
	}
	
//	void printEntry (void) {
//		std::cout << "Record: "<< name << " : " << data << std::endl; 
//	}
	
	friend std::ostream & operator << (std::ostream & output, const entry<T> & to) {
		return outuput; //Do zmiany ofc
	}
};

template <class T>
class IHash : public entry<T>{
public:
	virtual void add(int,entry<int>) = 0;
	virtual T find(std::string) = 0;
	virtual ~IHash () {}	
};

template <class T>
class Hash : public IHash<T>{
private:
	Itabn<T> * tablica;
	int numberOfBuckets=0;
public:
	Hash (int nOBuckets) : tablica (new tabn<T>) {
		numberOfBuckets = nOBuckets;
	}
	
	virtual void add(int bucket, T ent) {
		if (bucket<=numberOfBuckets) {
			tablica->add(ent,bucket);
		}
		else throw ContinueException("Bucket number wrong!");
	}
	virtual T find(std::string) {
		return tablica->show(0);
	}
	
	
	
	

};
#endif
