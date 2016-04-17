#ifndef _ASOC_HH
#define _ASOC_HH

#include <iostream>
#include <string>
#include "hash.hh"


template <class T, class T2>
class IAsoc {
public:
	virtual void print (std::ostream &)=0;
public:
	virtual void add(T, T2) = 0;
//	virtual void remove (T) = 0;
private:
	virtual int hash (T) = 0;
public:
	virtual ~IAsoc () {}
	friend std::ostream operator << (std::ostream & output, const IAsoc & to) {
		to.print(output);
		return output;
	}
};

template <class T, class T2>
class Asoc : public IAsoc<T,T2>{
private:
	int numberOfBuckets;
	Itabn<Bucket<T,T2>> * buckets;
public:
	Asoc (int nOBuckets) : buckets (new tabn<Bucket<T,T2>>) {
		numberOfBuckets = nOBuckets;
		for (int i=0;i<nOBuckets;i++) {
			Bucket <T,T2> buck(i);
			buckets->add(buck);
		}
	}
	
	virtual void print (std::ostream & output) {
		for (int i=0; i<numberOfBuckets; i++) {
			output << "Bucket " << i << '\n';
			output << '\t' << buckets->show(i) << '\n';
		}
	}
private:
	virtual int hash (T key) {
		return 0; //ZASTĄPIĆ FUNKCJĄ HASZUJĄCĄ
	}
public:
	virtual void add(T key, T2 val) {
		entry<T,T2> newElem(key,val);
		buckets->operator[](hash(key)).add(newElem);
	}
	
	
};

#endif
