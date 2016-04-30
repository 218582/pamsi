/*!
 *\file
 *\brief Główny plik programu
 */

#include <iostream>
using namespace std;
#include "../inc/main.hh"
#include <numeric>



int main (void) { 
//	ITreeRB<int> * tree = new TreeRB<int>; 
nodeRB<int> one (5);
cout << "Key: " << one.getKey() << endl;
cout << "Colour: " << one.getColour() << endl;
cout << "Left: "<< one.getLeft() << endl;
cout << "Right: " << one.getRight() << endl;
cout << "Up: " << one.getUp() << endl;	
	
}
	
//	int liczbaElementow[] = {10, 100, 1000, 10000, 100000, 1000000};
//	double timeW = 0;
//	double timeS = 0;
//	
//	
//	
//	ofstream WynikiWrite;
//	WynikiWrite.open("WynikiWrite",std::ios::app);
//	if(!WynikiWrite.is_open()){
//    	cerr << "Nie otwarty plik!"<< endl;
//   	 return 1;
//	}
//	
//	ofstream WynikiSearch;
//	WynikiSearch.open("WynikiSearch",std::ios::app);
//	if(!WynikiSearch.is_open()){
//    	cerr << "Nie otwarty plik!"<< endl;
//   	 return 1;
//	}
//	
//	try {
//		WynikiWrite << "#Zapisywanie" << endl;
//		WynikiSearch << "#Wyszukiwanie" << endl;
//		for (int i=0; i<6; i++) {
//			for(int j=0; j<10; j++) {
//				IStoper * stoper = new Stoper;
//				asoc_test test(liczbaElementow[i]);
//				stoper->start();
//				test.prepare(liczbaElementow[i]);
//				stoper->stop();
//				timeW = timeW+(stoper->getElapsedTimeMs());
//				stoper->start();
//				test.run();
//				stoper->stop();
//				timeS = timeS+(stoper->getElapsedTimeMs());
//			}
//			timeW = timeW / 10;
//			timeS = timeS / 10;
//			WynikiWrite << liczbaElementow[i] << " " << timeW << endl;
//			WynikiSearch << liczbaElementow[i] << " " << timeS << endl;
//			timeW = 0;
//			timeS = 0;
//			cout << "Test dla " << liczbaElementow[i] << " zakonczony." << endl;
//		}
//	}
//	catch (CriticalException & except) {
//		cout << "Critical Exception: " << except << endl;
//	}
//	catch (ContinueException & except) {
//		cout << "Exception: " << except << endl;
//	}
//	catch (ExceptionBase & base) {
//		cout << "Exception" << base << endl;
//	}
//	catch (...) {
//		cout << "Totally unknown!" << endl;
//	}
//}
	
	
	
	
////	IAsoc<string,int> * t_asoc = new Asoc<string,int>(10);
//	try {
//		t_asoc->add("kowalski",0);
//		t_asoc->add("kowalska",1);
//		t_asoc->add("whatever",5);
//		t_asoc->add("whatever",10);
//		t_asoc->add("where",18);
//		t_asoc->add("a",15);
//		t_asoc->add("b",11);
//		t_asoc->add("c",11);
//		t_asoc->add("d",11);
//		t_asoc->add("e",11);
//		t_asoc->add("f",11);
//		t_asoc->add("g",11);
//		t_asoc->add("h",11);
//		t_asoc->add("i",11);
//		t_asoc->add("j",2);
//		t_asoc->add("k",2);
//		t_asoc->add("Wladyslaw IV Waza", 502222);
//		t_asoc->add("Wladyslaw Warnenczyk", 502222);
//		cout << t_asoc->find("whatever");
//		cout << t_asoc;
//		

//	}
//	catch (CriticalException & except) {
//		cout << "Critical Exception: " << except << endl;
//	}
//	catch (ContinueException & except) {
//		cout << "Exception: " << except << endl;
//	}
//	catch (ExceptionBase & base) {
//		cout << "Exception" << base << endl;
//	}
//	catch (...) {
//		cout << "Totally unknown!" << endl;
//	}
//}

//Przykład obsługi samego bucketa

//	try {
//		IBucket<string,int> * kosz = new Bucket<string,int>(0);
//		entry<string,int> wpis("Nowak",48);
//		kosz->add(wpis);
//		entry<string,int> wpis1("Kowalska",62);
//		kosz->add(wpis1);
//		entry<string,int> wpis2("Kowalski",2265);
//		kosz->add(wpis2);
//		entry<string,int> wpis3("Torun",200);
//		kosz->add(wpis3);
//		entry<string,int> wpis8("Torun",201);
//		kosz->add(wpis8);
//		entry<string,int> wpis4("Walbrzych",1111);
//		kosz->add(wpis4);
//		entry<string,int> wpis5("Bombsite",7358);
//		kosz->add(wpis5);
//		entry<string,int> wpis6("Ciastko",413);
//		kosz->add(wpis6);
//		kosz->remove("Nowak");
//		string user_input;
//		cin >>user_input;
//		cout << kosz->lookupWhole(user_input);
//		//kosz->printAllElements();
//	}
//	catch (CriticalException & except) {
//		cout << "Exception: " << except << endl;
//	}
//	catch (ContinueException & except) {
//		cout << "Exception: " << except << endl;
//	}
//	catch (ExceptionBase & base) {
//		cout << "Exception" << base << endl;
//	}
//	catch (...) {
//		cout << "Totally unknown!" << endl;
//	}
//}

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


