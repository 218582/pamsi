#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include "except.hh"
#include "tabl.hh"

enum Colour {red, black};

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
public:
	T key;
	Colour colour;
	class nodeRB<T> * left;
	class nodeRB<T> * right;
	class nodeRB<T> * up;
	
	nodeRB (T elem) {
		colour = black;
		key = elem;
		left = right = up = NULL;
	}
	
	nodeRB (void) {
		left = right = up = NULL;
		colour = black;
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
	virtual nodeRB<T> * search    (nodeRB<T> *, T) = 0;
	virtual nodeRB<T> * searchMin (nodeRB<T> *) = 0;
	virtual nodeRB<T> * searchMax (nodeRB<T> *) = 0;
//	virtual void rightRot (nodeRB<T> *) = 0;
//	virtual void leftRot  (nodeRB<T> *) = 0;
//	virtual void restore (nodeRB<T> *) = 0;
//	virtual void insert(nodeRB<T> *) = 0;
//	virtual void remove(nodeRB<T> *) = 0;

	friend std::ostream & operator << (std::ostream & output, ITreeRB * to) {
		to->print(output);
		return output;
	}
	
};


template <class T>
class TreeRB : public ITreeRB<T> {
private:
	nodeRB<T> * root;
	nodeRB<T> * current;
	nodeRB<T> * sentinel;
public:
	TreeRB () {
		root = current = sentinel = NULL;
	}
	
	virtual ~TreeRB () {

	}	 
	
	
	virtual nodeRB<T> * search (nodeRB<T> * node, T searchKey) {
		while ((node != NULL) and (node->key != searchKey)) {
        	if (searchKey < node->key) {
            	node = node->left;
          	}
        	else {
        	    node = node->right;
        	}
        }
   		return node;
	}
	
	//Element najbardziej po lewej będzie najmniejszy
	virtual nodeRB<T> * searchMin (nodeRB<T> * node) {
		while (node->left != NULL) {
		    node = node->left;
		}
		return node;
    }
    
    //analogicznie
    virtual nodeRB<T> * searchMax (nodeRB<T> * node) {
		while (node->right != NULL) {
		    node = node->right;
		}
		return node;
    }
    
//    virtual void rightRot (nodeRB<T> * node);
//	virtual void leftRot  (nodeRB<T> * node);
//	virtual void restore (nodeRB<T> * node);
//	virtual void insert(nodeRB<T> * node); 
//	virtual void remove(nodeRB<T> * node);
//    	
	
	
	
	virtual void print(std::ostream & out) {
		//coś
	}


};
#endif
