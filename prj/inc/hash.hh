#ifndef _HASH_HH
#define _HASH_HH

#include <iostream>
#include <string>
#include "lista.hh"

/*!
 *\brief Klasa definująca obiekt typu wpis
 */

template <class T, class T2>
class entry {
private:
	T key;
	T2 value;
public:
	
	entry(T entryKey, T2 entryData) {
		key = entryKey;
		value = entryData;
	}
	
	//~entry () {}
	
		
	T2 getVal (void) {
		return value;
	}
	
	T getKey (void) {
		return key;
	}
	
	friend bool operator < (entry<T,T2> one, entry<T,T2> two) {
		if (one.key < two.key) return true;
		else return false;
	}
	
	friend bool operator > (entry<T,T2> one, entry<T,T2> two) {
		if (one.key > two.key) return true;
		else return false;
	}
	
	friend bool operator <= (entry<T,T2> one, entry<T,T2> two) {
		if (one.key <= two.key) return true;
		else return false;
	}
	
	friend bool operator >= (entry<T,T2> one, entry<T,T2> two) {
		if (one.key >= two.key) return true;
		else return false;
	}
	
	friend std::ostream & operator << (std::ostream & output, const entry<T,T2> & to) {
		output << to.key << " " << to.value;
		return output;
	}
};



template <class T, class T2>
class IBucket : public entry<T,T2>{
public:
	virtual void add(entry<T,T2>) = 0;
	virtual T2 remove(T) = 0;
	virtual void reassign(entry<T,T2>) = 0;
	virtual T2 lookup(T) = 0;
	virtual ~IBucket () {}	
};

template <class T, class T2>
class Bucket : public IBucket<T,T2>{
private:
	Itabn<entry<T,T2>> * tablica;
	int bucketID;
public:
	Bucket (int ID) : tablica (new tabn<entry<T,T2>>) {
		bucketID = ID;
	}
	virtual void add(entry<T,T2> Ent) {
		tablica->add(Ent);
	}
	
//	virtual void add(int bucket, T ent) {
//		if (bucket<=numberOfBuckets) {
//			tablica->add(ent,bucket);
//		}
//		else throw ContinueException("Bucket number wrong!");
//	}

	
	
	
	

};
#endif
