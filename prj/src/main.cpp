/*!
 *\file
 *\brief Główny plik programu
 */

#include <iostream>
using namespace std;
#include "../inc/main.hh"



int main (void) {

//Przykład użycia:
//	IRunnable * runner = new lista_test;
//	IStoper * stoper = new Stoper;
//	unsigned int testSize = 100;
//	string outputFile = "file123";
//	try {
//		runner->prepare(testSize);
//		stoper->start();
//		runner->run();
//		stoper->stop();
//		printOnscreen(testSize,stoper);
//		dumpToFile(outputFile,testSize,stoper);
//		}
//	catch (ContinueException &cex) {
//		std::cout << "Exception: " << cex.getError() << std::endl;
//	}
//	catch (CriticalException & crit_ex) {
//		std::cout << "Critical: " << crit_ex.getError() << std::endl;
//		delete stoper;
//		delete runner;
//		return -1;
//	}
//	catch (...) {
//		std::cerr << "Unexpected exception!" << std::endl;
//		delete stoper;
//		delete runner;
//		return -1;
//	}
//	delete stoper;
//	delete runner;

	Itabn<int> * tablica = new tabn<int>;
	try {
		tablica->add(1,0);
		tablica->add(2,1);
		tablica->add(6,1);
		tablica->showElems();
	}
	catch (ContinueException &cex) {
		std::cout << "Exception: " << cex.getError() << std::endl;
	}
	catch (CriticalException & crit_ex) {
		std::cout << "Critical: " << crit_ex.getError() << std::endl;
		delete tablica;
		exit(-1);
	}
	catch (...) {
		std::cerr << "Unexpected exception" << std::endl;
		delete tablica;
		exit(-1);
	}
	delete tablica;
	return 0;
	
	
	//test bubblesort
//	Itabn<int> * tablica = new tabn<int>;
//	tablica->add(7);
//	tablica->add(4);
//	tablica->add(1);
//	tablica->add(9);
//	tablica->add(10);
//	tablica->add(94);
//	tablica->add(-4);
//	tablica->add(5);
//	tablica->add(15);
//	tablica->add(8);
//	tablica->add(9);
//	tablica->add(17);
//	tablica->add(19);
//	tablica->showElems();
//	tablica->bubblesort();
//	tablica->showElems();
}


void dumpToFile (string nameOfFile, unsigned int testsize, IStoper * stoper) {
	fstream file;
	file.open(nameOfFile, ios::app);
	if (file.good()) {
		file << to_string(testsize) << " ";
		file << to_string(stoper->getElapsedTimeMs()) << endl;
	}
	file.close();
}

void printOnscreen (unsigned int testsize, IStoper * stoper) {
	cout << "Test dla " << testsize << " elementów ukończony w czasie " << stoper->getElapsedTimeMs() << " ms." << endl;
}


