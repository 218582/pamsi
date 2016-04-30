#include "../inc/tree.hh"

std::ostream & operator << (std::ostream & output, Colour col) {
	if (col == red) {
		output << "red";
	} 
	else if (col == black) {
		output << "black";
	}
	return output;
}
