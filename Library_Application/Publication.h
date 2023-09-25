#ifndef PUBLICATION_H_
#define PUBLICATION_H_
#include <iostream>
#include <cstring>
#include "Date.h"
#include "Streamable.h"
#include "Lib.h"

class Publication : public Streamable {
	char* m_title;							// C-string to hold a dynamic title for the publication.
	char m_shelfId[SHELF_ID_LEN + 1];	// C-string to hold the location of the publication in the library.
	int m_membership;						// Integer to hold a 5 digit membership number of members of the library.
	int m_libRef;							// Integer to hold serial number is used internally to uniquely identify each publication in the system.
	Date m_date;							// Date object to hold date is used for the publish date of the item.

public:
	Publication();										// Default constructor
	Publication(const Publication& src);				// Copy class constructor
	~Publication();										// Destructor	
	Publication& operator=(const Publication& src);		// Overload assign operator

	virtual void set(int member_id);	// Sets the membership attribute to either zero or a five-digit integer.
	void setRef(int value);				// Sets the **libRef** attribute value
	void resetDate();					// Sets the date to the current date of the system.
	
	virtual char type()const;					//Returns the character 'P' to identify this object as a "Publication object"
	bool onLoan()const;							//Returns true is the publication is checkout (membership is non-zero)
	Date checkoutDate()const;					//Returns the date attribute
	bool operator==(const char* title)const;	//Returns true if the argument title appears anywhere in the title of the publication. Otherwise, it returns false; (use strstr() function in <cstring>)
	operator const char* ()const;				//Returns the title attribute
	int getRef()const;							//Returns the libRef attribute.

	bool conIO(std::ios& io)const;			// Method to check the address of the io object is the same as the address of either the cin object or the cout object.
	std::ostream& write(std::ostream& os) const;	// Method to check the os argument is a console IO object
	std::istream& read(std::istream& istr);		// Method to read all the values in local variables before setting the attributes to any values.
	operator bool() const;				// Method to check neither of the title or shelfId attributes is null or empty.
};
#endif //!PUBLICATION_H_
