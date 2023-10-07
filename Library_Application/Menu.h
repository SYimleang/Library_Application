#ifndef MENU_H_
#define MENU_H_

#include <iostream>

#define MAX_MENU_ITEMS 20

class MenuItem {
	char* m_content;
	
	MenuItem();						// Default constructor.						
	MenuItem(const char* title);	// Constructor with one argument.

	// Rules of five
	~MenuItem();										// Destructor
	MenuItem(const MenuItem& src) = delete;				// Prevent copy constructor
	MenuItem& operator=(const MenuItem& src) = delete;	// Prevent copy assignment operator
	MenuItem(MenuItem&&) = delete;						// Prevent move constructor
	MenuItem& operator=(MenuItem&&) = delete;			// Prevent move assignment operator

	bool validate() const;			// Validate content method.
	operator bool() const;			// Overload bool type conversions operator.
	operator const char* () const;	// Overload const string type conversions operator.

	std::ostream& display(std::ostream& os = std::cout) const;	// Display the content method.

	friend class Menu;
};

class Menu {
		MenuItem m_title;						// Class Variable to hold the title name.
		MenuItem* m_menuItem[MAX_MENU_ITEMS];	// Class array to hold the menu of the Items.
		int m_noMenuItems;						// Variable to hold number of the items.
		friend class MenuItem;
	public:
		Menu();						// Default Constructor.
		Menu(const char* title);	// Constructor with one argument.

		// Rules of three
		~Menu();									// Destructor.
		Menu(const Menu& src) = delete;				// Prevent copying the instance of a class.
		Menu& operator=(const Menu& src) = delete;	// Prevent assigning the instance of a class.

		std::ostream& displayTitle(std::ostream& os = std::cout) const;	// Display Title method.
		std::ostream& display(std::ostream& os = std::cout) const;		// Display content method.
		unsigned int run();												// Run the whole module method.

		unsigned int operator~();						// Overload ~ operator.
		Menu& operator<<(const char* menuItemContent);	// Overload insertion operator.
		operator int() const;							// Overload int type conversions operator.
		operator unsigned int() const;					// Overload int type conversions operator.
		operator bool() const;							// Overload bool type conversions operator.
		const char* operator[](int ndx) const;			// Overload the indexing operator.

		friend std::ostream& operator<<(std::ostream& os, const Menu& menu);

};

#endif //!MENU_H_