#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include "except.hh"
#include "tabl.hh"
#include "run.hh"

/*!
 *\brief Kolory node'a drzewa czerwono-czarnego
 */
enum Colour {red, black};

/*!
 *\brief Wyświetlanie koloru node'a
 */
std::ostream & operator << (std::ostream &, Colour);
	
	
/* \brief Klasa definiująca obiekt typu node dla drzewa czerwono-czarnego
*/
template <class T>
class nodeRB {
public:
	T key;
	Colour colour;
	class nodeRB<T> * left;
	class nodeRB<T> * right;
	class nodeRB<T> * up;

public:
	/*!
	 *\brief brief_desc
	 */
	 
	nodeRB (T addKey, Colour col = red, nodeRB<T> * addUp = NULL, nodeRB<T> * addLeft = NULL, nodeRB<T> * addRight = NULL) {
		key = addKey;
		up = addUp;
		left = addLeft;
		right = addRight;
		colour = col;
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
	
	nodeRB<T> * getParent (void) {
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
	
	T getParentKey (void) {
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
	
	void setParent (nodeRB<T> * parent) {
		up = parent;
	}
	
	nodeRB<T> & operator = (const nodeRB<T> & read) {
		key = read.key;
		colour = read.colour;
		left = read.left;
		right = read.right;
		up = read.up;
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
	
	friend bool operator == (nodeRB<T> one, nodeRB<T> two) {
		if (one.key == two.key) return true;
		else return false;
	}
	
	friend std::ostream & operator << (std::ostream & output, const nodeRB<T> * to) {
			output <<  to->key << " " << to->colour << " ";
			if (to->up == NULL) {
				output << "ROOT\n";
			}
			else {
				output << "C: " << to->up->key << " " << to->up->colour;
			}
			return output;
	}
	
	friend std::istream & operator >> (std::istream & input, const nodeRB<T> * to) {
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


/*!
 *\brief Interfejs klasy drzewa czerwono-czarnego
 */
template <class T>
class ITreeRB {
private:
	virtual void print (std::ostream &)=0;
public:
	virtual void insert (T) = 0;
	virtual void insert (T, nodeRB<T> *) =0;
	virtual bool search (T) = 0;
	virtual ~ITreeRB () {};
	
	friend std::ostream & operator << (std::ostream & output, ITreeRB * to) {
		to->print(output);
		return output;
	}
		
};

/*!
 *\brief Klasa implementująca interfejs drzewa czerwono-czarnego
 */
template <class T>
class TreeRB : public ITreeRB<T> {

private: 
	nodeRB<T> * root;
	
	void print (std::ostream & output) {
		print (output, root);
	}
	
	//Wyświetlanie elementów drzewa
	void print (std::ostream & output, nodeRB<T> * node) {
		if (root->left==NULL && root->right==NULL && root->up==NULL) {
			output << "Empty tree\n";
			return;
		}
		else {
			if (node != NULL) {
				output << node;
				output << '\n';
				if (node->left != NULL) {
					print(output, node->left);
				}
				if (node->right != NULL) {
					print(output,node->right);
				}
				output << '\n';
			}
		}
	}
	
	/*!
	 *\brief Obraca wybrane poddrzewo w lewo
	 */
	void leftRot (nodeRB<T> * nd) {
		if (nd->right !=NULL) { //Warunek rotacji
			nodeRB<T> * y = nd->right;
			
			//Przypisanie lewego syna prawego syna nd do bycia prawym synem nd obróconego drzewa
			if (y->left!=NULL) {
				nd->right=y->left;
				y->left->up = nd;
			}
			else {
				nd->right=NULL;
			}
			
			//Ustalenie prawego syna nd jako roota poddrzewa obróconego
			if (nd->up!=NULL) {
				y->up = nd->up;
			}
			if (nd->up == NULL) { 
				root = y;
			}
			
			//Edycja wskaźnika rodzica poddrzewa obracanego
			else {
				if(nd==nd->up->left) nd->up->left = y;
				else nd->up->right = y;
			}
			
			//Podpięcie elementu nd jako dziecka obecnego roota poddrzewa
			y->left = nd;
			nd->up=y;
		}
	}
	
	void rightRot (nodeRB<T> * nd) {
		if (nd->left != NULL) { //Warunek rotacji
			nodeRB <T> * y = nd->left;
			
			//Przypisanie prawego syna lewego syna nd do bycia lewym synem nd obróconego drzewa
			if (y->right != NULL) {
				nd->left = y->right;
				y->right->up = nd;
			}
			else {
				nd->left = NULL;
			}
			
			//Ustalenie lewego syna nd jako roota poddrzewa obróconego
			if (nd->up == NULL) {
				y->up = nd->up;
			}
			if (nd->up == NULL) {
				root = y;
			}
			
			//Edycja wskaźnika rodzica poddrzewa obracanego
			else {
				if (nd==nd->up->left) {
					nd->up->left = y;
				}
				else {
					nd->up->right = y;
				}
			}
			
			//Podpięcie elementu nd jako dziecka obecnego roota poddrzewa
			y->right = nd;
			nd->up = y;
		}
	}
	
public:

	/*!
	 *\brief Konstruktor
	 */
	TreeRB () : root(NULL) {
	}
	
	/*!
	 *\brief Destruktor
	 */
	 virtual ~TreeRB () {
	 	delete root;
	 }
	
	/*!
	 *\brief Wstawia element do drzewa
	 *\warning Nowy element jest domyślnie zakolorowany na czerwono (patrz konstruktor nodeRB() )
	 */
	virtual void insert (T element) {
		insert(element, root);
	}
	
	
	virtual void insert (T element, nodeRB<T> * node) {

		//Jeśli wstawiamy pierwszy element do drzewa
		if (node==NULL) {
			root = new nodeRB<T>(element,black);
			return;
		}
		
		//Wstawienie
		if (node->left == NULL && element < node->key) {
			node->setLeft(new nodeRB<T>(element,red,node));
		}
		else if (node->right == NULL && element > node->key) {
			node->setRight(new nodeRB<T>(element,red,node));
		}
		else if (node->left != NULL && element < node->key) {
			insert(element, node->left);
		}
		else if (node->right != NULL && element > node->key) {
			insert(element, node->right);
		}
	}
	
	virtual bool search (T k) {
		bool found = false;
		nodeRB<T> * current = root;
		if (root == NULL) {
			throw CriticalException("EmptyTreeCannotSearch");
			return false;
		}
		while (found==false && current != NULL) {
			if (current->key == k) found = true;
			if (found==false) {
				if (current->key > k) {
					current = current->left;
				}
				else current = current->right;
			}
		}
		if (found == true) return true;
		else return false;
	}
	
};



#endif
