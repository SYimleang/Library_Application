#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Book.h"

/* Default constructor. Set author's name to null. */
Book::Book() {
	m_author = nullptr;
}

/* Copy constructor. Copy receive Book object to current object. */
Book::Book(const Book& src) : Publication(src) {

	// Check if author's name is exists, then deallocate author's name attribute and set to null.
	if (m_author) {
		delete[] m_author;
		m_author = nullptr;
	}

	// Allocating author's name attribute and copy receive author's name object to current object.
	m_author = new char[strlen(src.m_author) + 1];
	strcpy(m_author, src.m_author);
}

/* Copy assignment operator. Copy receive Book object to current object. */
Book& Book::operator=(const Book& src) {

	// Invoke assign operator of the Base class.
	Publication::operator=(src);

	// Check if author's name is exists, then deallocate author's name attribute and set to null.
	if (m_author) {
		delete[] m_author;
		m_author = nullptr;
	}

	// Check if receive author's name object is exists, then allocating author's name of current object and copy receive author's name object to current object.
	if (src.m_author) {
		m_author = new char[strlen(src.m_author) + 1];
		strcpy(m_author, src.m_author);
	}

	return *this;
}

/* Destructor. Deallocate author's name. */
Book::~Book() {
	delete[] m_author;
}

// Return character 'B'
char Book::type() const {
	return 'B';
}

/* First invoke write function from the base class, then check if the os argument is a console IO object, print shelfId, title, author, membership and date attributes. */
std::ostream& Book::write(std::ostream& os) const {

	// Invoke the write of the Base class.
	Publication::write(os);

	// Check if the incoming argument is a console IO object, then print the author's name as format.
	if (conIO(os)) {
		char author[AUTHOR_WIDTH + 1] = { 0 };
		std::strncpy(author, m_author, AUTHOR_WIDTH);
		os << " " << std::setw(AUTHOR_WIDTH) << std::left << std::setfill(' ') << author << " |";
	}
	
	// If the incoming argument is not a console IO object, then print tab character follow by author's name.
	else {
		os << '\t' << m_author;
	}
	return os;
}

/* Read the author name in local variables before setting the attribute to any value. */
std::istream& Book::read(std::istream& istr) {

	// Declare the temporary string size 
	char t_author[256] = { 0 };
	
	// Invoke the read of the Base class.
	Publication::read(istr);
	
	// Check if author's name is exists. Then free the memory held for the author's name
	if (m_author) {
		delete[] m_author;
		m_author = nullptr;
	}
	
	// Check if the incoming argument is a console IO object, then ignore new line character.
	if (conIO(istr)) {
		istr.ignore(1000, '\n');
		std::cout << "Author: ";
		istr.get(t_author, 256);
	}

	// If the incoming argument is not a console IO object, then ignore tab character.
	else {
		istr.ignore(1000, '\t');
		istr.get(t_author, 256);
	}

	// Check if input is the exist content, then assign the author's name of current object to temporary string.
	if (istr) {
		m_author = new char[strlen(t_author) + 1];
		strcpy(m_author, t_author);
	}
	return istr;
}

/* Invoke the set of the base class to set the member id and reset Date. */
void Book::set(int member_id) {
	Publication::set(member_id);
	resetDate();
}

/* Return true if the author's name exists and is not empty */
Book::operator bool() const {
	return m_author && Publication::operator bool();
}