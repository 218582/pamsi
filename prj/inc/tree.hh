#ifndef _TREE_HH
#define _TREE_HH
#include <iostream>
#include <ctime>
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
	//int balanceFactor;
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
		//balanceFactor = 0;
	}
	
	T getKey (void) {
		return key;
	}
	
	Colour getColour (void) {
		if (this==NULL) {
			return black;
		}
		else return colour;
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
		if (this==NULL) return;
		colour = colourToSet;
	}
	
	void setLeft (nodeRB<T> * leftDescendant) {
		left = leftDescendant;
	}
	
	void setRight (nodeRB<T> * rightDescendant) {
		right = rightDescendant;
	}
	
	void setParent (nodeRB<T> * up) {
		up = up;
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
			if (to->up == NULL) {
				output << "\n\n" << to->key << " " << to->colour << " " << "ROOT\n";
			}
			else {
				output << to->key << to->colour << " ";
				if (to->up->left == to)
					output << "L: " << to->up->key << to->up->colour;
				else if (to->up->right == to)
					output << "R: " << to->up->key << to->up->colour;
				else
					output << "U: " << to->up->key << to->up->colour;
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
	virtual void leftRot (nodeRB<T> *) = 0;
	virtual void rightRot (nodeRB<T>* ) = 0;
	virtual nodeRB<T> * retRoot (void) = 0;
	
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
private:
	void print (std::ostream & output) {
		print (output, root);
	}
	
	//Wyświetlanie elementów drzewa
	void print (std::ostream & output, nodeRB<T> * node) {
		if (root==NULL) {
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
				//output << '\n';
			}
		}
	}
	
	int height (nodeRB<T> * nd) {
		if (nd == NULL) return 0;
		else {
			int leftdepth = height(nd->left);
			int rightdepth = height(nd->right);
			if (leftdepth>rightdepth) return leftdepth + 1;
			else return rightdepth + 1;
		}
	}
	

	
public:
	
	virtual nodeRB<T> * retRoot (void) {
		return root;
	}

	/*!
	 *\brief Obraca wybrane poddrzewo w lewo
	 *\param in element najstarszy do obrotu
	 */
	virtual void leftRot (nodeRB<T> * nd) {
	
		if (nd->right !=NULL) { //Warunek rotacji
			nodeRB<T> * y = nd->right;
			
			//Edycja wskaźnika rodzica poddrzewa obracanego
			if (nd->up == NULL) { 
				root = y;
				y->up = NULL;
			}
			else {
				nodeRB<T> * par = nd->up;
				if(nd==nd->up->left) nd->up->left = y;
				else nd->up->right = y;
				y->up = par;
			}
			
			//Przypisanie lewego syna prawego syna nd do bycia prawym synem nd obróconego drzewa
			if (y->left!=NULL) {
				nd->right=y->left;
				y->left->up = nd;
			}
			else {
				nd->right=NULL;
			}
			
			//Podpięcie elementu nd jako dziecka obecnego roota poddrzewa
			y->left = nd;
			nd->up=y;
		}
		else throw CriticalException("CannotRotateLeft");
	}
	
	/*!
	 *\brief Obraca wybrane poddrzewo w prawo
	 *\param in element najstarszy do obrotu
	 */
	virtual void rightRot (nodeRB<T> * nd) {

		if (nd->left !=NULL) { //Warunek rotacji
			nodeRB<T> * y = nd->left;
			
			//Edycja wskaźnika rodzica poddrzewa obracanego
			if (nd->up == NULL) { 
				root = y;
				y->up = NULL;
			}
			else {
				nodeRB<T> * par = nd->up;
				if(nd==nd->up->right) nd->up->right = y;
				else nd->up->left = y;
				y->up = par;
			}
			
			
			if (y->right!=NULL) {
				nd->left=y->right;
				y->right->up = nd;
			}
			else {
				nd->left=NULL;
			}
			
			//Podpięcie elementu nd jako dziecka obecnego roota poddrzewa
			y->right = nd;
			nd->up=y;
		}
		else throw CriticalException("CannotRotateRight");
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
		else {
			//Wstawienie
			if (node->left == NULL && element < node->key) {
				node->setLeft(new nodeRB<T>(element,red,node));
				node = node->left;
				recolour(node);
			}
			else if (node->right == NULL && element > node->key) {
				node->setRight(new nodeRB<T>(element,red,node));
				node = node->right;
				recolour(node);
			}
			else if (node->left != NULL && element < node->key) {
				insert(element, node->left);
			}
			else if (node->right != NULL && element > node->key) {
				insert(element, node->right);
			}
			else return; //następny element do wpisania - prawdopodobnie już mamy taki w drzewie
		}
	}
	
private:

	void recolour(nodeRB<T> *node) {
		while (node->up->getColour() == red) {
			if (node->up == node->up->up->left) {
				nodeRB<T> * y = node->up->up->right;
				if (y->getColour() == red) {
					node->up->setColour(black);
					y->setColour(black);
					node->up->up->setColour(red);
					node = node->up->up;
				}
				else {
					if (node == node->up->right) {
						node = node->up;
						leftRot(node);
					}
					node->up->setColour(black);
					node->up->up->setColour(red);
					rightRot(node->up->up);
				}
			}
			else {
				nodeRB<T> * y = node->up->up->left;
				if (y->getColour() == red) {
					node->up->setColour(black);
					y->setColour(black);
					node->up->up->setColour(red);
					node = node->up->up;
				}
				else {
					if (node == node->up->left) {
						node = node->up;
						rightRot(node);
					}
					node->up->setColour(black);
					node->up->up->setColour(red);
					leftRot(node->up->up);
				}
			}
		}
		root->setColour(black);
	}

//		nodeRB<T> * temp;
//		while ((node!=root) && (node->up->getColour()==red)) {
//			if (node->up == node->up->up->left) {
//				temp = node->up->up->right;
//					if (temp->getColour() == red) {
//						node->up->setColour(black);
//						temp->setColour(black);
//						node->up->up->setColour(black);
//						node = node->up->up;
//					}
//				else {
//					if (node == node->up->right) {
//						node = node->up;
//						leftRot(node);
//					}
//					node->up->setColour(black);
//					node->up->up->setColour(red);
//					rightRot(node->up->up);
//				}
//			}
//			else {
//				temp = node->up->up->left;
//				if (temp->getColour()==red) {
//					node->up->setColour(black);
//					temp->setColour(black);
//					node->up->up->setColour(black);
//					node = node->up->up;
//				}
//				else {
//					if (node == node->up->left) {
//						node = node->up;
//						rightRot(node);
//					}
//					node->up->setColour(black);
//					node->up->up->setColour(red);
//					leftRot(node->up->up);
//				}
//			}
//		}
//		root->setColour(black);
//	}

public:
	
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


class tree_test : public IRunnable {
private:
	ITreeRB<int> * testtree;
	int counter;
	int testsize;
		/*!
	 * \brief Metoda ustawia punkt startowy generatora
	 * pseudolosowego.
	 */
	void seedSrand (void) {
		srand(clock());
	}
	
	/*!
	 * \brief Metoda generuje liczbę pseudolosową 
	 *
	 *\retval Liczba pseudolosowa
	 */
	int generateRandomDgt () {
		return rand()%(testsize*1000);
	}
	
public:
	tree_test () : testtree(new TreeRB<int>) {
		seedSrand();
	} 
	
	virtual ~tree_test () {
		delete testtree;
	}
	
	virtual bool prepare (int sizeOfTest) {
		counter = sizeOfTest;
		testsize = sizeOfTest;
		try {
			for (;counter>0;counter--) {
				testtree->insert(generateRandomDgt());
			}
		}
		catch (...) {
			throw;
		}
		return true;
	}
	
	virtual bool run () {
		try {
			testtree->search(generateRandomDgt());
		}
		catch (...) {
			throw;
		}
		return true;
	}
};



#endif
