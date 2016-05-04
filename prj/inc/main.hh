#ifndef _MAIN_HH
#define _MAIN_HH
/*!
 * \file 
 *
 */
#include <iostream>
#include <fstream>
#include "stoper.hh"
#include "tabl.hh"
#include "run.hh"
#include "lista.hh"
#include "stos.hh"
#include "kolejka.hh"
#include "asoc.hh"
#include "hash.hh"
#include "tree.hh"
#include "graph.hh"

/*! \mainpage 
 *
 *	\section Dokumentacja Dokumentacja klas w repozytorium pamsi.
 *	Ten dokument zawiera dokumentację klas znajdujących się w plikach repozytorium pamsi.
 *
 *  \section Example Przykład uruchomienia testu
 *
 * 	
 *
 * \code{.cpp}
 	//Poniższy test wymaga, aby w folderze projektu znajdował się słownik o nazwie zadanej w metodzie virtual bool lista_test::prepare(int) . Należy dokonać edycji w/w metody w celu zmian. Trawją prace nad rozwiązaniem problemu.
 	IRunnable * runner = new lista_test;
	IStoper * stoper = new Stoper;
	unsigned int testSize = 100;
	string outputFile = "file123";
	try {
		runner->prepare(testSize);
		stoper->start();
		runner->run();
		stoper->stop();
		printOnscreen(testSize,stoper);
		dumpToFile(outputFile,testSize,stoper);
		}
	catch (ContinueException &cex) {
		std::cout << "Exception: " << cex.getError() << std::endl;
	}
	catch (CriticalException & crit_ex) {
		std::cout << "Critical: " << crit_ex.getError() << std::endl;
		delete stoper;
		delete runner;
		return -1;
	}
	catch (...) {
		std::cerr << "Unexpected exception!" << std::endl;
		delete stoper;
		delete runner;
		return -1;
	}
	delete stoper;
	delete runner;
	
 *	\endcode
 *
 *	\section Examples Inne przykłady
 *	\subsection Example1 Test sortowania bąbelkowego
 *	
 *	\code{.cpp}
 	Itabn<int> * tablica = new tabn<int>;
	tablica->add(7);
	tablica->add(4);
	tablica->add(1);
	tablica->add(9);
	tablica->add(10);
	tablica->add(94);
	tablica->add(-4);
	tablica->add(5);
	tablica->add(15);
	tablica->add(8);
	tablica->add(9);
	tablica->add(17);
	tablica->add(19);
	tablica->showElems();
	tablica->bubblesort();
	tablica->showElems();
	delete tablica;
	
 *	\endcode
 *
 *  \subsection Example2 Test obsługi wyjątków
 *
 * W poniższym teście powinien wystąpić wyjątek, związany z próbą dodania elementu o indeksie 10, gdy tablica dynamicznie rozszerzalna ma 3 elementy (czyli gdy maksymalny indeks to 2).
 *
 *  \code{.cpp}
 	Itabn<int> * tablica = new tabn<int>;
	try {
		tablica->add(1,0);
		tablica->add(2,1);
		tablica->add(6,1);
		tablica->add(10,10);
	}
	catch (ContinueException &cex) {
		std::cout << "Exception: " << cex.getError() << std::endl;
		delete tablica;
		exit(-1);
	}
	catch (CriticalException & crit_ex) {
		std::cout << "Critical: " << crit_ex.getError() << std::endl;
		delete tablica;
		exit(-2);
	}
	catch (...) {
		std::cerr << "Unexpected exception!" << std::endl;
		delete tablica;
		exit(-3);
	}
	delete tablica;
	return 0;
 *	\endcode
 *	
 *	\subsection Example3 Obsługa stosu
 *	
 *	\code{.cpp}
	//Wykorzystanie stosu
	IStos<int> * stos = new Stos<int>;
	try{
		stos->push(4);
		stos->push(3);
		cout << "TOP: " << stos->pop() << endl; //Powinno być 3
		cout << "TOP: " << stos->get() << endl; //Powinno być 4
		stos->pop();
		if (stos->isEmpty()) cout << "Stos pusty!" << endl; //wykona się
		cout << "----------------" << endl;
		stos->pop(); //Wyrzuci wyjątek
	}
	catch (ContinueException &cex) {
		std::cout << "Exception: " << cex.getError() << std::endl;
		delete stos;
		exit(-1);
	}
	catch (CriticalException & crit_ex) {
		std::cout << "Critical: " << crit_ex.getError() << std::endl;
		delete stos;
		exit(-2);
	}
	catch (...) {
		std::cerr << "Unexpected exception!" << std::endl;
		delete stos;
		exit(-3);
	}
	delete stos;
	return 0;
 *	\endcode
 *
	
 */

/*!
 *\brief Zrzuca dane wynikowe do pliku
 *
 *\param nameOfFile nazwa pliku wynikowego
 *\param testsize rozmiar testu 
 *\param stoper klasa stopera
 */
void dumpToFile (std::string, unsigned int, IStoper *);

/*!
 *\brief Wyświetla wynik na standardowym wyjściu
 *
 *\param testSize rozmiar testu
 *\param stoper klasa stopera
 */
void printOnscreen (unsigned int, IStoper *);


#endif
