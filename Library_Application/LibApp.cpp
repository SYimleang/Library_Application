#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "LibApp.h"
using namespace std;

bool LibApp::confirm(const char* message) {

	Menu confirm(message);

	confirm << "Yes";

	return confirm.run() == 1;
}

/* Print loading message.*/
void LibApp::load() {
	cout << "Loading Data" << endl;
}

/* Print saving message.*/
void LibApp::save() {
	cout << "Saving Data" << endl;
}

/* Print searching message.*/
void LibApp::search() {
	cout << "Searching for publication" << endl;
}

/*Call search() method and print return status message.*/
void LibApp::returnPub() {
	search();
	cout << "Returning publication" << endl;
	cout << "Publication returned" << endl;
	cout << endl;
	m_changed = true;
}

/* Adding new publication to library method.*/
void LibApp::newPublication() {
	m_changed = false;
	cout << "Adding new publication to library" << endl;

	//If confirm method return true, then sets m_changed to true.
	if (confirm("Add this publication to library?")) {
		m_changed = true;
		cout << "Publication added" << endl;
	}
	cout << endl;
}

/* Remove publication from library method.*/
void LibApp::removePublication() {
	cout << "Removing publication from library" << endl;
	m_changed = false;
	//Searching for the publication from library.
	search();
	
	//If confirm method return true, then sets m_changed to true.
	if (confirm("Remove this publication from the library?")) {
		m_changed = true;
		cout << "Publication removed" << endl;
	}
	cout << endl;
}

/* Check out publication method.*/
void LibApp::checkOutPub() {
	m_changed = false;

	//Searching for the publication from library.
	search();

	//If confirm method return true, then sets m_changed to true.
	if (confirm("Check out publication?")) {
		m_changed = true;
		cout << "Publication checked out" << endl;
	}
	cout << endl;
}

/* Default Constructor. Initialize default messages for main menu and exit menu.*/
LibApp::LibApp() : m_mainMenu("Library Application"), 
	m_exitMenu("Changes have been made to the data, what would you like to do?") {
	m_changed = false;

	// Populated the main menu.
	m_mainMenu << "Add New Publication";
	m_mainMenu << "Remove Publication";
	m_mainMenu << "Checkout publication from library";
	m_mainMenu << "Return publication to library";
	
	// Populated the exit menu.
	m_exitMenu << "Save changes and exit";
	m_exitMenu << "Cancel and go back to the main menu";

	load();
}

/* Destructor.*/
LibApp::~LibApp() {

}

/* Displays the main menu and based on the user's selection calls the corresponding private method 
and repeats the above until the user chooses to exit. */
void LibApp::run() {
	
	int mainSelect;
	int exitSelect;
	bool flag = false;

	// Loop until user confirmed to exit.
	do {

		// Display main menu and prompt user to select.
		mainSelect = m_mainMenu.run();

		if (mainSelect == 1) {		// If user selected 1, then call newPublication() method.
			newPublication();
		}
		else if (mainSelect == 2) {	// If user selected 2, then call removePublication() method.
			removePublication();
		}
		else if (mainSelect == 3) {	// If user selected 3, then call checkOutPub() method.
			checkOutPub();
		}
		else if (mainSelect == 4) {	// If user selected 4, then call returnPub() method.
			returnPub();
		}

		// If user selected something else.
		else {

			// If the information has been changed, then the program will display an exit menu to ask the user to confirm save.
			if (m_changed) {
				exitSelect = m_exitMenu.run();
				if (exitSelect == 1) {			// If user selected 1, then call save() method. Then exit the program.
					save();
					cout << endl;
					cout << "-------------------------------------------" << endl;
					cout << "Thanks for using Library Application" << endl;
					flag = true;
				}
				else if (exitSelect == 2) {		// If user selected 2, then keep continue the loop.
					cout << endl;
				}	

				// If user selected something else.
				else {

					// Ask user to confirm to discard all the change. If yes, program will discard the change and exit the program.
					if (confirm("This will discard all the changes are you sure?")) {
						cout << endl;
						cout << "-------------------------------------------" << endl;
						cout << "Thanks for using Library Application" << endl;
						flag = true;
					}
				}
			}
			else {
				cout << endl;
				cout << "-------------------------------------------" << endl;
				cout << "Thanks for using Library Application" << endl;
				flag = true;

			}
			
		}
		
	} while (!flag);
}