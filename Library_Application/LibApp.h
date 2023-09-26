#ifndef LIBAPP_H_
#define LIBAPP_H_

#include <fstream>
#include "Menu.h"
#include "Publication.h"
#include "Lib.h"
#include "PublicationSelector.h"
#include "Book.h"

class LibApp : public Menu {
    bool m_changed;                         // Attribute to hold the changing status of the program.
    Menu m_mainMenu;                        // Class attribute to hold the main menu messages.
    Menu m_exitMenu;                        // Class attribute to hold the exit menu messages.
    char m_fileName[FILENAME_WIDTH + 1];    // Class array of 256 characters attribute to hold the publication data file name.
    Publication* m_PPA[LIBRARY_CAPACITY];   // Class attribute to hold the pointers array of publication objects.
    int m_NOLP;                             // An integer to hold the number of Publications loaded into the PPA.
    int m_LLRN;                             // An integer to hold the last library reference number read from the data file.
    Menu m_publicType;                      // Class attribute to hold the publication type.

    bool confirm(const char* message);   // The method to return the confirmation.
    void load();                         // prints: "Loading Data"
    void save();                         // prints: "Saving Data"
    int search(int selected);            // prints: "Searching for publication"
    void returnPub();                    //  Calls the search() method. Prints "Returning publication" prints "Publication returned" sets m_changed to true.
    void newPublication();               // Adding new publication method.
    void removePublication();            // Remove publication method.
    void checkOutPub();                  // Check out republication method.

public:
    Publication* getPub(int libRef); // The PPA that has the library reference number matching the "libRef" argument.

    LibApp(const char* fileName);   // Constructor with C-String parameter (filename).

    // Rules of three
    ~LibApp();                                      // Destructor.
    LibApp(const LibApp& src) = delete;             // Prevent copying the instance of a class.
    LibApp& operator=(const LibApp& src) = delete;  // Prevent assigning the instance of a class.

    void run();     // The run method is the main application driver.
};
#endif // !LIBAPP_H_