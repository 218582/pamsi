#ifndef _EXCEPT_HH
#define _EXCEPT_HH

/*!
 *\file
 *\brief Plik zawiera definicje wyjątków
 */

#include <iostream>
#include <string>
#include <exception>
/*!
 *\brief Ogólny wyjątek
 */
class ExceptionBase{
public:
	std::string cause;
	
	ExceptionBase() {
	}
	
    ExceptionBase(std::string description) : cause(description){
    }
    
    virtual void Throw() {
    	throw *this;
    }
    
    friend std::ostream & operator << (std::ostream & output, const ExceptionBase & to) {
		output << to.cause;
		return output;
	}
};

/*!
 *\brief Wyjątek krytyczny, wymagający zamknięcia programu
 */
class CriticalException : public ExceptionBase {
public:
	
	CriticalException() : ExceptionBase("none") {
	}
	
	CriticalException(std::string description) : ExceptionBase(description) {
    }
    
    virtual void Throw() {
    	throw *this;
    }

};

/*!
 *\brief Wyjątek, który może spowodować nieprzewidziane działanie programu, ale program mógłby dalej działać.
 */
class ContinueException : public ExceptionBase {
public:

	ContinueException() : ExceptionBase("none") {
	}
	
 	ContinueException(std::string description) : ExceptionBase(description) {
    }
    
    virtual void Throw() {
    	throw *this;
    }

 };
 
template <class ExceptT>
void what (ExceptT & except)
{
  except.Throw();
}


#endif
