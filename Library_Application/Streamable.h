#ifndef STREAMABLE_H_
#define STREAMABLE_H_
#include <iostream>

class Streamable {
public:
	virtual std::ostream& write(std::ostream& os) const = 0;	// Pure virtual functions overriding this function will write into an ostream object.
	virtual std::istream& read(std::istream& is) = 0;			// Pure virtual functions overriding this function will read from an istream object.
	virtual bool conIO(std::ios& io) const = 0;			// Pure virtual functions overriding this function will determine if the incoming ios object is a console IO object or not.
	virtual operator bool() const = 0;				// Pure virtual overloading boolean type conversion.
	virtual ~Streamable();							// virtual Destructor.
};
std::ostream& operator<<(std::ostream& os, const Streamable& istr);	// Overload insertion operator.
std::istream& operator>>(std::istream& is, Streamable& ext);			// Overload extraction operator

#endif //!STREAMABLE_H_