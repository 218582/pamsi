#ifndef _TABL_HH
#define _TABL_HH

/*!
 * \file
 * \brief Definicja interfejsu Itabn, klasy tabn oraz klasy tabn_test
 */
#include <iostream>
#include "run.hh"
#include "except.hh"

#define SIZE 10

/*!
 * \brief Interfejs klasy tabn
 *
 * Definiuje jednolity sposób dostępu do tablicy rozszerzalnej.
 */
template <class T>
class Itabn {
public:

	/*!
	 *\brief Sprawdza, czy tablica jest pusta
	 */
	 virtual bool isEmpty(void) = 0;
	 
	/*!
	 *\brief Dodaje element na koniec tablicy
	 */
	virtual void add(T) = 0;
	
	/*!
	 *\brief Dodaje element w dane miejsce do tablicy, przesuwając wszystkie następne elementy o miejsce w prawo
	 *\param element wstawiany element
	 *\param position indeks pola, w które ma być wstawiony element.
	 */
	virtual void add(T,int) = 0;
	
	/*!
	 *\brief Usuwa i zwraca element z końca tablicy
	 */
	virtual T remove() = 0;
	
	/*!
	 *\brief Usuwa i zwraca wybrany element z tablicy
	 *\param position indeks pola, z którego ma być usunięty element.
	 */
	virtual T remove(int) = 0;
	/*!
	 *\brief Zwraca żadany element, o ile istnieje
	 */
	virtual T show (int) const = 0;
	 
	/*!
	 *\brief Wyświetla elementy tablicy
	 */
	virtual void showElems(void) = 0;
	
	/*!
	 *\brief Zwraca liczbę elementów w tablicy
	 */
	virtual int nOE(void) = 0;
	
	/*!
	 *\brief Zwraca index ostatniego elementu
	 */
	 virtual int maxIndex(void) = 0;
	
	/*!
	 *\brief Zwraca ilość miejsca w tablicy
	 */
	virtual int aSize(void) = 0;
	
	/*!
	 *\brief Pozwala na dostęp do dowolnego elementu
	 */
	virtual T& operator [] (int) = 0;
	
	/*!
	 *\brief Pozwala na dostęp do dowolnego elementu
	 */
	virtual T operator [] (int) const = 0;
	
	/*!
	 *\brief Destruktor witrualny interfejsu
	 */
	virtual ~Itabn(){}
	
	/*!
	 *\brief Sortowanie elementów tablicy algorytmem sortowania bąbelkowego
	 *\warning Wymaga typu danych ze zdefiniowanym operatorem porównania "większe od"
	 */
	 virtual void bubblesort() = 0;
	 
	/*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval true gdy element został znaleziony
	 */
	 virtual bool search(T) = 0;
	 
	 /*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval indeks znalezionego elementu
	 */
	 virtual int searchIndex(T) = 0;
	 
	 /*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval indeks znalezionego elementu
	 */
	 virtual T searchObject(T) = 0;
	 
	 
	 //Jest OK
	 friend std::ostream & operator << (std::ostream & output, /*const - BEZ TEGO DZIAŁA*/  Itabn<T> * to) {
		for (int i=0; i<(to->nOE());i++) {
			output << to->show(i) << " ";
		}
		return output;
	}
	
	 
};


/*! \brief Modeluje tablicę dynamicznie rozszerzalną
 *
 * Przechowuje elementy w rozszerzalnej tablicy o 
 * rozmiarze początkowym SIZE
 */
template <class T>
class tabn : public Itabn<T> {
private:
	T* tab;
	int allocatedSize;
	int numberOfElems;

public:

	/*!
	 *\brief Konstruktor klasy tabn.
	 */
	tabn() {
		allocatedSize = SIZE;
		numberOfElems = 0;
		tab = new T[SIZE];
	}
	
	/*!
	 *\brief Destruktor klasy tabn.
	 */
	virtual ~tabn() {
		delete [] tab;
	}
	
private:
	
	/*!
	 *\brief Rozszerza tablicę dwukrotnie
	 *
	 * Rozszerzanie wykonywane jest poprzez stworzenie dwa razy większej tablicy,
	 * skopiowanie do niej danych, usunięcie mniejszej i zastąpienie jej nową.
	 */
	void expand2(void);
	
	/*!
	 *\brief Zmniejsza tablicę dwukrotnie
	 *
	 * Metoda pozwala na skopiowanie danych do dwa razy mniejszej tablicy i zastąpienie nią
	 * dotychczasowej.
	 *
	 *\exception ContinueException przy próbie zmniejszenia najmniejszej mozliwej tablicy
	 */
	void reduce2(void);
	
	/*!
	 *\brief Wyrzuca wyjątek, gdy tablica jest pusta
	 *
	 *\exception CriticalException gdy tablica jest pusta
	 */
	void isEmptyException (void);
	
	/*!
	 *\brief Przesuwa elementy od pozycji \link positionShifted \endlink w prawo
	 *\param element wstawiany element na zadaną pozycję
	 *\param position indeks pola, w które ma być wstawiony element. Elementy po nim następujące zostaną przesunięte o 1 w prawo
	 *
	 *\exception ContinueException przy błędnej pozycji, od której rozpoczęto przesunięcie
	 */
	 void shiftRight (T,int);
	 
	 /*!
	 *\brief Przesuwa elementy od pozycji \link positionShifted \endlink w lewo
	 *\param position indeks pola, z którego ma być usuniety element. Elementy po nim następujące zostaną przesunięte o 1 w lewo
	 *
	 *\exception ContinueException przy błędnej pozycji, od której rozpoczęto przesunięcie
	 */
	 void shiftLeft (int);
	
public:	
	
	/*!
	 *\brief Sprawdza, czy tablica jest pusta
	 *
	 *\retval 0 gdy tablica nie jest pusta
	 *\retval 1 gdy tablica jest pusta
	 */
	 virtual bool isEmpty(void);
	
	
	/*!
	 * \brief Dodaje element
	 * Dodaje element do tablicy dynamicznej, odpowiednio ją rozszerzając
	 *
	 *\param element - element do dodania
	 */
	virtual void add(T);
	
	/*!
	 *\brief Dodaje element w dane miejsce do tablicy, przesuwając wszystkie następne elementy o miejsce w prawo.
	 *\param element - wstawiany element
	 *\param positionShifted - indeks pola, w które ma być wstawiony element.
	 *
	 *\exception ContinueException WrongPositionToShiftFromRightException przy próbie dodania elementu do niewłaściwego miejsca (re-throw z tabn<T>::shiftRight(T,int)).
	 */
	virtual void add(T,int);
	
	/*!
	 * \brief Usuwa i zwraca ostatni element z tablicy.
	 *
	 **\exception CriticalException EmptyTableException przy próbie usunięcia z pustej tablicy (re-throw z tabn<T>::isEmptyException()).
	 *\exception CriticalException WrongIndexException przy próbie usunięcia z pustej tablicy (re-throw z tabn<T>::show(int)).
	 *\exception ContinueException re-throw z tabn<T>::reduce2().
	 */
	virtual T remove();
	
	/*!
	 *\brief Usuwa i zwraca wybrany element z tablicy, przesuwając wszystkie następne elementy o miejsce w lewo
	 *\param position indeks pola, z którego ma być usunięty element.
	 *
	 *\exception CriticalException EmptyTableException przy próbie usunięcia z pustej tablicy lub nieistniejącego elementu (re-throw z tabn<T>::isEmptyException()).
	 *\exception CriticalException WrongIndexException przy próbie usunięcia z pustej tablicy lub nieistniejącego elementu (re-throw z tabn<T>::show(int)).
	 *\exception ContinueException re-throw z tabn<T>::reduce2().
	 */
	virtual T remove(int);
	
	/*!
	 *\brief Zwraca żądany element, o ile istnieje, bez jego usuwania
	 *
	 *\exception CriticalException WrongIndexException przy próbie odczytania z pustej tablicy lub dostępu do nieistniejącego elementu.
	 */
	 virtual T show (int) const;

	/*!
	 * \brief Wyświetla listę elementów
	 */
	virtual void showElems(void);
	
	/*!
	 *\brief zwraca liczbę elementów w tablicy
	 *
	 *\retval int Liczba elementów w tablicy
	 */
	virtual int nOE(void);
	
	/*!
	 *\brief Zwraca index ostatniego elementu
	 */
	 virtual int maxIndex(void);
	 
	/*!
	 *\brief zwraca wielkość zaalokowanej przestrzeni dla tablicy
	 *
	 *\retval int Ilość zaalokowanych pól
	 */
	virtual int aSize(void);
	
	/*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval true gdy element został znaleziony
	 */
	 virtual bool search(T);
	 
	/*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval index indeks znalezionego elementu
	 */
	 virtual int searchIndex(T);
	 
	 /*!
	 *\brief znajduje element w tablicy
	 *
	 *\retval znaleziony element
	 */
	 virtual T searchObject(T);
	

	
	/*!
	 *\brief Umożliwia dostęp do dowolnego elementu tablicy bez
	 * sprawdzania zakresu (debug)
	 *
	 *\param index - numer elementu tablicy
	 *\retval T* Wskaźnik na wybrany element tablicy
	 */
	virtual T& operator [] (int index) {
		return tab[index];
	}

	
	/*!
	 *\brief Umożliwia odczyt dowolnego elementu tablicy bez
	 * sprawdzania zakresu (debug)
	 *
	 *\param index - numer elementu tablicy
	 *\retval T Element tablicy
	 */
	virtual T operator [] (int index) const {
		return tab[index];
	} 
	

	
private:
	/*!
	 *\brief Zamienia dwa elementy miejscami
	 *\param position1 indeks pierwszego elementu do zmiany miejscami
	 *\param position2 indeks drugiego elementu do zmiany miejscami
	 *
	 *\exception CriticalException WrongIndexException przy próbie dostępu do pustej tablicy lub nieistniejącego elementu (re-throw z tabn<T>::show(int))
	 */
	 void swap(int,int);
public:
	/*!
	 *\brief Sortowanie elementów tablicy algorytmem sortowania bąbelkowego
	 *\warning Wymaga typu danych ze zdefiniowanym operatorem porównania "większe od"
	 *
	 *\exception CriticalException re-throw z tabn<T>::swap(int,int)
	 */
	 virtual void bubblesort(void);
	 
//	 friend std::ostream & operator << (std::ostream & output, tabn<T> & to) {
//		for (int i=0; i<to.nOE();i++) {
//			output << to.show(i);
//		}
//		return output;
//	}
};


template <class T>
bool tabn<T>::search (T elem) {
	for(int i=0; i<numberOfElems; i++) {
		if (tab[i] == elem) return true;
	}
	return false;
}

template <class T>
int tabn<T>::searchIndex (T elem) {
	if (!search(elem)) throw CriticalException("ElementNotFoundCannotShowIndex");
	else {
		for(int i=0; i<numberOfElems; i++) {
			if (tab[i] == elem) return i;
		}
	}
	return -1;
}

template <class T>
T tabn<T>::searchObject (T obj) {
	return tab[searchIndex(obj)];
}


template <class T>
void tabn<T>::add (T element) {
	numberOfElems++;
	if (((numberOfElems) > allocatedSize))
		expand2(); 	
	tab[numberOfElems-1] = element;
}

template <class T>
void tabn<T>::add (T element, int position) {
	try {
		shiftRight(element,position);
	}
	catch (ContinueException &cex) {
		std::cerr << "Nastapila proba dodania elementu do niewlasciwego miejsca. (Indeks: " << position << ")" << std::endl;
		throw;
	}
	//tab[position] = element;
}

template <class T>
void tabn<T>::shiftRight (T element, int positionShifted) {
	if (positionShifted>numberOfElems) {
		throw ContinueException("WrongPositionToShiftFromRightException");
	}
	numberOfElems++;
	if (((numberOfElems) > allocatedSize))
		expand2(); 	
	T* nowy = new T[numberOfElems-positionShifted-1];
	for(int i = positionShifted,j=0;i<(numberOfElems-1);i++,j++) {
			nowy[j]=tab[i];
	}
	tab[positionShifted] = element;
	for(int i = positionShifted+1,j=0;i<(numberOfElems);i++,j++) {
			tab[i]=nowy[j];
	}
	delete [] nowy;
}

template <class T>
T tabn<T>::remove() {
	T temporary;
	try {
		isEmptyException();
		temporary = show(numberOfElems-1);
	}
	catch (CriticalException & crit_ex) {
		std::cerr << "Próba usunięcia nieistniejącego elementu." << std::endl;
		throw; 
	}
	numberOfElems--;
	if ((((numberOfElems) <= (allocatedSize/2)) && (allocatedSize > SIZE))) {
		try {
			reduce2();
		}
		catch (ContinueException & cex) {
			throw;
		}
	}
	return temporary;
}

template <class T>
T tabn<T>::remove(int position) {
	T temporary;
	try {
		isEmptyException();
		temporary = show(position);
	}
	catch (CriticalException & crit_ex) {
		std::cerr << "Próba usunięcia nieistniejącego elementu." << std::endl;
		throw;
	}
	try {
		shiftLeft(position); //Uwaga - shiftLeft dekrementuje numberOfElems.
	}
	catch (ContinueException & cex) {
		std::cerr << "Nastapila proba usuniecia elementu z niewlasciwego miejsca. (Indeks: " << position << ")" << std::endl;
		throw;
	}
	if ((((numberOfElems) <= (allocatedSize/2)) && (allocatedSize > SIZE))) {
		try {
			reduce2();
		}
		catch (ContinueException & cex) {
			throw;
			
		}
	}
	return temporary;
}

template <class T>
void tabn<T>::shiftLeft(int positionShifted) {
	if (positionShifted>numberOfElems) {
		throw ContinueException("WrongPositionToShiftFromLeftException");
	}
	
	T* nowy = new T[numberOfElems-positionShifted-1];
	for(int i = positionShifted+1,j=0;i<(numberOfElems);i++,j++) {
			nowy[j]=tab[i];
	}
	numberOfElems--;
	for(int i = positionShifted,j=0;i<(numberOfElems);i++,j++) {
			tab[i]=nowy[j];
	}
	delete [] nowy;
}

template <class T>
void tabn<T>::expand2(void) {
	T* nowy = new T[allocatedSize*2];
	allocatedSize*=2;
	for (int i=0; i<=(numberOfElems-2); i++) {
		nowy[i] = tab[i];
	}
	delete [] tab;
	tab = nowy;
}

template <class T>
void tabn<T>::reduce2(void) {
	if(allocatedSize <= SIZE) {
		throw ContinueException("SmallestTableException");
	}
	T* nowy = new T[allocatedSize/2];
	allocatedSize=allocatedSize/2;
	for (int i=0;i<=(numberOfElems-1);i++){
		nowy[i] = tab[i];
	}
	delete [] tab;
	tab = nowy;
}

template <class T>
bool tabn<T>::isEmpty(void) {
	if (numberOfElems <= 0) {
		return 1;
	}
	else return 0;
}

template <class T>
void tabn<T>::isEmptyException (void) {
	if (numberOfElems <= 0) {
		throw CriticalException("EmptyTableException");
	}
	else {}
}

template <class T>
T tabn<T>::show(int position) const {
	if (position>=numberOfElems || position<0) {
		throw CriticalException("WrongIndexException");
	}
	else {
		return tab[position];
	}
}

template <class T>
void tabn<T>::showElems (void) {
		for (int i=0; i<numberOfElems; i++) {
			std::cout << tab[i] << '\n';
		}
		std::cout << std::endl;
	}
	

	
template <class T>
int tabn<T>::nOE(void) {
		return numberOfElems;
	}

template <class T>
int tabn<T>::maxIndex(void) {
	return numberOfElems-1;
}
	
template <class T>
int tabn<T>::aSize(void) {
		return allocatedSize;
	}
	
template <class T>
void tabn<T>::swap(int position1, int position2) {
	T element1;
	T element2;
	try {
		element1 = show(position1);
		element2 = show(position2);
	}
	catch (CriticalException & crit_ex) {
		std::cerr << "Próba uzyskania dostępu do nieistniejącego elementu." << std::endl;
		throw;
	}
	tab[position1]=element2;
	tab[position2]=element1;
}
	
template <class T>
void tabn<T>::bubblesort (void) {
	int i,j;
	for (j = 0; j<(numberOfElems-1);j++) {
		for (i = 0; i<(numberOfElems-1);i++) {
			if(tab[i] > tab[i+1]) {
				try {
					swap(i,i+1);
				}
				catch (CriticalException & crit_ex) {
					throw;
				}
			}
		}
	}
}

	
	
	
	
	
	
	
	
	
	

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/*! \brief Definiuje sposób testowania wypełniania tablicy tabn
 *
 */
class tabn_test : public IRunnable  {
private:
	Itabn<int> * test;
	int counter;
public:
	/*!
	 * \brief Konstruktor klasy tabn_test.
	 */
	tabn_test () : test (new tabn<int>) {
		seedSrand();
	}
	/*!
 	 * \brief Destruktor klasy tabn_test.
	 */
	virtual ~tabn_test () {
		delete test;
	}
	
private:

	/*!
	 * \brief Metoda ustawia punkt startowy generatora
	 * pseudolosowego.
	 */
	void seedSrand (void) {
		srand(time(NULL));
	}
	
	/*!
	 * \brief Metoda generuje liczbę pseudolosową z zakresu 0..9
	 *
	 *\retval Liczba pseudolosowa z zakresu 0..9
	 */
	int generateRandomDgt (void) {
		return rand()%10;
	}


public:		
	/*!
 	 * \brief Przygotowuje rozmiar testu
 	 *
 	 * \param sizeOfTest - rozmiar testu
 	 * \retval bool zawsze true
	 */
	virtual bool prepare(int sizeOfTest) {
		counter = sizeOfTest;
		return true;
	}
	
	/*!
 	 * \brief Wykonuje test
 	 *
 	 * Pozwala na wykonanie testu w pętli for iterującej
 	 * \link counter \endlink razy. Zasila funkcję dodawania
 	 * generując losowe cyfry w funkcji 
 	 * \link generateRandomDgt() \endlink
 	 *
 	 * \retval bool zawsze true
 	 *
 	 * \exception ContinueException re-throw tabn<T>::add(int)
	 */
	virtual bool run() {
		try {
			for (;counter>0;counter--) {
				test->add(generateRandomDgt());
			}
		}
		catch (...) {
			throw;
		}
		std::cout << "SIZE:  " << test->aSize() << std::endl;
		std::cout << "Elems: " << test->nOE() << std::endl;
		return true;
	}
};


#endif
