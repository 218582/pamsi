/*!
 *\file
 *\brief Główny plik programu
 */

#include <iostream>
using namespace std;
#include "../inc/main.hh"

// W rozdziale 1. dokumentacji (../../dox/latex/refman.pdf) znajdują się użyteczne przykłady.
// Poniżej znajduje się szablon wykorzystania obiektu stos i jego metod, oraz proponowana obsługa wyjątków.

int main (void) {

	IHash<entry<int>> * hash = new Hash<entry<int>> (3);
	entry<int> ent("ciastko", 234);
	try {
		hash->add(0,ent);
	}
	catch (CriticalException * except) {
		cout << "Exception: " << except->getError() << endl;
	}
	catch (ContinueException * except) {
		cout << "Exception: " << except->getError() << endl;
	}
	catch (...) {
		cout << "Exception: Unknown!" << endl;
	}
}

//Szablon projektu
	
//	//Tworzenie obiektów
//	IStos<int> * stos = new Stos<int>;
//	
//	//Działanie programu
//	try{
//		stos->push(4);
//		stos->push(3);
//		cout << "TOP: " << stos->pop() << endl; //Powinno być 3
//		cout << "TOP: " << stos->get() << endl; //Powinno być 4
//		stos->pop();
//		if (stos->isEmpty()) cout << "Stos pusty!" << endl; //wykona się
//		cout << "----------------" << endl;
//		stos->pop(); //Wyrzuci wyjątek
//	}
//	
//	//Obsługa wyjątków
//	catch (ContinueException &cex) {
//		std::cout << "Exception: " << cex.getError() << std::endl;
//		delete stos;
//		exit(-1);
//	}
//	catch (CriticalException & crit_ex) {
//		std::cout << "Critical: " << crit_ex.getError() << std::endl;
//		delete stos;
//		exit(-2);
//	}
//	catch (...) {
//		std::cerr << "Unexpected exception!" << std::endl;
//		delete stos;
//		exit(-3);
//	}
//	
//	//Usunięcie obiektów
//	delete stos;
//	
//	return 0;
//}




//--------------------------------------------------------------------------------------

void dumpToFile (string nameOfFile, unsigned int testsize, IStoper * stoper) {
	fstream file;
	file.open(nameOfFile, ios::app);
	if (file.good()) {
		file << to_string(testsize) << " ";
		file << to_string(stoper->getElapsedTimeMs()) << endl;
	}
	else {
		file.close();
		throw CriticalException("FileError");
	}
	file.close();
}

void printOnscreen (unsigned int testsize, IStoper * stoper) {
	cout << "Test dla " << testsize << " elementów ukończony w czasie " << stoper->getElapsedTimeMs() << " ms." << endl;
}


