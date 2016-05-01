#include "../inc/tree.hh"

std::ostream & operator << (std::ostream & output, Colour col) {
	if (col == red) {
		output << "R";
	} 
	else if (col == black) {
		output << "B";
	}
	return output;
}
