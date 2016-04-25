#ifndef _GRAPH_HH
#define _GRAPH_HH

#include "tabl.hh"
class empty {

};

template <class T>
class IGraph {	
public:
	
	virtual ~IGraph () {
	}
	
	virtual void addVertex(T) = 0;
	virtual void addEgde(int, int) = 0;
	virtual void removeVertex(int) = 0;
	virtual void removeEdge(int) = 0;
	virtual int * getNeightbours(int) = 0;
	virtual bool areConnected(int,int) = 0;
	
};


template <class T>
class Graph : public IGraph{
private:
	Itabn <Itabn<int>> * edges;
	Itabn <T> elements;
	
public:
	Graph() : 
		edges (new tabn<Itabn<int>>),
		elements (new tabn<T>) 
	{	
	}
	
	~Graph () {
		delete [] edges;
		delete elements;
	}
	
	/*!
	 *\brief Dodaje kolejny węzeł grafu
	 */
	virtual void addVertex(T element) {
		elements->add(element); //dodaje nowy element do tablicy;
		edges->add(NULL); //dodaje nową pozycję do listy węzłów - obecnie brak powiązań
	}
	
	virtual void addEdge(int first, int second) {
		if (edges->operator[first] == NULL) {
			Itabn <int> * newConnectionsList = new tabn<int>;
			egdes->add(newConnectionsList,first);
		}
		else {
			
		}
		if (edges->operator[second] == NULL) {
			Itabn <int> * newConnectionsList = new tabn<int>;
			egdes->add(newConnectionsList,second);
		}
		edges->add(newConnection,first);
	}
	
	
	virtual void removeVertex(int) {
	
	}
	
	virtual void removeEdge(int) {
	
	}
	
	virtual  getNeightbours(int) {
	
	}
	
	virtual bool areConnected(int,int) {
	
	}
	
	
	
	
	
};












#endif
