#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Publication.h"

/* Default constructor. Set all attributes to empty state. */ 
Publication::Publication() {
	m_title = nullptr;
	m_shelfId[0] = '\0';
	m_membership = 0;
	m_libRef = -1;
	resetDate();
}

/* Destructor. Deallocate the title. */
Publication::~Publication() {
	delete[] m_title;
}

/* Copy constructor. */
Publication::Publication(const Publication& src) {
	*this = src;
}

/* Copy assign operator. */
Publication& Publication::operator=(const Publication& src) {

	// Check if title of current object is exists.
	if (m_title)
	{
		// Deallocate previous address and set to null.
		delete[] m_title;
		m_title = nullptr;
	}

	// Check if current object is not same as receives object, receive title is exists and receive shelf ID is exists.
	if (this != &src && src.m_title && src.m_shelfId) {

		// Dynamic allocating and copy title.
		m_title = new char[strlen(src.m_title) + 1];
		strcpy(m_title, src.m_title);

		// Copy shelf ID, membership number, library refernce and date.
		strcpy(m_shelfId, src.m_shelfId);
		m_membership = src.m_membership;
		m_libRef = src.m_libRef;
		m_date = src.m_date;
	}

	// If current title of current object does not exist, then set to null.
	else {
		m_title = nullptr;
	}
	return *this;
}

/* Move constructor. */
Publication::Publication(Publication && src)
{
	*this = std::move(src);
}

/* */
Publication& Publication::operator=(Publication&& src) {
	// Self assignment check.
	if(this != &src){
		// Cleanup
		delete[] m_title;

		// Shallow copy members
		for (int i = 0; i < 5; ++i)
			m_shelfId[i] = src.m_shelfId[i];
		m_membership = src.m_membership;
		m_libRef = src.m_libRef;
		m_date = src.m_date;

		// Move resource
		strcpy(m_title, src.m_title);
		src.m_title = nullptr;
	}
	return *this;
}

/* Sets the membership attribute to either zero or a five-digit integer. */
void Publication::set(int member_id) {
	m_membership = member_id;
}

/* Sets the** libRef** attribute value */ 
void Publication::setRef(int value) {
	m_libRef = value;
}

/* Sets the date to the current date of the system. */
void Publication::resetDate() {
	m_date = Date();
}

/* //Returns the character 'P' to identify this object as a "Publication object" */
char Publication::type() const {
	return 'P';
}

/* Returns true is the publication is checkout (membership is non-zero) */
bool Publication::onLoan()const {
	return m_membership != 0;
}

/* Returns the date attribute */
Date Publication::checkoutDate()const {
	return m_date;
}

/* Returns true if the argument title appears anywhere in the title of the publication. 
Otherwise, it returns false; (use strstr() function in <cstring>) */
bool Publication::operator==(const char* title)const {
	return strstr(m_title, title) != nullptr;
}

/* Returns the title attribute */
Publication::operator const char* ()const {
	return m_title;
}

/* Returns the libRef attirbute. */
int Publication::getRef()const {
	return m_libRef;
}

/* Returns true if the address of the io object is the same as the address of either the cin object or the cout object. */
bool Publication::conIO(std::ios& io)const {
return &io == &std::cin || &io == &std::cout;
}

/* If the os argument is a console IO object, print shelfId, title, membership and date attributes. */
std::ostream& Publication::write(std::ostream& os) const {

	// Create the temporary string to hold only 30 characters of title name, Then copy the title name.
		char t_title[31];
		strncpy(t_title, m_title, 30);
		t_title[30] = '\0';

		// Check if address of io object is same as receive os. Then print as format.
		if (conIO(os)) {
			os << "| " << m_shelfId << " | " << std::setw(30) << std::left << std::setfill('.') << t_title << " | ";
			if (m_membership == 0) {
				os << " N/A ";
			}
			else {
				os << m_membership;
			}
			os << " | " << m_date << " |";
		}

		// If address is not same, then print as no exist format.
		else {
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
			if (m_membership == 0) {
				os << " N/A ";
			}
			else {
				os << m_membership;
			}
			os << "\t" << m_date;
		}
		return os;
}

/* Read all the values in local variables before setting the attributes to any values. */
std::istream& Publication::read(std::istream& istr) {

	// Create temporary variables, string and objects for receive the input.
	char t_title[TITLE_WIDTH + 1]{}, t_shelfId[SHELF_ID_LEN + 1]{};
	int t_libRef = -1, t_membership = 0;
	Date t_date;

	// Clearing the memory if it is allocated and setting the values to default
	if (m_title) {
		delete[] m_title;
		m_title = nullptr;
	}
	m_title = nullptr;
	m_shelfId[0] = '\0';
	m_membership = 0;
	m_libRef = -1;
	resetDate();

	// Check if address of io object is same as receive instr. Then read as format.
	if (conIO(istr)) {
		std::cout << "Shelf No: ";
		istr.getline(t_shelfId, SHELF_ID_LEN + 1);

		if (strlen(t_shelfId) != SHELF_ID_LEN) {
			istr.setstate(std::ios::failbit);
		}

		std::cout << "Title: ";
		istr.getline(t_title, TITLE_WIDTH + 1);

		std::cout << "Date: ";
		istr >> t_date;
	}

	// If address is not same, then read as no exist format.
	else {
		istr >> t_libRef;
		istr.ignore();
		istr.getline(t_shelfId, SHELF_ID_LEN + 1, '\t');
		istr.getline(t_title, TITLE_WIDTH + 1, '\t');
		istr >> t_membership;
		istr.ignore();
		istr >> t_date;
	}

	// Check if date is not exists, then set error state flag as logical error on io operation.
	if (!t_date) {
		istr.setstate(std::ios::failbit);
	}

	// Check if input is the exist content, then assign all attributes of current object to temporary variables.
	if (istr) {
		m_title = new char[strlen(t_title) + 1];
		strcpy(m_title, t_title);
		strcpy(m_shelfId, t_shelfId);
		m_membership = t_membership;
		m_date = t_date;
		m_libRef = t_libRef;
	}
	return istr;
}

/* Returns true if neither of the title or shelfId attributes is null or empty. Otherwise, it will return false. */
Publication::operator bool() const {
	return (m_title && m_shelfId[0] != '\0');

}