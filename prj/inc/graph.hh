#ifndef _GRAPH_HH
#define _GRAPH_HH

#include "tabl.hh"

/*!
 *\brief Interfejs grafu
 */
class IGraph {	
public:
	
	virtual ~IGraph () {
	}
	
	virtual void insertVertex(int) = 0;
	virtual void insertEdge(int, int) = 0;
//	virtual void removeVertex(int) = 0;
//	virtual void removeEdge(int) = 0;
	virtual Itabn<int> * getNeightbours(int) = 0;
	virtual bool areAdjacent(int,int) = 0;
	
};


/*!
 *\brief Klasa implementująca inerfejs grafu
 */
class Graph : public IGraph {
private:


	Itabn <Itabn <int> *> * edges; 

	//Tablica elementów grafu
	Itabn <int> * elements;

public:
	/*!
	 *\brief Konstruktor klasy Graph
	 */
	 Graph () : 
	 	edges (new tabn <Itabn <int> *>), 
	 	elements (new tabn<int>) 
	 	{
	 }
	 
	 /*!
	 *\brief Destruktor klasy Graph
	 */
	 virtual ~Graph() {
	 	delete edges;
	 	delete elements;
	 }
	 
	 /*!
	 *\brief Dodaje element do grafu
	 */
	 virtual void insertVertex(int elem) {
	 	//Dodanie elementu do tablicy elementów
	 	elements->add(elem);
	 	
	 	//Dodanie nowego wpisu dla powiązań elementu, aby utrzymać porządek indeksów
	 	edges->add(NULL);
	 	edges->operator[](elements->nOE()-1) = new tabn <int>; 
	 }
	 
	 /*!
	  *\brief Dodaje powiązanie między dwoma elementami
	  */
	 virtual void insertEdge(int index1, int index2) {
		if ((index1 > elements->nOE()-1) || (index2 > elements->nOE()-1) || (index1 > edges->nOE()-1) || (index2 > edges->nOE()-1)) {
			throw CriticalException("GraphInsertIndexWrong");
		}
		else {
			edges->operator[](index1)->add(index2);
			edges->operator[](index2)->add(index1);
		}
		
	 }
	 
	 /*!
	  *\brief Sprawdza, czy dwa elementy mają krawędź między sobą
	  */
	 virtual bool areAdjacent(int index1,int index2) {
		if ((index1 > elements->nOE()-1) || (index2 > elements->nOE()-1) || (index1 > edges->nOE()-1) || (index2 > edges->nOE()-1)) {
			throw CriticalException("GraphInsertIndexWrong");
		}
		else {
			if ((edges->operator[](index1)->search(index2)) && (edges->operator[](index2)->search(index1))) {
				return true;
			}
			else return false;
		}
	 }
	 
	 
	 virtual Itabn<int> * getNeightbours(int index) {
	 	return edges->operator[](index);
	 }
	 
	 
	 
	  
	
};












#endif
