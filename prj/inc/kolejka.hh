#ifndef _KOLEJKA_HH
#define _KOLEJKA_HH
/*!
 *\file Plik definiuje typ danych kolejka
 *
 */
 #include "tabl.hh"


/*!
 *\brief Interfejs klasy Kolejka
 * Definiuje operacje dostępne dla klasy Kolejka
 */
template <class T>
class IKolejka {
public:
	/*!
	 *\brief Dodaje element na koniec kolejki
	 *
	 *\param element - element do umieszczenia w kolejce
	 */
	virtual void enqueue(T) = 0;
	
	/*!
	 *\brief Usuwa i zwraca element z początku kolejki
	 *\retval T element z początku kolejki
	 */
	virtual T dequeue(void) = 0;
	
	/*!
	 *\brief Sprawdza, czy kolejka nie jest pusta
	 *\retval 0 gdy niepusta
	 *\retval 1 gdy pusta
	 */
	virtual bool isEmpty(void) = 0;
	
	/*!
	 *\brief Zwraca element z początku kolejki bez usuwania
	 *\warning Uwaga! Próba podglądu elementu z pustej kolejki spowoduje wyrzucenie wyjątku
	 *\warning Sprawdź dokumentację metody Kolejka<T>::get(void).
	 */
	virtual T get(void) = 0;
	
	/*!
	 *\brief Destruktor wirtualny interfejsu
	 */
	virtual ~IKolejka() {}
	
	private:

	/*!
	 *\brief Wyświetlanie stosu
	 */
	virtual void print (std::ostream &)=0;

public:	
	/*!
	 *\brief Przeciążenie operatora <<
	 */
	friend std::ostream & operator << (std::ostream & output, IKolejka * to) {
		to->print(output);
		return output;
	}
};

/*!
 *\brief Klasa modeluje kolejkę
 */
template <class T>
class Kolejka : public IKolejka<T>{
private:
	Itabn<T> * tablica/* = new tabn<T>*/;
public:
	/*!
	 *\brief Konstruktor tablicy obsługującej kolejkę
	 */
	Kolejka() : tablica (new tabn<T>) {}
	
	/*!
	 *\brief Dodaje element na koniec kolejki
	 *
	 *\param element - element do umieszczenia w kolejce
	 */
	virtual void enqueue(T);
	
	/*!
	 *\brief Usuwa i zwraca element z początku kolejki
	 *\retval T element z początku kolejki
	 *\exception CriticalException re-throw z tabn<T>::remove()
	 *\exception ContinueException re-throw z tabn<T>::remove()
	 */
	virtual T dequeue(void);
	
	/*!
	 *\brief Sprawdza, czy kolejka nie jest pusta
	 *\retval 0 gdy niepusta
	 *\retval 1 gdy pusta
	 */
	virtual bool isEmpty(void);
	
	/*!
	 *\brief Zwraca element z początku kolejki bez usuwania
	 *
	 *\retval T element z początku kolejki
	 *\exception CriticalException re-throw z tab::show(int)
	 *\warning Uwaga! Próba odczytania elementu z pustej kolejki spowoduje wyrzucenie wyjątku.
	 *\warning Przykład sprawdzenia:
	 *\code{.cpp}
	 	//Przykład korzystania z get()
	 	IKolejka<int> * kolejka = new Kolejka<int>;
	 	if (kolejka->isEmpty() == false) {
			cout << kolejka->get() << endl;
			}
		else
			cerr << "Kolejka pusta" << endl;
		\endcode
	 */
	virtual T get(void);
	
	/*!
	 *\brief Destruktor klasy Kolejka
	 */
	virtual ~Kolejka() {
		delete tablica;
	}
	
	private:
	virtual void print (std::ostream & output) {
		output << tablica;
	}
};

template <class T>
void Kolejka<T>::enqueue(T element) {
	tablica->add(element,(tablica->nOE()));
}


template <class T>
T Kolejka<T>::dequeue(void) {
	T temporary;
	try {
		temporary = tablica->remove(0);
	}
	catch (...) {
		throw;
	}
	return temporary;
}

template <class T>
bool Kolejka<T>::isEmpty(void) {
	return tablica->isEmpty();
}

template <class T>
T Kolejka<T>::get(void) {
	T temporary;
	try {
		temporary = tablica->show(0);
	}
	catch (...) {
		throw;
	}
	return temporary;
}











#endif
