#ifndef _GRAPH_HH
#define _GRAPH_HH

#include "tabl.hh"
#include "lista.hh"
#include "stos.hh"
#include "kolejka.hh"
#include "run.hh"

/*!
 *\brief Interfejs grafu
 */
class IGraph {	
public:
	
	virtual ~IGraph () {
	}
	
	virtual bool isEmpty(void) = 0;
	virtual void insertVertex(void) = 0;
	virtual void insertEdge(int, int) = 0;
//	virtual void removeVertex(int) = 0;
//	virtual void removeEdge(int) = 0;
	virtual Itabn<int> * getNeightbours(int) = 0;
	virtual bool areAdjacent(int,int) = 0;
	virtual int numberOfEdges(void) = 0;
	virtual Itabn<int>* DFS(void) = 0;
	virtual Itabn<int>* BFS(void) = 0;
	
};


/*!
 *\brief Klasa implementująca inerfejs grafu
 */
class Graph : public IGraph {
private:


	Itabn <Itabn <int> *> * edges; 
	 	
	//Tablica elementów grafu
	Itabn <int> * elements;
	
	int edgesCount;

public:
	/*!
	 *\brief Konstruktor klasy Graph
	 */
	 Graph () : 
	 	edges (new tabn <Itabn <int> *>), 
	 	elements (new tabn<int>),
	 	edgesCount (0)
	 	{
	 }
	 
	 /*!
	 *\brief Destruktor klasy Graph
	 */
	 virtual ~Graph() {
	 	delete edges;
	 	delete elements;
	 }
	 
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
	 	edges->operator[](elements->nOE()-1) = new tabn <int>; 
	 }
	 
	 /*!
	  *\brief Dodaje powiązanie między dwoma elementami
	  */
	 virtual void insertEdge(int index1, int index2) {
	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotInsertEdge");
		if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
			throw CriticalException("GraphInsertIndexWrong");
		}
		else {
			edges->operator[](index1)->add(index2);
			edges->operator[](index2)->add(index1);
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
			if ((edges->operator[](index1)->search(index2)) && (edges->operator[](index2)->search(index1))) {
				return true;
			}
			else return false;
		}
	 }
	 
	 
	 /*!
	  *\brief Zwraca wskaźnik na tablicę elementów będących zbiorem sąsiadów wierzchołka index
	  */
	 virtual Itabn<int> * getNeightbours(int index) {
	 	return edges->operator[](index);
	 }
	 
	 /*!
	  *\brief Zwraca ilość krawędzi drzewa
	  */
	 virtual int numberOfEdges(void) {
	 	return edgesCount;
	 }
	 
	 /*!
	  *\brief Przeszukuje graf wgłąb
	  */
	 virtual Itabn<int>* DFS(void) {
	 	std::cout << edges << std::endl;
	 	Itabn<int> * dfs = new tabn<int>;
		IStos<int> * found = new Stos<int>;
		int * visited = new int[elements->nOE()];
		//wszystkie nieodwiedzone
		for (int i=0; i<elements->nOE();i++) {
			visited[i]=0;
		}
		
		//Rozpoczęcie DFS
		found->push(0);
		
		while(!(found->isEmpty())) {
			dfs->add(found->pop());
			visited[dfs->show(dfs->maxIndex())] = 1;
			Itabn<int> * neightb = new tabn<int>();
			neightb = getNeightbours(dfs->show(dfs->maxIndex()));
			neightb->bubblesort();
			std::cout << "sąsiedzi " << dfs->show(dfs->maxIndex()) << " : " << neightb << '\n';
			
			//Dodawanie nieodwiedzonych wierzchołków sąsiadujących do stosu
			for (int i = neightb->maxIndex(); i>=0; i--) {
				//Jeżeli nieodwiedzone
				if (visited[neightb->show(i)] == 0) {
					found->push(neightb->show(i));
					visited[found->get()] = 1;
				}
			}
			std::cout << "Obecny stos: " << found << '\n';
			delete neightb;
		}
		delete found;
		delete visited;
		return dfs;
	 }
	 
	 /*!
	  *\brief Przeszukuje graf wszerz
	  */
	  virtual Itabn<int>* BFS(void) {
	  	std::cout << edges << std::endl;
	 	Itabn<int> * bfs = new tabn<int>;
		IKolejka<int> * found = new Kolejka<int>;
		int * visited = new int[elements->nOE()];
		//wszystkie nieodwiedzone
		for (int i=0; i<elements->nOE();i++) {
			visited[i]=0;
		}
		
		//Rozpoczęcie DFS
		found->enqueue(0);
		
		while(!(found->isEmpty())) {
			bfs->add(found->dequeue());
			visited[bfs->show(bfs->maxIndex())] = 1;
			Itabn<int> * neightb = new tabn<int>();
			neightb = getNeightbours(bfs->show(bfs->maxIndex()));
			neightb->bubblesort();
			std::cout << "sąsiedzi " << bfs->show(bfs->maxIndex()) << " : " << neightb << '\n';
			
			//Dodawanie nieodwiedzonych wierzchołków sąsiadujących do stosu
			for (int i = 0; i<=neightb->maxIndex(); i++) {
				//Jeżeli nieodwiedzone
				if (visited[neightb->show(i)] == 0) {
					found->enqueue(neightb->show(i));
					visited[found->get()] = 1;
				}
			}
			std::cout << "Obecna kolejka: " << found << '\n';
			delete neightb;
		}
		delete found;
		delete visited;
		return bfs;
	  }
	
};


class test_graph : public IRunnable {

private:

	IGraph * graph;

	/*!
	 * \brief Metoda ustawia punkt startowy generatora
	 * pseudolosowego.
	 */
	void seedSrand (void) {
		srand(clock());
	}
	
public:
	
	test_graph () : graph(new Graph()) {
	}
	
private:


	/*!
	 *\brief Dodaje określoną ilość wierzchołków do grafu
	 */
	 void addElementsOfGraph(int numberOfVertices) {
	 	for (int i=0; i <numberOfVertices;i++) {
	 		graph->insertVertex();
	 	}
	 }
	
	/*!
	 *\brief Generuje losowy najmniejszy graf spójny
	 */
	 void generateMinimalConnectedGraph(int numberOfVertices) {
	 	addElementsOfGraph(numberOfVertices);
	 	seedSrand();
	 	for (int j=0; j<numberOfVertices;j++) {
	 		if (j==0); //nic nie rób  - nie łączę pierwszego el. z żadnym
	 		else {
	 			int t = (rand() %j);
	 			graph->insertEdge(t,j);
	 		}
	 	}
	 }
	 
	/*!
	 *\brief Generuje graf spójny o określonej liczbie krawędzi
	 */
	void generateGraph(int numberOfVertices, int numberOfEdg) {
	 	generateMinimalConnectedGraph(numberOfVertices);
	 	
	 	int needMore = numberOfEdg - graph->numberOfEdges();
	 	
	 	for (int i = 0; i < needMore; i++) {
	 		int one = rand()%(numberOfVertices-1);
	 		int two = rand()%(numberOfVertices-1);
	 		
	 		while (graph->areAdjacent(one,two) || one == two) {
	 			one = rand()%(numberOfVertices-1);
	 			two = rand()%(numberOfVertices-1);
	 		}
	 		graph->insertEdge(one,two);
	 	}
	 }
	 
	 /*!
	  *\brief Generuje efektywniej graf o maksymalnej liczbie krawedzi
	  * Gererowanie grafu o ilości krawędzi bliskiej (a szczególnie równej) maksymalnej może spowodować
	  * znaczne wydłużenie czasu generowania grafu - możliwy jest długi czas oczekiwania na wylosowanie 
	  * nowej krawędzi
	  */
	 void generateMaximumGraph (int numberOfVertices) {
	 	addElementsOfGraph(numberOfVertices);
	 	//Obliczanie ilości krawędzi
	 	int requiredNumberOfEdges=0;
	 	for(int i = numberOfVertices-1; i>0;i--) {
			requiredNumberOfEdges+=i;
		}
		
		//Dodawanie wszystkich krawedzi
		for (int i = numberOfVertices-1; i>0; i--) {
			for (int j=0;j<i;j++) {
				graph->insertEdge(i,j);	
			}
		}
	 }
	 
public:
	bool prepare(int testSize) {
		generateGraph(testSize,testSize/2);
		//generateMaximumGraph(testSize);
		return true;
	}
	
	bool run (void) {
		//std::cout << graph->DFS();
		std::cout << graph->BFS();
		return true;
	}
};











#endif
