#ifndef MENU_H_
#define MENU_H_
#define MAX_MENU_ITEMS 20
#include <iostream>

class MenuItem {
private:
	char* m_content;
	MenuItem();
	MenuItem(const char* title);

	// Rules of three
	~MenuItem();
	MenuItem(const MenuItem& src) = delete;
	MenuItem& operator=(const MenuItem& src) = delete;
	

	bool validate() const;
	operator bool() const;
	operator const char* () const;

	std::ostream& display(std::ostream& os = std::cout) const;

	friend class Menu;
};

class Menu {
private:
	MenuItem m_title;
	MenuItem* m_menuItem[MAX_MENU_ITEMS];
	int m_noMenuItems;
	friend class MenuItem;
public:
	Menu();
	Menu(const char* title);

	// Rules of three
	~Menu();
	Menu(const Menu& src) = delete;
	Menu& operator=(const Menu& src) = delete;
	

	std::ostream& displayTitle(std::ostream& os = std::cout) const;
	std::ostream& display(std::ostream& os = std::cout) const;
	unsigned int run();
	unsigned int operator~();
	Menu& operator<<(const char* menuItemContent);
	operator int() const;
	operator unsigned int() const;
	operator bool() const;

	const char* operator[](int ndx) const;

	friend std::ostream& operator<<(std::ostream& os, const Menu& menu);

};

#endif