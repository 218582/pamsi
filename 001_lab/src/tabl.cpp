#include "../inc/tabl.hh"

void tabn::setExpandMode(expandType type) {
	expandMode = type;
}

void tabn::add (int element) {
	switch (expandMode) {
		case one:
			addElemLast(element); break;
		case twice:
			addElemDoubleTabl(element); break;
		case onehalf:
			addElem1Tabl5(element); break;
		default:
			break;
	}
}


void tabn::addElemLast(int elem) {
		 numberOfElems++;
		 if (numberOfElems <= allocatedSize) {
		 	tab[numberOfElems-1] = elem; 
		 }
		 else {
		 	int* nowy = new int[numberOfElems];
		 	allocatedSize++;
		 	for (int i=0; i<=(numberOfElems-2); i++) {
		 		nowy[i] = tab[i];
		 	}		 	
		 	nowy[numberOfElems-1] = elem;
		 	delete [] tab;
		 	tab = nowy;
		 }
	}
	
void tabn::addElemDoubleTabl(int elem) {
		numberOfElems++;
		if (numberOfElems <= allocatedSize) {
			tab[numberOfElems-1] = elem; 
		}
		else {
			int* nowy = new int[allocatedSize*2];
		 	allocatedSize*=2;
		 	for (int i=0; i<=(numberOfElems-2); i++) {
		 		nowy[i] = tab[i];
		 	}		 	
		 	nowy[numberOfElems-1] = elem;
		 	delete [] tab;
		 	tab = nowy;
		}
}

void tabn::addElem1Tabl5 (int elem) {
		numberOfElems++;
		if (numberOfElems <= allocatedSize) {
			tab[numberOfElems-1] = elem; 
		}
		else {
			int* nowy = new int[allocatedSize+(allocatedSize/2)];
		 	allocatedSize=allocatedSize+(allocatedSize/2);
		 	for (int i=0; i<=(numberOfElems-2); i++) {
		 		nowy[i] = tab[i];
		 	}		 	
		 	nowy[numberOfElems-1] = elem;
		 	delete [] tab;
		 	tab = nowy;
		}
}

int& tabn::operator [] (int index) {
	return tab[index];
}

int tabn::operator [] (int index) const {
	return tab[index];
}
	
void tabn::showElems (void) {
		for (int i=0; i<numberOfElems; i++) {
			cout << tab[i] << " ";
		}
		cout << endl;
	}
	
int tabn::nOE(void) {
		return numberOfElems;
	}
	
int tabn::aSize(void) {
		return allocatedSize;
	}
	
void tabn_test::seedSrand (void) {
	srand(time(NULL));
}
	
int tabn_test::generateRandomDgt (void) {
	return rand()%10 + 1;
}


void tabn_test::setTypeOfExpansion(expandType type) {
	test->setExpandMode(type);
}


bool tabn_test::prepare (int sizeOfTest) {
	counter = sizeOfTest;
	setTypeOfExpansion(twice);
	return true;
}

bool tabn_test::run (void) {
	for (;counter>0;counter--) {
			test->add(randomDgtToWrite);
	}
	cout << "SIZE:  " << test->aSize() << endl;
	cout << "Elems: " << test->nOE() << endl;
	return true;
}

