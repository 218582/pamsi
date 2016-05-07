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
	 *\brief Wyświetlanie kolejki
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




/*!
 *\brief Węzeł kolejki
 */
template <class T>
class node {
public:
	T value;
	class node<T> * next;
	class node<T> * previous;
	
	node<T> (T o) : value(o), next(NULL), previous(NULL){
	}
	
	node<T> (void) : next(NULL), previous(NULL) {
	}
	

	node<T> & operator = (const node<T> & read) {
		value=read.value;
		next=read.next;
		previous=read.previous;
		return * this;
	}
	
	friend bool operator < (node<T> one, node<T> two) {
		if (one.value < two.value) return true;
		else return false;
	}
	
	friend bool operator > (node<T> one, node<T> two) {
		if (one.value > two.value) return true;
		else return false;
	}
	
	friend bool operator <= (node<T> one, node<T> two) {
		if (one.value <= two.value) return true;
		else return false;
	}
	
	friend bool operator >= (node<T> one, node<T> two) {
		if (one.value >= two.value) return true;
		else return false;
	}
	
	friend bool operator == (node<T> one, node<T> two) {
		if (one.value == two.value) return true;
		else return false;
	}
	
	friend std::ostream & operator << (std::ostream & output, const node<T> & to) {
		output << to.value;
		return output;
	}	
};

template <class T>
class IQueue {
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
	virtual ~IQueue() {}
	
	private:

	/*!
	 *\brief Wyświetlanie kolejki
	 */
	virtual void print (std::ostream &)=0;

public:	
	/*!
	 *\brief Przeciążenie operatora <<
	 */
	friend std::ostream & operator << (std::ostream & output, IQueue * to) {
		to->print(output);
		return output;
	}
	
};

/*!
 *\brief Kolejka oparta na węzłach
 */
template <class T>
class Queue: public IQueue<T> {
private: 
	node<T> * first;
	node<T> * last;

public:
	Queue (void): first(NULL), last(NULL) {
	}
	
private:
	virtual void print (std::ostream & output) {
		if(first==NULL) output << "Empty Queue\n";
		node<T> *it = new node<T>;
		it = first;
		while (it!=NULL) {
			output << it->value << " ";
			it=it->next;
		}
	}
	
public:

	/*!
	 *\brief Dodaje element na koniec kolejki
	 *
	 *\param element - element do umieszczenia w kolejce
	 */
	virtual void enqueue(T element) {
		node<T> * newElement = new node<T>(element);
//		newElement->next = NULL;
		newElement->previous = last;
		last = newElement;
		if (newElement->previous == NULL) {
			first = newElement;
		}
		else {
			newElement->previous->next = newElement;
		}
	}
	
	/*!
	 *\brief Usuwa i zwraca element z początku kolejki
	 *\retval T element z początku kolejki
	 */
	virtual T dequeue(void) {
		if (first==NULL && last==NULL) throw ContinueException("EmptyQueueDequeue");
		T retval = first->value;
		node<T> * elementToDelete = new node<T>();
		elementToDelete = first;
		if(first==last) {
			first=last=NULL;
		}
		else {
			first = first->next;
		}
		delete elementToDelete;
		return retval;
	}
	
	/*!
	 *\brief Sprawdza, czy kolejka nie jest pusta
	 *\retval 0 gdy niepusta
	 *\retval 1 gdy pusta
	 */
	virtual bool isEmpty(void) {
		if (first==NULL) return true;
		else return false;
	}
	
	/*!
	 *\brief Zwraca element z początku kolejki bez usuwania
	 */
	virtual T get(void) {
		if(first==NULL) throw CriticalException("EmptyQueueGet");
		return first->value;
	}
	
	/*!
	 *\brief Destruktor 
	 */
	virtual ~Queue() {
		delete first;
	}
	
};










#endif
