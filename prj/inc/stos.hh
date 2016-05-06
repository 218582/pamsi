#ifndef _STOS_HH
#define _STOS_HH

/*!
 *\file Plik definiuje typ danych stos
 *
 */
 #include "tabl.hh"

 /*!
  *\brief Interfejs stosu
  *
  * Definiuje dostępne operacje na klasie Stos
  */
template <class T>
class IStos {
public:
	/*!
	 *\brief Umieszcza element na szczycie stosu
	 *
	 * \param element - element do umieszczenia na stosie
	 */
	virtual void push(T) = 0;
	
	/*!
	 *\brief Zdejmuje element ze szczytu stosu
	 *
	 * \retval T element ze szczytu stosu
	 *\warning Uwaga! Próba zdjęcia elementu z pustego stosu spowoduje wyrzucenie wyjątku 
	 *\warning Sprawdź dokumentację metody Stos<T>::pop(void).
	 */
	virtual T pop(void) = 0;
	
	/*!
	 *\brief Sprawdza, czy stos jest pusty
	 *\retval 0 gdy niepusty
	 *\retval 1 gdy pusty
	 */
	virtual bool isEmpty(void) = 0;
	
	/*!
	 *\brief Zwraca element ze szczytu stosu bez jego usuwania
	 *
	 *\retval T element ze szczytu stosu
	 *\warning Uwaga! Próba odczytania elementu z pustego stosu spowoduje wyrzucenie wyjątku 
	 *\warning Sprawdź dokumentację metody Stos<T>::get(void).
	 */
	virtual T get(void) = 0;
	
	/*!
	 *\brief Destruktor wirtualny IStos
	 */
	virtual ~IStos(){}
	
private:

	/*!
	 *\brief Wyświetlanie stosu
	 */
	virtual void print (std::ostream &)=0;

public:	
	/*!
	 *\brief Przeciążenie operatora <<
	 */
	friend std::ostream & operator << (std::ostream & output, IStos * to) {
		to->print(output);
		return output;
	}
};


/*!
 *\brief Klasa Stos
 *
 * Modeluje pojęcie stosu
 */
template <class T>
class Stos : public IStos<T> {
private:
	Itabn<T> * tablica/* = new tabn<T>*/;
public:
	/*!
	 *\brief Konstruktor tablicy obsługującej stos
	 */
	Stos() : tablica (new tabn<T>) {}
	
	/*!
	 *\brief Umieszcza element na szczycie stosu
	 *
	 * \param element - element do umieszczenia na stosie
	 */
	virtual void push(T);
	
	/*!
	 *\brief Zdejmuje element ze szczytu stosu
	 *
	 * \retval T element ze szczytu stosu
	 * \exception CriticalException re-throw z tabn<T>::remove()
	 * \exception ContinueException re-throw z tabn<T>::remove()
	 *
	 *\warning Uwaga! Próba zdjęcia elementu z pustego stosu spowoduje wyrzucenie wyjątku
	 *\warning Przykład sprawdzenia:
	 *\code{.cpp}
	 	//Przykład korzystania z get()
	 	IStos<int> * stos = new Stos<int>;
	 	if (stos->isEmpty() == false) {
			cout << stos->pop() << endl;
			}
		else
			cerr << "Stos pusty" << endl;
		\endcode
	 */
	virtual T pop(void);
	
	/*!
	 *\brief Sprawdza, czy stos jest pusty
	 *\retval 0 gdy niepusty
	 *\retval 1 gdy pusty
	 */
	virtual bool isEmpty(void);
	
	/*!
	 *\brief Zwraca element ze szczytu stosu bez jego usuwania
	 *
	 *\retval T element ze szczytu stosu
	 *\exception CriticalException re-throw z tabn<T>::show(int)
	 *\warning Uwaga! Próba odczytania elementu z pustego stosu spowoduje wyrzucenie wyjątku 
	 *\warning Przykład sprawdzenia:
	 *\code{.cpp}
	 	//Przykład korzystania z get()
	 	IStos<int> * stos = new Stos<int>;
	 	if (stos->isEmpty() == false) {
			cout << stos->get() << endl;
			}
		else
			cerr << "Stos pusty" << endl;
		\endcode
	 */
	virtual T get(void);
	
	/*!
	 *\brief Destruktor stosu
	 */
	virtual ~Stos(){
		delete tablica;
	}
	
private:
	virtual void print (std::ostream & output) {
		output << tablica;
	}
	
};

template <class T>
void Stos<T>::push(T element) {
	tablica->add(element);
}

template <class T>
T Stos<T>::pop(void) {
	T temporary;
	try {
		temporary = tablica->remove();
	}
	catch (...) {
		throw;
	}
	return temporary;
}

template <class T>
bool Stos<T>::isEmpty(void) {
	return tablica->isEmpty();
}

template <class T>
T Stos<T>::get(void) {
	T temporary;
	try {
		temporary = tablica->show((tablica->nOE())-1);
	}
	catch (...) {
		throw;
	}
	return temporary;
}

#endif
