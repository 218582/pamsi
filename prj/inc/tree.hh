#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include "except.hh"
#include "tabl.hh"

enum Colour {red, black};

std::ostream & operator << (std::ostream &, Colour);
	
	
/* \brief Klasa definiująca obiekt typu node dla drzewa czerwono-czarnego
*/

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
	
	T getLeftKey (void) {
		if (left != NULL)
			return left->getKey();
		else
			return 0;
	}
	
	T getRightKey (void) {
		if (right != NULL)
			return right->getKey();
		else
			return 0;	
	}
	
	T getUpKey (void) {
		if (up != NULL)
			return up->getKey();
		else
			return 0;
	}
	
	void setKey (T keyToSet) {
		key = keyToSet;
	}
	
	void setColour (Colour colourToSet) {
		colour = colourToSet;
	}
	
	void setLeft (nodeRB<T> * leftDescendant) {
		left = leftDescendant;
	}
	
	void setRight (nodeRB<T> * rightDescendant) {
		right = rightDescendant;
	}
	
	void setUp (nodeRB<T> * parent) {
		up = parent;
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
