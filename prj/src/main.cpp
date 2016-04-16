/*!
 *\file
 *\brief Główny plik programu
 */

#include <iostream>
using namespace std;
#include "../inc/main.hh"


int main (void) { 


//Przykład obsługi samego bucketa

	try {
		IBucket<string,int> * kosz = new Bucket<string,int>(0);
		entry<string,int> wpis("Nowak",48);
		kosz->add(wpis);
		entry<string,int> wpis1("Kowalska",62);
		kosz->add(wpis1);
		entry<string,int> wpis2("Kowalski",2265);
		kosz->add(wpis2);
		entry<string,int> wpis3("Torun",200);
		kosz->add(wpis3);
		entry<string,int> wpis4("Walbrzych",1111);
		kosz->add(wpis4);
		entry<string,int> wpis5("Bombsite",7358);
		kosz->add(wpis5);
		entry<string,int> wpis6("Ciastko",413);
		kosz->add(wpis6);
		string user_input;
		cin >>user_input;
		cout << kosz->lookup(user_input) << endl;
	}
	catch (CriticalException & except) {
		cout << "Exception: " << except << endl;
	}
	catch (ContinueException & except) {
		cout << "Exception: " << except << endl;
	}
	catch (ExceptionBase & base) {
		cout << "Exception" << base << endl;
	}
	catch (...) {
		cout << "Totally unknown!" << endl;
	}
}

////Szablon projektu
//	
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
//		std::cout << "Exception: " << cex << std::endl;
//		delete stos;
//		exit(-1);
//	}
//	catch (CriticalException & crit_ex) {
//		std::cout << "Critical: " << crit_ex << std::endl;
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


