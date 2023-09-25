#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"

// Empty destructor.
Streamable::~Streamable() {}

/* Overload extraction operator to print content from draw() function in the Shape class. */
std::ostream& operator<<(std::ostream& os, const Streamable& ins) {

	if (ins) {
		ins.write(os);
	}
	return os;
}

/* Overload insertion operator to get content from getSpec() function in the Shape class. */
std::istream& operator>>(std::istream& in, Streamable& ext) {
	return ext.read(in);
}