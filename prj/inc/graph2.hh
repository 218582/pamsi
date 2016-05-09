#ifndef _GRAPH2_HH
#define _GRAPH2_HH
#include "tabl.hh"
#include "lista.hh"
#include "stos.hh"
#include "kolejka.hh"
#include "run.hh"
#include "asoc.hh"

/*!
 *\brief Klasa definiujaca typ, w ktorym zapisywana jest informacja o krawedzi grafu
 */
class edgeInfo
{
public:

	int edgeTo;
	int weight;
	
	//Konstruktor
	edgeInfo(int edg, int w=0) :
		edgeTo(edg),
		weight(w)
	{
	}
	
	edgeInfo() :
		edgeTo(0),
		weight(0)
	{
	}
	
	/*!
	 *\brief Zwraca informację o wierzchołku, z którym łączy ta krawędź
	 */
	int conn(void) {
		return edgeTo;
	}
	
	/*!
	 *\brief Zwraca informację o wadze krawędzi
	 */
	int w(void) {
		return weight;
	}

	friend std::ostream & operator << (std::ostream & output, const edgeInfo to) {
		output << to.edgeTo << "w" << to.weight << std::endl;
		return output;
	}
	
	edgeInfo & operator = (const edgeInfo & read) {
		edgeTo = read.edgeTo;
		weight = read.weight;
		return * this;
	}
	
	friend bool operator < (edgeInfo one, edgeInfo two) {
		if (one.weight < two.weight) return true;
		else return false;
	}
	
	friend bool operator > (edgeInfo one, edgeInfo two) {
		if (one.weight > two.weight) return true;
		else return false;
	}
	
	friend bool operator <= (edgeInfo one, edgeInfo two) {
		if (one.weight <= two.weight) return true;
		else return false;
	}
	
	friend bool operator >= (edgeInfo one, edgeInfo two) {
		if (one.weight >= two.weight) return true;
		else return false;
	}
	
	friend bool operator == (edgeInfo one, edgeInfo two) {
		if (one.edgeTo == two.edgeTo) return true;
		else return false;
	}
};
	
/*!
 *\brief Interfejs grafu2 z uwzględnieniem wag
 */
class IGraph2 {	
public:
	
	virtual ~IGraph2 () {
	}
	
	virtual bool isEmpty(void) = 0;
	virtual void insertVertex(void) = 0;
	virtual void insertEdge(int, int) = 0;
//	virtual void removeVertex(int) = 0;
//	virtual void removeEdge(int) = 0;
	virtual Itabn<edgeInfo> * getNeightbours(int) = 0;
	virtual bool areAdjacent(int,int) = 0;
	virtual int numberOfEdges(void) = 0;
//	virtual Itabn<int>* DFS(void) = 0;
//	virtual Itabn<int>* BFS(void) = 0;
	virtual Itabn <int> * branchAndBound(int, int) = 0;	
};


/*!
 *\brief graf2 z uwzględnieniem wag
 */
class Graph2 : public IGraph2 {

private:
	Itabn <Itabn <edgeInfo> *> * edges; 
	Itabn <int> * elements;
	int edgesCount;
	
public:
	/*!
	 *\brief Konstruktor klasy Graph
	 */
	 Graph2 () : 
	 	edges (new tabn <Itabn <edgeInfo> *>), 
	 	elements (new tabn<int>),
	 	edgesCount (0)
	 	{
	 }
	 
	 /*!
	 *\brief Destruktor klasy Graph
	 */
	 virtual ~Graph2() {
	 	delete edges;
	 	delete elements;
	 }
	 
	/*!
	 *\brief Sprawdza czy graf jest pusty
	 */
	 virtual bool isEmpty (void) {
	 	if (elements->maxIndex() == -1) return true;
	 	else return false;
	 }
	 
	/*!
	 *\brief Dodaje element do grafu
	 */
	 virtual void insertVertex() {
	 
	 	//Dodanie elementu do tablicy elementów
	 	elements->add(elements->nOE());
	 	
	 	//Dodanie nowego wpisu dla powiązań elementu, aby utrzymać porządek indeksów
	 	edges->add(NULL);
	 	edges->operator[](elements->nOE()-1) = new tabn <edgeInfo>; 
	 }
	
	 /*!
	  *\brief Dodaje powiązanie między dwoma elementami
	  */
	 virtual void insertEdge(int index1, int index2, int wei) {
	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotInsertEdge");
		if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
			throw CriticalException("GraphInsertIndexWrong");
		}
		else {
			edgeInfo one(index1,wei);
			edgeInfo two(index2,wei);
			edges->operator[](index1)->add(one);
			edges->operator[](index2)->add(two);
			edgesCount++;
		}
	 }
	 
	 /*!
	  *\brief Sprawdza, czy dwa elementy mają krawędź między sobą
	  */
	 virtual bool areAdjacent(int index1,int index2) {
	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotCheckIfAdjacent");
		if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
			throw CriticalException("GraphInsertIndexWrong");
		}
		else {
			edgeInfo one(index1);
			edgeInfo two(index2);
			if ((edges->operator[](index1)->search(two)) && (edges->operator[](index2)->search(one))) {
				return true;
			}
			else return false;
		}
	 }
	 
	 /*!
	  *\brief Zwraca wskaźnik na tablicę elementów będących zbiorem sąsiadów wierzchołka index
	  */
	 virtual Itabn<edgeInfo> * getNeightbours(int index) {
	 	return edges->operator[](index);
	 }
	 
	 /*!
	  *\brief Zwraca ilość krawędzi drzewa
	  */
	 virtual int numberOfEdges(void) {
	 	return edgesCount;
	 }
	 
	 /*!
	  *\brief Znajduje najkrótszą możliwą ścieżkę miedzy dwoma elementami
	  */
	 virtual Itabn<int> * branchAndBound(int start, int end) {
	 	
	 	Itabn<int> *  = new tabn<int>;
	 	return cos;
	 }
	 
private:

	 
};







#endif
