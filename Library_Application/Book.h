#ifndef BOOK_H_
#define BOOK_H_
#include <iostream>
#include <iomanip>
#include "Publication.h"

class Book : public Publication{
	char* m_author;		// C-string to hold an author's name.
public:
	Book();								// Default constructor.

	// Rules of three
	~Book();							// Destructor.
	Book(const Book& src);				// Copy constructor.
	Book& operator=(const Book& src);	// Overload copy assign operator.

	char type() const;								// Always return 'B'.
	std::ostream& write(std::ostream& os) const;	// Method to check the os argument is a console IO object of the book object and display the values as format.
	std::istream& read(std::istream& is);			// Method to read all the values in local variables before setting the attributes to any values.
	void set(int member_id);						// Method to set the member ID.
	operator bool() const;							// Verify the author's name method.
};

#endif //!BOOK_H_