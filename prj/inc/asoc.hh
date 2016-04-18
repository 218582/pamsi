#ifndef _ASOC_HH
#define _ASOC_HH

#include <iostream>
#include <string>
#include <functional>
#include <numeric>
#include "hash.hh"
#include "run.hh"
#include <ctime>
#include <chrono>


template <class T, class T2>
class IAsoc {
private:
	virtual void print (std::ostream &)=0;
public:
	virtual void add(T, T2) = 0;
//	virtual void remove (T) = 0;
private:
	virtual int hash (T) = 0;
public:
	virtual ~IAsoc () {}
	virtual Itabn<T2> * find (T) = 0;
	virtual T2 findOne (T) = 0;
	
	friend std::ostream & operator << (std::ostream & output, IAsoc * to) {
		to->print(output);
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
	
	~Asoc () {
		delete buckets;
	}
private:
	virtual void print (std::ostream & output) {
		for (int i=0; i<numberOfBuckets; i++) {
			output << "Bucket " <<  buckets->operator[](i).getID() << '\n';
			buckets->show(i).printAllElements();
		}
	}
	
private:
	virtual int hash (T key) {
		return std::accumulate(key.begin(),key.end(),0)%(numberOfBuckets);
	}
	
public:
	virtual void add(T key, T2 val) {
		entry<T,T2> newElem(key,val);
		buckets->operator[](hash(key)).add(newElem);
	}
	
	virtual Itabn<T2> * find (T position){
		return buckets->operator[](hash(position)).lookupWhole(position);
	}
	
	virtual T2 findOne (T position) {
		return buckets->operator[](hash(position)).lookup(position);
	}
	
};




class asoc_test : public IRunnable {
private:
	IAsoc<std::string,int> * t_asoc;
	int counter;
	std::fstream plik;
	std::string toFind;
	double randomShift = 0;
	
public:
	asoc_test () {
		counter = 0;
	}
	asoc_test (int sizeOfTest){ 
		t_asoc = new Asoc<std::string, int>((int)(sizeOfTest < 100 ? 10 : sizeOfTest < 10000 ? sizeOfTest/100 : sizeOfTest/1000));
		counter = sizeOfTest;
	}
	
	~asoc_test () {
		plik.close();
		delete t_asoc;
	}
	
	
	virtual bool prepare (int sOT) {
		counter = sOT;
//		std::cout << t_asoc;
	
		int i = 0;
		std::string keydb;
		int datadb;
		plik.open("data.txt",std::ios::in);
		if (plik.good() == true) {
			while (plik >> keydb >> datadb && i<counter) {
				t_asoc->add(keydb,datadb);
				i+=1;
				if (i==counter-(counter/2)) {
					toFind = keydb;
				}
			}
			plik.close();
			//std::cout << t_asoc;
			return true;
		}
		else {
			plik.close();
			throw CriticalException("FileError");
		}
		return true;
	}
	
	/*!
	 * \brief Przeprowadzanie badań
	 */
	virtual bool run () {
		try {
			t_asoc->findOne(toFind);
		}
		catch (...) {
			throw;
		}
		return true;
	}
};


#endif
