#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include "except.hh"
#include "tabl.hh"

template <class T>
class tree_element {
private:
	T element;
	class tree_element<T> * left;
	class tree_element<T> * right;
public:
	
	tree_element (T elem) {
		element = elem;
		left = nullptr;
		right = nullptr;
	}
	
	tree_element (void) {
		element = 0;
		left = nullptr;
		right = nullptr;
	}
	
	~tree_element () {}
	
	
	
	tree_element<T> & operator = (const tree_element<T> & read) {
		element = read.element;
		return * this;
	}
	
	friend bool operator < (tree_element<T> one, tree_element<T> two) {
		if (one.element < two.element) return true;
		else return false;
	}
	
	friend bool operator > (tree_element<T> one, tree_element<T> two) {
		if (one.element > two.element) return true;
		else return false;
	}
	
	friend bool operator <= (tree_element<T> one, tree_element<T> two) {
		if (one.empty || two.empty) return false;
		else if (one.element <= two.element) return true;
		else return false;
	}
	
	friend bool operator >= (tree_element<T> one, tree_element<T> two) {
		if (one.element >= two.element) return true;
		else return false;
	}
	
	friend std::ostream & operator << (std::ostream & output, const tree_element<T> & to) {
			output <<  to.element;
			return output;
	}
	
	friend std::istream & operator >> (std::istream & input, const tree_element<T> & to) {
		if(input.eof()) {
			input.setstate(std::ios::eofbit);
		}
		else {
			T elem;
			input >> elem;
			to.element = elem;
		}
		return input;
	}
};

template <class T>
class ITree {
private:
	virtual void print(std::ostream &) = 0;
public:
	virtual void add(T) = 0;
//	virtual T read(T) = 0;

	friend std::ostream & operator << (std::ostream & output, ITree * to) {
		to->print(output);
		return output;
	}
	
};


template <class T>
class Tree : public ITree<T> {
private:
	tree_element<T> * top;
public:
	Tree () {
		top = nullptr;
	}
	
	~Tree () {

	}	 
	
	virtual void add(T elem) {
		
	}
	
	
	virtual void print(std::ostream & out) {
		//coś
	}
	
//	virtual T read(T elem) {
//		return ;
//	}
	
	
};
#endif
