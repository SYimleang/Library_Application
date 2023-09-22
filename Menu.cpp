#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstring>
#include "Menu.h"

using namespace std;

//////////Private function of Menu Class//////////

/* Default Constructor. Created empty Menu with no MenuItems and zero number of item.*/
Menu::Menu() {
	m_title.m_content = nullptr;
	m_noMenuItems = 0;
}

/* Constructor. Created empty Menu and zero number of item with title.*/
Menu::Menu(const char* title) {
	m_title.m_content = new char[strlen(title) + 1];
	strcpy(m_title.m_content, title);
	m_noMenuItems = 0;
}

/* Destructor.*/
Menu::~Menu() {

	//Loop through all element in m_menuItem and deallocate all of them.
	for (int ndx = 0; ndx < m_noMenuItems; ndx++) {
		delete m_menuItem[ndx];
	}
}

/* Display the title of the Menu on ostream if the title is not empty.*/
ostream& Menu::displayTitle(ostream& os) const {

	if (m_title.m_content != nullptr) {
		os << m_title.m_content;
	}
	return os;
}

/* Display the entire Menu on ostream.*/
ostream& Menu::display(ostream& os) const {

	//Display title.
	displayTitle();
	if (m_title.m_content != nullptr) {
		os << ":" << endl;
	}

	//Display all the MenuItems one by one.
	for (int ndx = 0; ndx < m_noMenuItems; ndx++) {
		os << setw(2) << setfill(' ') << ndx + 1 << "- ";
		(*m_menuItem[ndx]).display(os);
		os << endl;
	}
	os << setw(2) << setfill(' ') << "0" << "- Exit" << endl;
	os << "> ";

	return os;
}

/* Displays the Menu and gets the user selection.*/
unsigned int Menu::run() {
	unsigned select = -1;

		//Display the Menu.
		display();

		//If input is invalid, then display error message and loop again.
		do {
			
			//Get input from user.
			cin >> select;
			
			if (select < 0 || select > (unsigned)m_noMenuItems || cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				select = -1;
				cout << "Invalid Selection, try again: ";
			}
		} while (select < 0 || select >(unsigned)m_noMenuItems || cin.fail());
	
	return select;
}

/* Overload operator "~" to do exactly what the run function does (two different ways to run the menu)*/
unsigned int Menu::operator~() {
	return run();
}

/*Overload a member insertion operator (operator<<) to add a MenuItem to the Menu.*/
Menu& Menu::operator<<(const char* menuItemContent) {

	//If the next spot for a MenuItem is available in the array of MenuItem pointers.
	if (m_noMenuItems < MAX_MENU_ITEMS) {

		//Dynamic allocating a MenuItem.
		m_menuItem[m_noMenuItems] = new MenuItem();

		//Dynamic allocating m_content member of MenuItem out of the content received
		m_menuItem[m_noMenuItems]->m_content = new char[strlen(menuItemContent) + 1];
		strcpy(m_menuItem[m_noMenuItems]->m_content, menuItemContent);
		m_noMenuItems++;
	}
	return *this;
}

/* Overload two type conversions for int to return the number of MenuItems.*/
Menu::operator int() const {
	return m_noMenuItems;
}

/* Overload two type conversions for unsigned int to return the number of MenuItems.*/
Menu::operator unsigned int() const {
	return m_noMenuItems;
}

/* Overload the type conversion for bool to return true if the Menu has one or more MenuItems otherwise, false.*/
Menu::operator bool() const {
	bool status = false;
	
	if (m_noMenuItems > 0) {
		status = true;
	}

	return status;
}

/* Overload the insertion operator to print the title of the Menu using cout.*/
ostream& operator<<(ostream& os, const Menu& menu){
	if (menu.m_noMenuItems > 0) {
		menu.displayTitle(os);
	}

	return os;
}

/* Overload the indexing operator to return the const char* cast of the corresponding MenuItem in the array of MenuItem pointers.*/
const char* Menu::operator[](int ndx) const {

	//If the index passes the number of MenuItems in the Menu, loop back to the beginning.
	if (ndx >= 0 && ndx < m_noMenuItems) {
		return (const char*)(*m_menuItem[ndx]);
	}
	return "";
}

//////////Private function of MenuItem Class//////////

/* Default Constructor, Sets content to empty state.*/
MenuItem::MenuItem() {
	m_content = nullptr;
}

/* Constructor. Allocates and sets the content of the MenuItem to a Cstring value at the moment of instantiation*/
MenuItem::MenuItem(const char* title) {
	m_content = new char[strlen(title) + 1];
	strcpy(m_content, title);
}

/* Destructor. Deallocates the content*/
MenuItem::~MenuItem() {
	delete[] m_content;
}

/* Validate the content. Return true if content is valid.*/
bool MenuItem::validate() const{
	bool status = false;
	if (m_content != nullptr && m_content[0] != '\0') {
		status = true;
	}
	return status;
}

/* Return true, if it is not empty and it should return false if it is empty.*/
MenuItem::operator bool() const {
	return validate();
}

/* Return the address of the content Cstring.*/
MenuItem::operator const char*() const{
	return m_content;
}

/* Display the content of the MenuItem on ostream.*/
ostream& MenuItem::display(ostream& os) const {

	if (validate()) {
		os << m_content;
	}
	return os;
}