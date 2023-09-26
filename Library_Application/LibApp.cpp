#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "LibApp.h"

bool LibApp::confirm(const char* message) {

	Menu confirm(message);

	confirm << "Yes";

	return confirm.run() == 1;
}

/* Print loading message and then open the data file for reading and read all the publications in dynamic instances pointed by the PPA Array. */
void LibApp::load() {
	std::cout << "Loading Data" << std::endl;

	// Open ifile stream follow filename.
	std::ifstream iFile(m_fileName);

	char type = {};

	// Iterating over the file
	for (int i = 0; iFile && i < LIBRARY_CAPACITY; i++) {

		// Reading a single character for the type of publication.
		iFile >> type;

		// Ignoring the white space character.
		iFile.ignore();

		// Check if the file is open, then check the type of publication.
		if (iFile) {

			// If publication is 'P' type, then dynamic allocating by Publication object.
			if (type == 'P')
				m_PPA[i] = new Publication;

			// If publication is 'B' type, then dynamic allocating by Book object.
			else if (type == 'B')
				m_PPA[i] = new Book;

			// Check if publication is valid, then extracting the object from the file stream.
			if (m_PPA[i]) {
				iFile >> *m_PPA[i];		// Extract the object.
				m_NOLP++;				// Increase the number of publication load.

				// Setting the LLRN to the reference number of the last publication read.
				m_LLRN = m_PPA[i]->getRef();
			}
		}
	}
}

/* Saving the content to the file. */
void LibApp::save() {
	std::cout << "Saving Data" << std::endl;

	// Open ostream file follow filename. 
	std::ofstream out_file(m_fileName);

	// Loop through all Loaded Publication.
	for (int i = 0; i < m_NOLP; i++) {

		// If serial number of publication object is valid, then save the Publication object content.
		if (m_PPA[i]->getRef() != 0)
		{
			out_file << *m_PPA[i] << std::endl;
		}
	}
	// Close the ostream file.
	out_file.close();
}

/* Searching the content from type selected. First will prompt user to select searching type and title, then will search through the content and return index of publication found. */
int LibApp::search(int searchType) {

	char title[256] = {};															// String array to hold the title input.
	int selectedType = 0, i = 0, libRef = 0;										// Initialize selectType and serial number of publication object to 0
	char typeChar;																	// Declare character variable to hold the type of publication.
	PublicationSelector pubSel("Select one of the following found matches:", 15);	// Initialize the Selector by set to display only 15 orders.

	// Getting the type of publication to search for from the user
	selectedType = m_publicType.run();

	// If selected type is 1, it will sets the publication type to 'B'.
	if (selectedType == 1) {
		typeChar = 'B';
	}

	// If selected type is 2, it will sets the publication type to 'P'.
	else if (selectedType == 2) {
		typeChar = 'P';
	}

	// Getting the title from input to search the PPA.
	std::cin.ignore(1000, '\n');
	std::cout << "Publication Title: ";
	std::cin.getline(title, 256);

	// If search type is 1, it will searches all publications.
	if (searchType == 1) {

		// Loop through all Loaded Publication.
		for (i = 0; i < m_NOLP; i++) {

			// Check if PPA is valid, then insert object into pubSel object to generate a selector to choose an element.
			if (m_PPA[i]->operator==(title) && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
				pubSel << m_PPA[i];
			}
		}
	}

	// If search type is 2, it will searches only those publications which are on loan by library members.
	else if (searchType == 2) {

		// Loop through all Loaded Publication.
		for (i = 0; i < m_NOLP; i++) {

			// Check if PPA is valid, then insert object into pubSel object to generate a selector to choose an element.
			if (m_PPA[i]->operator==(title) && m_PPA[i]->onLoan() && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
				pubSel << m_PPA[i];
			}
		}
	}

	// If search type is 3, it will searches only those publications which are not on loan.
	else if (searchType == 3) {

		// Loop through all Loaded Publication.
		for (i = 0; i < m_NOLP; i++) {

			// Check if PPA is valid, then insert object into pubSel object to generate a selector to choose an element.
			if (m_PPA[i]->operator==(title) && !m_PPA[i]->onLoan() && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
				pubSel << m_PPA[i];
			}
		}
	}

	// If matches are found, sort the result and get the user's selection.
	if (pubSel) {
		pubSel.sort();
		libRef = pubSel.run();

		// If serial number of publication object is valid, then display the serial number of publication object.
		if (libRef > 0)
		{
			std::cout << *getPub(libRef) << std::endl;
		}

		// If serial number of publication is invalid, then display error message.
		else {
			std::cout << "Aborted!" << std::endl;
		}
	}

	// If matches are not found, then return a message.
	else {
		std::cout << "No matches found!" << std::endl;
	}

	// Return the library reference number.
	return libRef;
}

/*Call search() method and check existing publication, then print return status message.*/
void LibApp::returnPub() {
	bool abort = false;		// Variable to hold the status of aborted.

	std::cout << "Return publication to the library" << std::endl;

	int libRef = search(2);	// Variable to hold the library referance number, which search only publications (which on loan by library members)
	
	// Check if library referance number is not valid, then sets abort to true.
	if (libRef <= 0) {
		abort = true;
	}

	// Check if abort status is false, then call confirm method.
	if (!abort) {
		bool confirmed = confirm("Return Publication?");

		// If confirm status is true, then get days have been loaned.
		if (confirmed) {
			int daysLoaned = Date() - getPub(libRef)->checkoutDate();

			// Check if the days are exceeded the maximum loan days.
			if (daysLoaned > MAX_LOAN_DAYS) {

				// Calculating the penalty charge and display.
				double penalty = (daysLoaned - MAX_LOAN_DAYS) * 0.5;
				std::cout << std::fixed << std::setprecision(2);
				std::cout << "Please pay $" << penalty << " penalty for being " << (daysLoaned - MAX_LOAN_DAYS) << " days late!" << std::endl;
			}

			// Set the member id to 0
			getPub(libRef)->set(0);
			m_changed = true;
		}
		std::cout << "Publication returned" << std::endl;
	}
	std::cout << std::endl;
}

/*Adding new publication to library method.*/
void LibApp::newPublication() {
	bool abort = false;		// Variable to hold the status of aborted.

	// Checking if the library is at its maximum capacity.
	if (m_NOLP == LIBRARY_CAPACITY)
	{
		std::cout << "Library is at its maximum capacity!" << std::endl;
		abort = true;
	}

	if (!abort) {
		std::cout << "Adding new publication to the library" << std::endl;

		// Getting the publication type from the user input.
		int pubType = m_publicType.run();
		std::cin.ignore(1000, '\n');

		// Initialize a dynamic publication to null.
		Publication* p = nullptr;

		// Check if the publication type is '0'.
		if (pubType == 0) {
			std::cout << "Aborted!" << std::endl;
			abort = true;
		}

		// If the publication type is Book type
		else if (pubType == 1) {
			p = new Book;
			std::cin >> *p;
		}

		// If the publication type is Publication type
		else if (pubType == 2) {
			p = new Publication;
			std::cin >> *p;
		}

		// Checks if input is not fail.
		if (!std::cin.fail())
		{
			// Checks if abort status is false and confirmation is true.
			if (!abort && confirm("Add this publication to the library?")) {

				// Checking if the publication object is not valid, then deallocate the Publication object.
				if (!*p) {
					std::cout << "Failed to add publication!" << std::endl;
					delete p;
				}

				// If the publication object is valid.
				else {

					// Increase the Last reference number and set reference as current reference number.
					m_LLRN++;
					p->setRef(m_LLRN);

					// Adding the publication object's address to the end of the PPA
					m_PPA[m_NOLP] = p;

					// Increase the number of loaded publication and set change status to true.
					m_NOLP++;
					m_changed = true;

					std::cout << "Publication added" << std::endl;
				}
			}
		}

		// If input is fail, then abort the publication.
		else {
			std::cin.ignore(1000, '\n');
			std::cin.clear();
			std::cout << "Aborted!" << std::endl;
		}
	}
	std::cout << std::endl;
}

/*Remove publication from library method.*/
void LibApp::removePublication() {

	std::cout << "Removing publication from the library" << std::endl;
	
	int libRef = search(1);		//Searching for all publication from library.
	
	// Check if library referance number is valid.
	if (libRef) {

		//If confirm method return true, then sets m_changed to true.
		if (confirm("Remove this publication from the library?")) {

			// Setting the library reference of the selected publication to 0 (zero)
			getPub(libRef)->setRef(0);

			m_changed = true;
			std::cout << "Publication removed" << std::endl;
		}
	}
	std::cout << std::endl;
}

/* Check out publication method. First, this method will search the available publication and prompt user to enter information, then will display checkout status*/
void LibApp::checkOutPub() {

	std::cout << "Checkout publication from the library" << std::endl;

	int libRef = search(3);		// Searching for only those publications which are not on loan and available.
	
	// Checking if a match library referance number is found, then call confirm method.
	if (libRef > 0) {
		bool confirmed = confirm("Check out publication?");

		//If confirm method return true, then get membership number from user input.
		if (confirmed) {
			int t_member;
			bool validInput = false;
			std::cout << "Enter Membership number: ";

			// Get the membership number from input. If the number is out of range then loop until get the valid membership number.
			do {
				std::cin >> t_member;
				if (!std::cin || t_member < 1000 || t_member > 99999) {
					std::cout << "Invalid membership number, try again: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					validInput = false;
				}
				else {
					validInput = true;
				}
			} while (validInput == false);

			// Assign the input membership number to membership number of the object.
			int inputMembership = t_member;

			// Setting the membership number of the selected publication the integer value
			getPub(libRef)->set(inputMembership);

			m_changed = true;
			std::cout << "Publication checked out" << std::endl;
		}
	}
	std::cout << std::endl;
}

// Return the address of a Publication object in the PPA that has the library reference number matching the "libRef" argument.
Publication* LibApp::getPub(int libRef) {
	Publication* result = nullptr;
	for (int i = 0; i < m_NOLP; i++)
	{
		if (m_PPA[i]->getRef() == libRef) {
			result = m_PPA[i];
		}
	}

	return result;
}

/*Constructor with file name argument. Initialize default messages for main menu, exit menu and publication type menu. */
LibApp::LibApp(const char* fileName) : m_mainMenu("Library Application"),
	m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicType("Choose the type of publication:") {
	m_changed = false;	// Set change status to false.
	m_NOLP = 0;			// Set Number of loaded publication to 0.

	// Checks if filename is valid. Then copy the received filename to filename of the object.
	if (fileName)
	{
		strcpy(m_fileName, fileName);
	}

	// Populated the main menu.
	m_mainMenu << "Add New Publication";
	m_mainMenu << "Remove Publication";
	m_mainMenu << "Checkout publication from library";
	m_mainMenu << "Return publication to library";
	
	// Populated the exit menu.
	m_exitMenu << "Save changes and exit";
	m_exitMenu << "Cancel and go back to the main menu";

	// Populating publication type menu items using operator overload in menu class
	m_publicType << "Book";
	m_publicType << "Publication";

	load();
}

/*Destructor. Delete all dynamically allocated memories.*/
LibApp::~LibApp() {
	for (int i = 0; i < m_NOLP; i++) {
		delete m_PPA[i];
	}
}

/* Displays the main menu and based on the user's selection calls the corresponding private method 
	and repeats the above until the user chooses to exit. */
void LibApp::run() {
	
	int mainselect;
	int exitSelect;
	bool flag = false;

	// Loop until user confirmed to exit.
	do {

		// Display main menu and prompt user to select.
		mainselect = m_mainMenu.run();

		if (mainselect == 1) {		// If user selected 1, then call newPublication() method.
			newPublication();
		}
		else if (mainselect == 2) {	// If user selected 2, then call removePublication() method.
			removePublication();
		}
		else if (mainselect == 3) {	// If user selected 3, then call checkOutPub() method.
			checkOutPub();
		}
		else if (mainselect == 4) {	// If user selected 4, then call returnPub() method.
			returnPub();
		}

		// If user selected something else.
		else {

			// If the information has been changed, then the program will display an exit menu to ask the user to confirm save.
			if (m_changed) {
				exitSelect = m_exitMenu.run();
				if (exitSelect == 1) {			// If user selected 1, then call save() method. Then exit the program.
					save();
					std::cout << std::endl;
					std::cout << "-------------------------------------------" << std::endl;
					std::cout << "Thanks for using Library Application" << std::endl;
					flag = true;
				}
				else if (exitSelect == 2) {		// If user selected 2, then keep continue the loop.
					std::cout << std::endl;
				}	

				// If user selected something else.
				else {

					// Ask user to confirm to discard all the change. If yes, program will discard the change and exit the program.
					if (confirm("This will discard all the changes are you sure?")) {
						std::cout << std::endl;
						std::cout << "-------------------------------------------" << std::endl;
						std::cout << "Thanks for using Library Application" << std::endl;
						flag = true;
					}
				}
			}
			else {
				std::cout << std::endl;
				std::cout << "-------------------------------------------" << std::endl;
				std::cout << "Thanks for using Library Application" << std::endl;
				flag = true;
			}
		}
	} while (!flag);
}