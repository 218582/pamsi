#ifndef _LISTA_HH
#define _LISTA_HH

/*!
 *\file Plik definiuje typ danych lista
 *
 */
#include "tabl.hh"
#include <fstream>
 
 /*!
  *\brief Interfejs listy
  *
  * Definiuje dostępne operacje na klasie Lista
  */
template <class T>
class ILista {
public:
	/*!
	 *\brief Dodaje element do zadanego miejsca listy
	 *
	 * Jeśli następuje próba dodania elementu w miejscu istniejącego, następuje przesunięcie następujących po nim
	 * elementów na następne pozycje
	 * \note Próba dodania elementu na miejsce dalsze niż pierwsze następujące po obecnie istniejącym spowoduje wyrzucenie wyjątku.
	 */
	virtual void add(T, int) = 0;
	
	/*!
	 *\brief Dodaje element na koniec listy
	 */
	virtual void add(T)=0;
	
	/*!
	 *\brief Usuwa element z zadanego miejsca listy
	 *
	 * Jeśli usunięcie następuje w środku listy, następujące po usuwanym elementy są przesuwane
	 * o jedną pozycję wcześniej.
	 * \retval T Usunięty element
	 * \warning Próba usunięcia elementu nieistniejącego lub z pustej listy spowoduje wyrzucenie wyjątku.
	 * \warning Sprawdź dokumentację metody Lista<T>::remove(int).
	 */
	virtual T remove(int) = 0;
	
	/*!
	 *\brief Usuwa element z końca listy
	 */
	virtual T remove(void) = 0;
	
	/*!
	 *\brief Sprawdza, czy lista jest pusta
	 *\retval 0 gdy niepusta
	 *\retval 1 gdy pusta
	 */
	virtual bool isEmpty(void) = 0;
	
	/*!
	 *\brief Zwraca element z zadanego miejsca bez usunięcia
	 *\retval T element w zadanym miejscu
	 * \warning Próba podglądu elementu nieistniejącego spowoduje wyrzucenie wyjątku.
	 * \warning Sprawdź dokumentację metody Lista<T>::get(int).
	 */
	virtual T get(int) = 0;
	
	/*!
	 *\brief Zwraca ilość elementów w liście
	 *\retval int ilość elementów
	 */
	virtual int size(void) = 0;
	
	virtual void qs(int,int) = 0;
	
	/*!
	 *\brief Destruktor wirtualny interfejsu ILista
	 */
	virtual ~ILista() {}
};

/*!
 *\brief Klasa lista
 *
 * Modeluje pojęcie listy
 */
template <class T>
class Lista : public ILista<T>{
private:
	Itabn<T> * tablica/* = new tabn<T>*/;
public:
	/*!
	 *\brief Konstruktor tablicy obsługującej listę
	 */
	Lista () : tablica (new tabn<T>) {}
	
	/*!
	 *\brief Dodaje element do zadanego miejsca listy
	 *
	 * Jeśli następuje próba dodania elementu w miejscu istniejącego, następuje przesunięcie następujących po nim
	 * elementów na następne pozycje
	 *
	 * \exception ContinueException re-throw z tabn<T>::add(T,int)
	 * \note Próba dodania elementu na miejsce dalsze niż pierwsze następujące po obecnie istniejącym spowoduje wyrzucenie wyjątku.
	 */
	virtual void add (T,int);
	
	/*!
	 *\brief Dodaje element na koniec listy
	 */
	virtual void add(T);
	
	/*!
	 *\brief Usuwa element z zadanego miejsca listy
	 *
	 * Jeśli usunięcie następuje w środku listy, następujące po usuwanym elementy są przesuwane
	 * o jedną pozycję wcześniej.
	 * \retval T Usunięty element
	 * \exception CriticalException re-throw z tabn<T>::remove()
	 * \exception ContinueException re-throw z tabn<T>::remove()
	 * \warning Próba usunięcia elementu nieistniejącego lub z pustej listy spowoduje wyrzucenie wyjątku.
	 * \warning Przykład sprawdzenia:
	 * \warning
	 	\code{.cpp}
	 	//Przykład sprawdzenia poprawności usuwania
	 	ILista<int> * list = new Lista<int>;
	 	list->add(2); //skomentuj odpowiednio linię aby sprawdzić działanie obu przypadków
	 	int positionToCheckAndRemove = 0;
	 	if(list->size()>positionToCheckAndRemove) {
	 		list->remove(positionToCheckAndRemove);
	 	}
	 	else
	 		cerr << "Element nie istnieje!" << endl;
	 	\endcode
	 */
	virtual T remove (int position);
	
	/*!
	 *\brief Usuwa element z końca listy
	 */
	virtual T remove(void);
	
	/*!
	 *\brief Sprawdza, czy lista jest pusta
	 *\retval 0 gdy niepusta
	 *\retval 1 gdy pusta
	 */
	virtual bool isEmpty (void);
	
	/*!
	 *\brief Zwraca element z zadanego miejsca bez usunięcia
	 *\retval T element w zadanym miejscu
	 *\exception CriticalException re-throw z tab<T>::show(int)
	 * \warning Próba podglądu elementu nieistniejącego spowoduje wyrzucenie wyjątku.
	 * \warning Przykład sprawdzenia:
	 * \warning
	 	\code{.cpp}
	 	//Przykład sprawdzenia poprawności podglądu
	 	ILista<int> * list = new Lista<int>;
	 	list->add(2); //skomentuj odpowiednio linię aby sprawdzić działanie obu przypadków
	 	int positionToCheckAndShow = 0;
	 	if(list->size()>positionToCheckAndShow) {
	 		cout << list->get(positionToCheckAndShow) << endl;
	 	}
	 	else
	 		cerr << "Element nie istnieje!" << endl;
	 	\endcode
	 */
	virtual T get (int position);
	
	/*!
	 *\brief Zwraca ilość elementów w liście
	 *\retval int ilość elementów
	 */
	virtual int size (void);
	
private:
	void swap(int,int);
	
public:
	virtual void qs(int,int);

	
	/*!
	 *\brief Destruktor Listy
	 */
	virtual ~Lista () {
		delete tablica;
	}
};

template <class T>
void Lista<T>::add(T element, int position) {
	try {
		tablica->add(element,position);
	}
	catch (...) {
		throw;
	}
}

template <class T>
void Lista<T>::add(T element) {
	tablica->add(element);
}

template <class T>
T Lista<T>::remove(int position) {
	T temporary;
	try {
		temporary = tablica->remove(position);
	}
	catch (...) {
		throw;
	}
	return temporary;
}

template <class T>
T Lista<T>::remove(void) {
	return tablica->remove((tablica->nOE())-1);
}

template <class T>
bool Lista<T>::isEmpty(void) {
		return tablica->isEmpty();
}

template <class T>
T Lista<T>::get(int position) {
	T temporary;
	try {
		temporary = tablica->show(position);
	}
	catch (...) {
		throw;
	}
	return temporary;
}

template <class T>
int Lista<T>::size(void) {
	return tablica->nOE();
}

template <class T>
void Lista<T>::swap(int positionOne, int positionTwo) {
	T elementOne;
	T elementTwo;
	try {
		elementOne = get(positionOne);
		elementTwo = get(positionTwo);
		remove(positionOne);
		add(elementTwo,positionOne);
		remove(positionTwo);
		add(elementOne,positionTwo);
	}	
	catch (...) {
		throw;
	}
}


template <class T>
void Lista<T>::qs(int indexFront, int indexBack) {
  	if (indexBack == 0) {throw CriticalException();}
	int i = indexFront;
	int j = indexBack;
	T pivot = get((i+j)/2);
  	try{
  		do {
			while(get(i) < pivot) {
				i=i+1;
			}
			while (get(j) > pivot) {
				j=j-1;
			}
			if (i<=j) {
				swap(i,j);
				i=i+1;
				j=j-1;
			}
		} while (i<=j);
		if (indexFront < j) {
			qs (indexFront, j);
		}
		if (indexBack > i) {
			qs (i, indexBack);
		}
	}
  	catch(...) {
  		throw;
  	}
  }







//------------------------------------------------------------------------------

/*! \brief Definiuje sposób testowania wypełniania listy
 *
 */
class lista_test : public IRunnable  {
private:
	ILista<std::string> * test;
	int counter = 0;
	std::fstream plik;
	std::string wordToSearch;
public:
	
	/*!
	 *\brief Konstruktor klasy testującej
	 *
	 */
	lista_test () : test(new Lista<std::string>) {
	}
	
	/*!
	 *\brief Destruktor klasy testującej
	 */
	~lista_test () {
		plik.close();
		delete test;
	}
	
private:

	/*!
	 *\brief Porównywanie słów
	 *\exception CriticalException re-throw z Lista::get(int)
	 */
	bool wordSearch(std::string word) {
		int i = 0;
		try {
			while(i<counter) {
			 	if(test->get(i) == word) {
			 		//cout << "Word found at position " << i <<endl;
			 		return true;
			 	}
			 	i+=1;
			}
		//cout << "Word not found"<< endl << endl;
		}
		catch (...) {
			throw;
		}
		return false;
	}

public:
	/*!
 	 * \brief Przygotowuje rozmiar testu
 	 *
 	 * \param sizeOfTest - rozmiar testu
 	 * \retval true gdy plik ze słownikiem został pomyślnie otwarty
 	 * \retval false gdy otwieranie pliku zakończyło się błędem
 	 * \exception CriticalException gdy wystąpił błąd przy otwarciu pliku
	 */
	virtual bool prepare(int sizeOfTest) {
		counter = sizeOfTest;
		int i = 0;
		std::string word;
		wordToSearch = "reminder";
		plik.open("largest",std::ios::in);
		if (plik.good() == true) {
			while (plik >> word || i<sizeOfTest) {
				test->add(word);
				i+=1;
			}
			//cout << "Found at: " << i << endl;
			plik.close();
			return true;
		}
		else {
			plik.close();
			throw CriticalException("FileError");
		}
		return false;
	}
	
	/*!
 	 * \brief Wykonuje test
 	 *
 	 * Pozwala na wykonanie testu.
 	 *
 	 * \retval true gdy test zakończył się sukcesem
 	 * \retval false gdy test zakończył się niepomyślnie
 	 * \exception CriticalException re-throw z lista_test::wordSearch(std::string)
	 */
	virtual bool run() {
		try {
			return wordSearch(wordToSearch);
		}
		catch (...) {
			throw;
		}
	}
	
};

#endif
