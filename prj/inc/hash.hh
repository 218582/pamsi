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
	
	entry () {
	}
	
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
	
	entry<T,T2> & operator = (const entry<T,T2> & read) {
		key=read.key;
		value=read.value;
		return * this;
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
		output <<  '\t' << to.key << " : " << to.value;
		return output;
	}
	
	friend std::istream & operator >> (std::istream & input, const entry<T,T2> & to) {
		if(input.eof()) {
			input.setstate(std::ios::eofbit);
		}
		else {
			T temp;
			T2 temp2;
			input >> temp >> temp2;
			to.key = temp;
			to.value = temp2;
		}
		return input;
	}
};



template <class T, class T2>
class IBucket : public entry<T,T2>{
public:
	virtual void add(entry<T,T2>) = 0;
	virtual T2 remove(T) = 0;
//	virtual void reassign(entry<T,T2>) = 0;
	virtual T2 lookup(T) = 0;
	virtual Itabn<T2> * lookupWhole (T)=0;
	virtual ~IBucket () {}	
	virtual void printAllElements() = 0;
	virtual int getID(void) = 0;
	virtual void printFoundElements(void) = 0;
};






template <class T, class T2>
class Bucket : public IBucket<T,T2>{
private:
	Itabn<entry<T,T2>> * tablica;

	int bucketID;
public:

	Itabn<T2> * temp;
	
	Bucket (): tablica (new tabn<entry<T,T2>>), temp (new tabn<T2>) {
		bucketID = 99;
	}
	
	Bucket (int ID) : tablica (new tabn<entry<T,T2>>), temp (new tabn<T2>) {
		bucketID = ID;
	}
	
	~Bucket () {
		//delete [] tablica;
		//delete temp;
	}
	
	virtual int getID(void) {
		return bucketID;
	}
	
	virtual void printAllElements() {
		tablica->showElems();
	}
	
	virtual void printFoundElements(void) {
		temp->showElems();
	}
	
	virtual void add(entry<T,T2> Ent) {
		try {
			tablica->add(Ent);
		}
		catch (...) {
			throw;
		}
	}
	
	virtual T2 remove(T position) {
		T2 temporary;
		try {
			for (int i=0; i<tablica->nOE(); i++) {
				if (tablica->show(i).getKey() == position) {
					temporary = tablica->show(i).getVal();
					tablica->remove(i);
					return temporary;
				}
			}
			throw CriticalException("ElementToRemoveFromBucketNotFound");
		}
		catch (...) {
			throw;
		}
	}
	
	
	virtual T2 lookup (T position) {
		try {
			for (int i=0; i<tablica->nOE(); i++) {
				if (tablica->show(i).getKey() == position) {
					return tablica->show(i).getVal();
				}
			}
			throw ContinueException("ElementNotFound");
		}
		catch (...) {
			throw;
		}
	}
	
	virtual Itabn<T2> * lookupWhole (T position){		
		try {
			if (temp->nOE()!=0) {
				for (int i=0; i<((temp->nOE())-1);i++) {
					temp->remove();
				}
			}
			for (int i=0; i<tablica->nOE(); i++) {
				if (tablica->show(i).getKey() == position) {
					//std::cout << tablica->show(i).getVal() << std::endl;
					temp->add(tablica->show(i).getVal());
				}
			}
			if (temp->nOE()==0) {
				throw ContinueException("ElementNotFound");
			}
		}
		catch (...) {
			throw;
		}
		return temp;
	}
	
	
	 
	
	
};
#endif
