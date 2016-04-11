#ifndef _ASOC_HH
#define _ASOC_HH

#include <iostream>
#include <string>
#include "hash.hh"


template <class T>
class IAsoc {
public:
	virtual int hash (std::string) = 0;
	virtual ~IAsoc () {}
	friend std::ostream operator << (std::ostream & output, const IAsoc & to) {
		to.print(output);
		return output;
	}
private:
	virtual void print (std::ostream &) = 0;

};

template <class T>
class Asoc : public IAsoc<T>{
private:

public:
};

#endif
