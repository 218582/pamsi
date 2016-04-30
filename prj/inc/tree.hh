#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include "except.hh"
#include "tabl.hh"

enum Colour {red, black};

std::ostream & operator << (std::ostream &, Colour);
	
//Colour & operator ++(Colour & col) {
//	switch (col) {
//		case red: return col = black; break;
//		case black: return col = red; break;
//	}
//	throw CriticalException("WrongOperatorPPColour");
//	return col;
//}

//Colour operator++(Colour& col, int)
//{
//  Colour temp(col);
//  ++col;
//  return temp;
//}

template <class T>
class nodeRB {
private:
	T key;
	Colour colour;
	class nodeRB<T> * left;
	class nodeRB<T> * right;
	class nodeRB<T> * up;

public:
	nodeRB (T addKey, nodeRB<T> * addUp = NULL, nodeRB<T> * addLeft = NULL, nodeRB<T> * addRight = NULL) {
		key = addKey;
		up = addUp;
		left = addLeft;
		right = addRight;
		colour = black;
	}
	
	T getKey (void) {
		return key;
	}
	
	Colour getColour (void) {
		return colour;
	}
	
	nodeRB<T> * getLeft (void) {
		return left;
	}
	
	nodeRB<T> * getRight (void) {
		return right;
	}
	
	nodeRB<T> * getUp (void) {
		return up;
	}
	
	
	nodeRB<T> & operator = (const nodeRB<T> & read) {
		key = read.key;
		colour = read.colour;
		return * this;
	}
	
	friend bool operator < (nodeRB<T> one, nodeRB<T> two) {
		if (one.key < two.key) return true;
		else return false;
	}
	
	friend bool operator > (nodeRB<T> one, nodeRB<T> two) {
		if (one.key > two.key) return true;
		else return false;
	}
	
	friend bool operator <= (nodeRB<T> one, nodeRB<T> two) {
		if (one.empty || two.empty) return false;
		else if (one.key <= two.key) return true;
		else return false;
	}
	
	friend bool operator >= (nodeRB<T> one, nodeRB<T> two) {
		if (one.key >= two.key) return true;
		else return false;
	}
	
	friend std::ostream & operator << (std::ostream & output, const nodeRB<T> & to) {
			output <<  to.key;
			return output;
	}
	
	friend std::istream & operator >> (std::istream & input, const nodeRB<T> & to) {
		if(input.eof()) {
			input.setstate(std::ios::eofbit);
		}
		else {
			T elem;
			input >> elem;
			to.key = elem;
		}
		return input;
	}
};



template <class T>
class ITreeRB {
private:
	virtual void print(std::ostream &) = 0;
public:
//	virtual nodeRB<T> * search    (nodeRB<T> *, T) = 0;
//	virtual nodeRB<T> * searchMin (nodeRB<T> *) = 0;
//	virtual nodeRB<T> * searchMax (nodeRB<T> *) = 0;
//	virtual void rightRot (nodeRB<T> *) = 0;
//	virtual void leftRot  (nodeRB<T> *) = 0;
//	virtual void restore (nodeRB<T> *) = 0;
//	virtual void insert(nodeRB<T> *) = 0;
//	virtual void remove(nodeRB<T> *) = 0;

//	friend std::ostream & operator << (std::ostream & output, ITreeRB * to) {
//		to->print(output);
//		return output;
//	}
	
};


template <class T>
class TreeRB : public ITreeRB<T> {


};
#endif
