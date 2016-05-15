//#ifndef _GRAPH2_HH
//#define _GRAPH2_HH
//#include "tabl.hh"
//#include "lista.hh"
//#include "stos.hh"
//#include "kolejka.hh"
//#include "run.hh"
//#include "asoc.hh"

///*!
// *\brief Klasa definiujaca typ, w ktorym zapisywana jest informacja o krawedzi grafu
// */
//class edgeInfo
//{
//public:

//	int edgeTo;
//	int weight;
//	
//	//Konstruktor
//	edgeInfo(int edg, int w=0) :
//		edgeTo(edg),
//		weight(w)
//	{
//	}
//	
//	edgeInfo() :
//		edgeTo(0),
//		weight(0)
//	{
//	}
//	
//	/*!
//	 *\brief Zwraca informację o wierzchołku, z którym łączy ta krawędź
//	 */
//	int conn(void) {
//		return edgeTo;
//	}
//	
//	/*!
//	 *\brief Zwraca informację o wadze krawędzi
//	 */
//	int w(void) {
//		return weight;
//	}

//	friend std::ostream & operator << (std::ostream & output, const edgeInfo to) {
//		output << to.edgeTo << "w" << to.weight << std::endl;
//		return output;
//	}
//	
//	edgeInfo & operator = (const edgeInfo & read) {
//		edgeTo = read.edgeTo;
//		weight = read.weight;
//		return * this;
//	}
//	
//	friend bool operator < (edgeInfo one, edgeInfo two) {
//		if (one.weight < two.weight) return true;
//		else return false;
//	}
//	
//	friend bool operator > (edgeInfo one, edgeInfo two) {
//		if (one.weight > two.weight) return true;
//		else return false;
//	}
//	
//	friend bool operator <= (edgeInfo one, edgeInfo two) {
//		if (one.weight <= two.weight) return true;
//		else return false;
//	}
//	
//	friend bool operator >= (edgeInfo one, edgeInfo two) {
//		if (one.weight >= two.weight) return true;
//		else return false;
//	}
//	
//	friend bool operator == (edgeInfo one, edgeInfo two) {
//		if (one.edgeTo == two.edgeTo) return true;
//		else return false;
//	}
//};




//	
///*!
// *\brief Interfejs grafu2 z uwzględnieniem wag
// */
//class IGraph2 {	
//public:
//	
//	virtual ~IGraph2 () {
//	}
//	
//	virtual bool isEmpty(void) = 0;
//	virtual void insertVertex(void) = 0;
//	virtual void insertEdge(int, int, int) = 0;
////	virtual void removeVertex(int) = 0;
////	virtual void removeEdge(int) = 0;
//	virtual Itabn<edgeInfo> * getNeightbours(int) = 0;
//	virtual bool areAdjacent(int,int) = 0;
//	virtual int numberOfEdges(void) = 0;
////	virtual Itabn<int>* DFS(void) = 0;
////	virtual Itabn<int>* BFS(void) = 0;
//	virtual int edgeWeight (int, int) = 0;
//};


///*!
// *\brief graf2 z uwzględnieniem wag
// */
//class Graph2 : public IGraph2 {

//private:
//	Itabn <Itabn <edgeInfo> *> * edges; //Uproszczona tablica asocjacyjna - klucz to indeks
//	Itabn <entry<int,int>> * elements;
//	int edgesCount;
//	
//public:
//	/*!
//	 *\brief Konstruktor klasy Graph
//	 */
//	 Graph2 () : 
//	 	edges (new tabn <Itabn <edgeInfo> *>), 
//	 	elements (new tabn<entry<int,int>>),
//	 	edgesCount (0)
//	 	{
//	 }
//	 
//	 /*!
//	 *\brief Destruktor klasy Graph
//	 */
//	 virtual ~Graph2() {
//	 	delete edges;
//	 	delete elements;
//	 }
//	 
//	/*!
//	 *\brief Sprawdza czy graf jest pusty
//	 */
//	 virtual bool isEmpty (void) {
//	 	if (elements->maxIndex() == -1) return true;
//	 	else return false;
//	 }
//	 
//	/*!
//	 *\brief Dodaje element do grafu
//	 */
//	 virtual void insertVertex() {
//	 
//	 	//Dodanie elementu do tablicy elementów
//	 	elements->add(elements->nOE());
//	 	
//	 	//Dodanie nowego wpisu dla powiązań elementu, aby utrzymać porządek indeksów
//	 	edges->add(NULL);
//	 	edges->operator[](elements->nOE()-1) = new tabn <edgeInfo>; 
//	 }
//	
//	 /*!
//	  *\brief Dodaje powiązanie między dwoma elementami
//	  */
//	 virtual void insertEdge(int index1, int index2, int wei) {
//	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotInsertEdge");
//		if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
//			throw CriticalException("GraphInsertIndexWrong");
//		}
//		else {
//			edgeInfo one(index1,wei);
//			edgeInfo two(index2,wei);
//			edges->operator[](index1)->add(one);
//			edges->operator[](index2)->add(two);
//			edgesCount++;
//		}
//	 }
//	 
//	 /*!
//	  *\brief Sprawdza, czy dwa elementy mają krawędź między sobą
//	  */
//	 virtual bool areAdjacent(int index1,int index2) {
//	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotCheckIfAdjacent");
//		if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
//			throw CriticalException("GraphIndexWrong");
//		}
//		else {
//			edgeInfo one(index1);
//			edgeInfo two(index2);
//			if ((edges->operator[](index1)->search(two)) && (edges->operator[](index2)->search(one))) {
//				return true;
//			}
//			else return false;
//		}
//	 }
//	 
//	 /*!
//	  *\brief Zwraca wskaźnik na tablicę elementów będących zbiorem sąsiadów wierzchołka index
//	  */
//	 virtual Itabn<edgeInfo> * getNeightbours(int index) {
//	 	return edges->operator[](index);
//	 }
//	 
//	 /*!
//	  *\brief Zwraca wagę krawędzi
//	  */
//	 virtual int edgeWeight (int index1, int index2) {
//	 	if (isEmpty()) throw CriticalException("GraphEmptyCannotReturnWeight");
//		else if ((index1 > elements->maxIndex()) || (index2 > elements->maxIndex()) || (index1 > edges->maxIndex()) || (index2 > edges->maxIndex())) {
//			throw CriticalException("GraphIndexWrong");
//		}
//		else {
//			edgeInfo two(index2);
//			return edges->operator[](index1)->searchObject(two).weight;
//		}
//	 }
//	 
//	 /*!
//	  *\brief Zwraca ilość krawędzi drzewa
//	  */
//	 virtual int numberOfEdges(void) {
//	 	return edgesCount;
//	 }
//	 	 
//};


//class test_graph2 : public IRunnable {

//private:

//	IGraph2 * graph;
//	IGraph2 * fastest;
//	int numberOfV;
//	int maxWeight;
//	
//public:

//	test_graph2 (void) :
//		graph(new Graph2),
//		fastest(new Graph2),
//		numberOfV(0),
//		maxWeight(10)
//	{	
//	}
//	
//private:
//	/*!
//	 * \brief Metoda ustawia punkt startowy generatora
//	 * pseudolosowego.
//	 */
//	void seedSrand (void) {
//		srand(clock());
//	}
//	
//	/*!
//	 *\brief Dodaje określoną ilość wierzchołków do grafu
//	 */
//	 void addElementsOfGraph(int numberOfVertices) {
//	 	numberOfV = numberOfVertices;
//	 	for (int i=0; i <numberOfVertices;i++) {
//	 		graph->insertVertex();
//	 	}
//	 }
//	
//	/*!
//	 *\brief Generuje losowy najmniejszy graf spójny z losowymi wagami krawędzi
//	 */
//	 void generateMinimalConnectedGraph(int numberOfVertices) {
//	 	addElementsOfGraph(numberOfVertices);
//	 	seedSrand();
//	 	for (int j=0; j<numberOfVertices;j++) {
//	 		if (j==0); //nic nie rób  - nie łączę pierwszego el. z żadnym
//	 		else {
//	 			int t = (rand() %j);
//	 			graph->insertEdge(t,j,rand()%maxWeight);
//	 		}
//	 	}
//	 }
//	 
//	/*!
//	 *\brief Generuje graf spójny o określonej liczbie krawędzi
//	 */
//	void generateGraph(int numberOfVertices, int numberOfEdg) {
//	 	generateMinimalConnectedGraph(numberOfVertices);
//	 	
//	 	int needMore = numberOfEdg - graph->numberOfEdges();
//	 	if (needMore <= 0) return;
//	 	
//	 	for (int i = 0; i < needMore; i++) {
//	 		int one = rand()%(numberOfVertices-1);
//	 		int two = rand()%(numberOfVertices-1);
//	 		
//	 		while (graph->areAdjacent(one,two) || one == two) {
//	 			one = rand()%(numberOfVertices-1);
//	 			two = rand()%(numberOfVertices-1);
//	 		}
//	 		graph->insertEdge(one,two,rand()%maxWeight);
//	 	}
//	 }
//	 
//	 /*!
//	  *\brief Generuje efektywniej graf o maksymalnej liczbie krawedzi
//	  * Gererowanie grafu o ilości krawędzi bliskiej (a szczególnie równej) maksymalnej może spowodować
//	  * znaczne wydłużenie czasu generowania grafu - możliwy jest długi czas oczekiwania na wylosowanie 
//	  * nowej krawędzi
//	  */
//	void generateMaximumGraph (int numberOfVertices) {
//	 	addElementsOfGraph(numberOfVertices);
//	 	//Obliczanie ilości krawędzi
//	 	int requiredNumberOfEdges=0;
//	 	for(int i = numberOfVertices-1; i>0;i--) {
//			requiredNumberOfEdges+=i;
//		}
//		
//		//Dodawanie wszystkich krawedzi
//		for (int i = numberOfVertices-1; i>0; i--) {
//			for (int j=0;j<i;j++) {
//				graph->insertEdge(i,j,rand()%maxWeight);	
//			}
//		}
//	}
//	 
//	 bool branchAndBoundLoopSearch (int now, int end) {
//	 	
//	 }
//	 
//	 /*!
//	  *\brief Znajduje najkrótszą możliwą ścieżkę miedzy dwoma elementami w grafie
//	  */
//	Itabn<int> * branchAndBound(int start, int end) {
//	 	
//	 	Itabn<int> * cos  = new tabn<int>;
//	 	IGraph2 * sGraph = new Graph2;
//	 	 
//	 	delete sGraph;
//	 	return cos;
//	}
//	
//	
//	 

//	
//	bool prepare (int sizeOfTest) {
//		return true;
//	}
//	
//	bool run (void) {
//		return true;
//	}
//};




//#endif
